/*
 * Copyright (C) 2010, 2011, 2012, 2013 Freescale Semiconductor, Inc.
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

#include <linux/slab.h>
#include "dbg_cpu.h"
#include "dbg_pmr.h"
#include "dbg_spr.h"

/* CPU private data */
struct cpu_regs {
	struct spr_register spr[SPR_MAX];
	struct pmr_register pmr[PMR_MAX];
};

/* CPU specific remove function */
int cpu_remove_fn(struct dbg_device *dev)
{
	int i;
	void *mem;

	for (i = 0; i < dev->num_mem_ids; i++) {
		if (dev->private[i]) {
			mem = dev->private[i];
			dev->private[i] = 0;
			kfree(mem);
		}
	}
	return 0;
}

/* CPU specific initialization function */
int cpu_init_fn(struct dbg_device *dev)
{
	struct device_node *np = dev->np;
	struct device_node *phandle;
	const u32 *property;
	int lenp;
	int i;

	/* the cpu reg property defines the virtual core id
	 associated with the memory range */
	property = of_get_property(np, "cpu-handle", NULL);
	if (property) {
		phandle = of_find_node_by_phandle(*property);
		if (phandle) {
			property = of_get_property(phandle, "reg", &lenp);
			if (property && lenp <= MAX_MEM_RANGE*sizeof(int)) {
				dev->num_mem_ids = lenp/sizeof(int);
				for (i = 0; i < dev->num_mem_ids; i++)
					dev->mem_id[i] = property[i];
			} else {
				printk(KERN_ERR
					": cpu \"reg\" property size (%d)"
					" larger than expected.\n",
					(int)(lenp/sizeof(int)));
			}
		}
	}

	for (i = 0; i < dev->num_mem_ids; i++) {
		dev->private[i] =
			kzalloc(sizeof(struct cpu_regs), GFP_ATOMIC);
		if (dev->private[i]) {
			/* define a remove function for the cpu */
			dev->dev_remove_fn = cpu_remove_fn;
			/* init cpu_regs */
			spr_reg_init(((struct cpu_regs*)(dev->private[i]))->spr,
				dev->mem_id[i]);
			pmr_reg_init(((struct cpu_regs*)(dev->private[i]))->pmr,
				dev->mem_id[i]);
		}
	}

	return 0;
}

/* Driver Initialization Function */
int dbg_cpu_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct core_proxy *ptr;
	struct cpu_regs *regs;
	int i;

	for (i = 0; i < dev->num_mem_ids; i++) {
		/* mem_id is the virtual core id */
		dev->dbgfs_dir_index = dev->mem_id[i];
		ptr = (struct core_proxy *)dev->mem_ptr[i];

		CREATE_CURRENT_DBGFS_DIR_INDEXED(parent_dentry, dev,
			DEBUGFS_CPU_NAME, dev->dbgfs_dir_index);

		/* Configuration */
		DBGFS_CREATE_RO_X32("pvr", current_dentry, &ptr->pvr);

		/* Machine state and control */
		DBGFS_CREATE_RW_X32("msr", current_dentry, &ptr->msr);
		DBGFS_CREATE_RO_X32("prsr", current_dentry, &ptr->prsr);

		/* Debug status control */
		DBGFS_CREATE_RW_X32("edbcr0", current_dentry, &ptr->edbcr0);
		DBGFS_CREATE_RO_X32("edbsr0", current_dentry, &ptr->edbsr0);
		DBGFS_CREATE_RO_X32("edbsr1", current_dentry, &ptr->edbsr1);
		DBGFS_CREATE_RO_X32("edesr", current_dentry, &ptr->edesr);
		DBGFS_CREATE_RW_X32("edbsrmsk0", current_dentry,
			&ptr->edbsrmsk0);

		/* PM shadow counters */
#ifdef CONFIG_PPC64
		DBGFS_CREATE_RO_X32("pcch", current_dentry, &ptr->pcch);
		DBGFS_CREATE_RO_X32("pccl", current_dentry, &ptr->pccl);
#else
		DBGFS_CREATE_RO_X32("pcc", current_dentry, &ptr->pccl);
#endif
		DBGFS_CREATE_RO_X32("pmcc0", current_dentry, &ptr->pmcc[0]);
		DBGFS_CREATE_RO_X32("pmcc1", current_dentry, &ptr->pmcc[1]);
		DBGFS_CREATE_RO_X32("pmcc2", current_dentry, &ptr->pmcc[2]);
		DBGFS_CREATE_RO_X32("pmcc3", current_dentry, &ptr->pmcc[3]);
#if defined(CORE_E6500)
		DBGFS_CREATE_RO_X32("pmcc4", current_dentry, &ptr->pmcc[4]);
		DBGFS_CREATE_RO_X32("pmcc5", current_dentry, &ptr->pmcc[5]);
		DBGFS_CREATE_RO_X32("pdir", current_dentry, &ptr->pdir);
#endif /* defined(CORE_E6500) */

		/* nexus */
		DBGFS_CREATE_RW_X32("dc1", current_dentry, &ptr->dc1);
		DBGFS_CREATE_RW_X32("dc2", current_dentry, &ptr->dc2);
#if defined(CORE_E6500)
		DBGFS_CREATE_RW_X32("dc3", current_dentry, &ptr->dc3);
#endif /* defined(CORE_E6500) */
		DBGFS_CREATE_RW_X32("dc4", current_dentry, &ptr->dc4);
		DBGFS_CREATE_RW_X32("wt1", current_dentry, &ptr->wt1);
#if defined(CORE_E6500)
		DBGFS_CREATE_RW_X32("wt2", current_dentry, &ptr->wt2);
#endif /* defined(CORE_E6500) */
		DBGFS_CREATE_RW_X32("wmsk", current_dentry, &ptr->wmsk);
		DBGFS_CREATE_RW_X32("ovcr", current_dentry, &ptr->ovcr);
#if defined(CORE_E6500)
		DBGFS_CREATE_RW_X32("rccr", current_dentry, &ptr->rccr);
		DBGFS_CREATE_RW_X32("rcvr", current_dentry, &ptr->rcvr);
		DBGFS_CREATE_RW_X32("pmscr", current_dentry, &ptr->pmscr);
#endif /* defined(CORE_E6500) */

		regs = (struct cpu_regs*)(dev->private[i]);
		if (!regs)
			continue;

		/* PerfMon registers */
		de = debugfs_create_file("pmc0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC0],
			&perfmon_fops);
		de = debugfs_create_file("pmc1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC1],
			&perfmon_fops);
		de = debugfs_create_file("pmc2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC2],
			&perfmon_fops);
		de = debugfs_create_file("pmc3", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC3],
			&perfmon_fops);
