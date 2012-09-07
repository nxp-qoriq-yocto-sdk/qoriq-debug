/*
 * Copyright (C) 2010, 2011 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * This software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/err.h>
#include <linux/of_platform.h>
#include <linux/io.h>

#include "qoriq_dbg.h"

/* platform_driver operations */
static int dcsr_probe(struct platform_device *pdev);
static int dcsr_remove(struct platform_device *pdev);
static int dcsr_probe_success;

/* our root directory entry */
static struct dentry *dbgfs_root_dentry;

/* driver will handle all debug activity for devices within dcsr */
const struct of_device_id dcsr_id_table[] = {
		{ .compatible = "fsl,dcsr"},
		{},
};
MODULE_DEVICE_TABLE(of, dcsr_id_table);

static struct platform_driver dcsr_driver = {
		.driver = {
				.name = DRIVER_NAME,
				.owner = THIS_MODULE,
				.of_match_table = dcsr_id_table,
		},
		.probe = dcsr_probe,
		.remove = dcsr_remove,
};

/* maintains information on each sub-device managed by the driver */
struct dbg_devices dbg_dev;

static struct device_node *dbgfs_map_fqcompatible(const char *compatible,
		struct device_node *from,
		const char *type,
		int instance,
		struct dbg_device *dev_ptr)
{
	struct device_node *np;
	np = of_find_compatible_node(from, type, compatible);
	if (np) {
		dev_ptr->mem_ptr = of_iomap(np, instance);
		dev_ptr->np = np;
	} else {
		dev_ptr->mem_ptr = 0;
		dev_ptr->np = 0;
	}
	return np;
}

#define DBGFS_MAP_FROM_COMPATIBLE(compatible, from, dev_ptr) \
		dbgfs_map_fqcompatible(compatible, from, NULL, 0, dev_ptr)

#define DBGFS_MAP_COMPATIBLE(compatible, dev_ptr) \
		dbgfs_map_fqcompatible(compatible, NULL, NULL, 0, dev_ptr)


static struct device_node *dbgfs_map_cpus(const char *compatible,
		struct device_node *from,
		struct dbg_device *dev_ptr)
{
	struct device_node *np;
	struct device_node *phandle;
	const u32 *property;
	const int pindex = 0;

	dev_ptr->index = 0;

	np = dbgfs_map_fqcompatible(compatible, from, NULL, pindex ,dev_ptr);
	if (np) {
		/* find the phandle property which contains the device index */
		property = of_get_property(np, "cpu-handle", NULL);
		if (property) {
			phandle = of_find_node_by_phandle(*property);
			if (phandle) {
				property = of_get_property(phandle, "reg",
								NULL);
				if (property)
					dev_ptr->index = *property;
			}
		}
	}

	return np;
}


static void dbgfs_unmap( struct dbg_device *dev_ptr)
{
	if (dev_ptr->mem_ptr) {
		iounmap(dev_ptr->mem_ptr);
		dev_ptr->mem_ptr = 0;
	}
}

typedef int (*init_fn)(struct dentry *parent_dentry, struct dbg_device *dev);

static int dbgfs_device_init(init_fn fn, struct dbg_device *dev_ptr,
		struct dentry *dentry)
{
	int ret = 0;
	if (dev_ptr->mem_ptr) {
		ret = fn(dentry, dev_ptr);
		if (ret)
			printk(KERN_ERR DRIVER_NAME ": Module @ 0x%08lx failed\n",
					(unsigned long)(dev_ptr)->mem_ptr);
	}
	return ret;
}

static void map_devices(void)
{
	int i;
	struct device_node *np;

	DBGFS_MAP_COMPATIBLE("fsl,dcsr-dpaa", &dbg_dev.dpaa);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-epu", &dbg_dev.epu);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-nal", &dbg_dev.nal);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-npc", &dbg_dev.npc);
	/* map the second NPC range */
	dbgfs_map_fqcompatible("fsl,dcsr-npc", NULL, NULL, 1,
			&dbg_dev.npc_trace);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-nxc", &dbg_dev.nxc);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-ocn", &dbg_dev.ocn);
	DBGFS_MAP_COMPATIBLE("fsl,bman", &dbg_dev.bman);
	DBGFS_MAP_COMPATIBLE("fsl,qman", &dbg_dev.qman);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-rcpm", &dbg_dev.rcpm);
	DBGFS_MAP_COMPATIBLE("fsl,dcsr-corenet", &dbg_dev.cndc1);
	/* map the second corenet range */
	dbgfs_map_fqcompatible("fsl,dcsr-corenet", NULL, NULL, 1,
			&dbg_dev.cndc2);

	/* start at the top (NULL) and search for
	 * at most MAX_NUM_DDR ddr devices
	 */
	np = NULL;
	for (i = 0; i < MAX_NUM_DDR; ++i) {
		np = DBGFS_MAP_FROM_COMPATIBLE("fsl,dcsr-ddr", np, &dbg_dev.ddr[i]);
		if (!np)
			break;
	}

	/* start at the top (NULL) and search for
	 * at most MAX_NUM_CPU cores
	 */
	np = NULL;
	for (i = 0; i < MAX_NUM_CPU; ++i) {
		np = dbgfs_map_cpus("fsl,dcsr-cpu-sb-proxy", np,
				&dbg_dev.cpu[i]);
		if (!np)
			break;
	}

	/* start at the top (NULL) and search for
	 *  at most MAX_NUM_FMAN fman devices
	 */
	np = NULL;
	for (i = 0; i < MAX_NUM_FMAN; ++i) {
		np = DBGFS_MAP_FROM_COMPATIBLE("fsl,fman", np, &dbg_dev.fman[i]);
		if (!np)
			break;
	}
}