#if defined(CORE_E6500)
		de = debugfs_create_file("pmc4", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC4],
			&perfmon_fops);
		de = debugfs_create_file("pmc5", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMC5],
			&perfmon_fops);
#endif /* defined(CORE_E6500) */
		de = debugfs_create_file("pmlca0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA0],
			&perfmon_fops);
		de = debugfs_create_file("pmlca1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA1],
			&perfmon_fops);
		de = debugfs_create_file("pmlca2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA2],
			&perfmon_fops);
		de = debugfs_create_file("pmlca3", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA3],
			&perfmon_fops);
#if defined(CORE_E6500)
		de = debugfs_create_file("pmlca4", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA4],
			&perfmon_fops);
		de = debugfs_create_file("pmlca5", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCA5],
			&perfmon_fops);
#endif /* defined(CORE_E6500) */
		de = debugfs_create_file("pmlcb0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB0],
			&perfmon_fops);
		de = debugfs_create_file("pmlcb1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB1],
			&perfmon_fops);
		de = debugfs_create_file("pmlcb2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB2],
			&perfmon_fops);
		de = debugfs_create_file("pmlcb3", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB3],
			&perfmon_fops);
#if defined(CORE_E6500)
		de = debugfs_create_file("pmlcb4", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB4],
			&perfmon_fops);
		de = debugfs_create_file("pmlcb5", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMLCB5],
			&perfmon_fops);
#endif /* defined(CORE_E6500) */
		de = debugfs_create_file("pmgc0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->pmr[PMR_PMGC0],
			&perfmon_fops);

		/* Special Purpose Registers */
		de = debugfs_create_file("dbsr", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBSR],
			&spr_fops);
		de = debugfs_create_file("dbcr0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBCR0],
			&spr_fops);
		de = debugfs_create_file("dbcr1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBCR1],
			&spr_fops);
		de = debugfs_create_file("dbcr2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBCR2],
			&spr_fops);
		de = debugfs_create_file("dbcr4", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBCR4],
			&spr_fops);
#if defined(CORE_E6500)
		de = debugfs_create_file("dbcr5", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBCR5],
			&spr_fops);
		de = debugfs_create_file("dbrr0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DBRR0],
			&spr_fops);
		de = debugfs_create_file("edbrac0", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_EDBRAC0],
			&spr_fops);
#endif /* defined(CORE_E6500) */
		de = debugfs_create_file("iac1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC1],
			&spr_fops);
		de = debugfs_create_file("iac2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC2],
			&spr_fops);
#if defined(CORE_E6500)
		de = debugfs_create_file("iac3", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC3],
			&spr_fops);
		de = debugfs_create_file("iac4", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC4],
			&spr_fops);
		de = debugfs_create_file("iac5", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC5],
			&spr_fops);
		de = debugfs_create_file("iac6", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC6],
			&spr_fops);
		de = debugfs_create_file("iac7", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC7],
			&spr_fops);
		de = debugfs_create_file("iac8", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_IAC8],
			&spr_fops);
#endif /* defined(CORE_E6500) */
		de = debugfs_create_file("dac1", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DAC1],
			&spr_fops);
		de = debugfs_create_file("dac2", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DAC2],
			&spr_fops);
		de = debugfs_create_file("nspd", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_NSPD],
			&spr_fops);
		de = debugfs_create_file("nspc", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_NSPC],
			&spr_fops);
		de = debugfs_create_file("devent", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DEVENT],
			&spr_fops);
		de = debugfs_create_file("ddam", DBGFS_WO_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_DDAM],
			&spr_fops);
		de = debugfs_create_file("npidr", DBGFS_RW_MODE,
			current_dentry,
			(void *)&regs->spr[SPR_NPIDR],
			&spr_fops);
	}
	return 0;
}