static void unmap_devices(void)
{
	int i;
	dbgfs_unmap(&dbg_dev.cndc1);
	dbgfs_unmap(&dbg_dev.cndc2);
	dbgfs_unmap(&dbg_dev.dpaa);
	dbgfs_unmap(&dbg_dev.epu);
	dbgfs_unmap(&dbg_dev.nal);
	dbgfs_unmap(&dbg_dev.npc);
	dbgfs_unmap(&dbg_dev.npc_trace);
	dbgfs_unmap(&dbg_dev.nxc);
	dbgfs_unmap(&dbg_dev.ocn);
	dbgfs_unmap(&dbg_dev.bman);
	dbgfs_unmap(&dbg_dev.qman);
	dbgfs_unmap(&dbg_dev.rcpm);

	for (i = 0; i < MAX_NUM_CPU; ++i)
		dbgfs_unmap(&dbg_dev.cpu[i]);

	for (i = 0; i < MAX_NUM_DDR; ++i)
		dbgfs_unmap(&dbg_dev.ddr[i]);

	for (i = 0; i < MAX_NUM_FMAN; ++i)
		dbgfs_unmap(&dbg_dev.fman[i]);
}

static int dcsr_probe(struct platform_device *pdev)
{
	int ret = 0;
	int i;
	int init_fail;

	/* Map devices from the device tree  */
	map_devices();

	/* create the root directory in debugfs */
	dbgfs_root_dentry = debugfs_create_dir(DBGFS_ROOT_NAME, NULL);
	if (IS_ERR_OR_NULL(dbgfs_root_dentry)) {
		ret = -ENOMEM;
		goto err_1_out;
	}

	/* accumulate all the dbgfs_device_init() return codes */
	init_fail = 0;

	/* create each possible CPU */
	for (i = 0; i < MAX_NUM_CPU; ++i) {
		//dbg_dev.cpu[i].index = i;
		init_fail |= dbgfs_device_init(dbg_cpu_init, &dbg_dev.cpu[i],
				dbgfs_root_dentry);
	}

	/* Corenet is defined in two regions in the same current directory */
	init_fail |= dbgfs_device_init(dcsr_corenet1_init, &dbg_dev.cndc1,
			dbgfs_root_dentry);
	/* pass the cndc1 current dir to the cndc2 */
	dbg_dev.cndc2.current_dentry = dbg_dev.cndc1.current_dentry;
	init_fail |= dbgfs_device_init(dcsr_corenet2_init, &dbg_dev.cndc2,
			dbgfs_root_dentry);

	/* create each possible DDR */
	for (i = 0; i < MAX_NUM_DDR; ++i) {
		dbg_dev.ddr[i].index = i+1;
		init_fail |= dbgfs_device_init(dcsr_ddr_init, &dbg_dev.ddr[i],
				dbgfs_root_dentry);
	}

	init_fail |= dbgfs_device_init(dcsr_dpaa_init, &dbg_dev.dpaa, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(dcsr_epu_init, &dbg_dev.epu, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(dcsr_nal_init, &dbg_dev.nal, dbgfs_root_dentry);

	/* NPC is defined in two regions in the same current directory */
	init_fail |= dbgfs_device_init(dcsr_npc_init, &dbg_dev.npc, dbgfs_root_dentry);
	/* pass the npc current dir to the npc_trace */
	dbg_dev.npc_trace.current_dentry = dbg_dev.npc.current_dentry;
	/* NPC trace needs access to NPC resources */
	init_fail |= dcsr_npc_trace_init(dbgfs_root_dentry, &dbg_dev);

	init_fail |= dbgfs_device_init(dcsr_nxc_init, &dbg_dev.nxc, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(dcsr_ocn_init, &dbg_dev.ocn, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(dcsr_rcpm_init, &dbg_dev.rcpm, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(ccsr_bman_init, &dbg_dev.bman, dbgfs_root_dentry);
	init_fail |= dbgfs_device_init(ccsr_qman_init, &dbg_dev.qman, dbgfs_root_dentry);

	/* create each possible FMAN */
	for (i = 0; i < MAX_NUM_FMAN; ++i) {
		dbg_dev.fman[i].index = i+1;
		init_fail |= dbgfs_device_init(ccsr_fman_init, &dbg_dev.fman[i],
				dbgfs_root_dentry);
	}

	if (init_fail)
		goto err_2_out;

	dcsr_probe_success = 1;
	return ret;

err_2_out:
	debugfs_remove_recursive(dbgfs_root_dentry);
	debugfs_remove(dbgfs_root_dentry);
err_1_out:
	unmap_devices();
	dcsr_probe_success = 0;

	return ret;
}

static int dcsr_remove(struct platform_device *pdev)
{
	if (dcsr_probe_success) {
		debugfs_remove_recursive(dbgfs_root_dentry);
		debugfs_remove(dbgfs_root_dentry);

		unmap_devices();
	}

	return 0;
}

/*
 * Load and unload the module
 * The real work is done when the device is bound to the driver
 */
static int __init dcsr_module_init(void)
{
	return platform_driver_register(&dcsr_driver);
}
module_init(dcsr_module_init);

static void __exit dcsr_module_exit(void)
{
	platform_driver_unregister(&dcsr_driver);
}
module_exit(dcsr_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("freescale.com");
MODULE_DESCRIPTION("QorIQ Trace Debug and Performance Monitoring");
MODULE_SUPPORTED_DEVICE("Freescale QorIQ P4080 P3041 P5020");
