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

#include "dbg_cpu.h"
#include "dbg_perfmon.h"
#include "dbg_spr.h"

/* Driver Initialization Function */
int dbg_cpu_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct core_proxy *ptr = (struct core_proxy *)dev->mem_ptr;
	int index = dev->index;

	CREATE_CURRENT_DBGFS_DIR_INDEXED(parent_dentry, dev,
						DEBUGFS_CPU_NAME);

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
	DBGFS_CREATE_RW_X32("edbsrmsk0", current_dentry, &ptr->edbsrmsk0);

	/* PM shadow counters */
#ifdef CONFIG_PPC64
	DBGFS_CREATE_RO_X32("pcch", current_dentry, &ptr->pcch);
#endif
	DBGFS_CREATE_RO_X32("pcc", current_dentry, &ptr->pccl);
	DBGFS_CREATE_RO_X32("pmcc0", current_dentry, &ptr->pmcc[0]);
	DBGFS_CREATE_RO_X32("pmcc1", current_dentry, &ptr->pmcc[1]);
	DBGFS_CREATE_RO_X32("pmcc2", current_dentry, &ptr->pmcc[2]);
	DBGFS_CREATE_RO_X32("pmcc3", current_dentry, &ptr->pmcc[3]);

	/* nexus */
	DBGFS_CREATE_RW_X32("dc1", current_dentry, &ptr->dc1);
	DBGFS_CREATE_RW_X32("dc2", current_dentry, &ptr->dc2);
	DBGFS_CREATE_RW_X32("dc4", current_dentry, &ptr->dc4);
	DBGFS_CREATE_RW_X32("wt1", current_dentry, &ptr->wt1);
	DBGFS_CREATE_RW_X32("wmsk", current_dentry, &ptr->wmsk);
	DBGFS_CREATE_RW_X32("ovcr", current_dentry, &ptr->ovcr);

	/* PerfMon registers - special since not memory mapped */
	de = debugfs_create_file("pmc0", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+0],
			&perfmon_fops);
	de = debugfs_create_file("pmc1", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+1],
			&perfmon_fops);
	de = debugfs_create_file("pmc2", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+2],
			&perfmon_fops);
	de = debugfs_create_file("pmc3", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+3],
			&perfmon_fops);
	de = debugfs_create_file("pmlca0", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+4],
			&perfmon_fops);
	de = debugfs_create_file("pmlca1", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+5],
			&perfmon_fops);
	de = debugfs_create_file("pmlca2", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+6],
			&perfmon_fops);
	de = debugfs_create_file("pmlca3", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+7],
			&perfmon_fops);
	de = debugfs_create_file("pmlcb0", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+8],
			&perfmon_fops);
	de = debugfs_create_file("pmlcb1", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+9],
			&perfmon_fops);
	de = debugfs_create_file("pmlcb2", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+10],
			&perfmon_fops);
	de = debugfs_create_file("pmlcb3", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+11],
			&perfmon_fops);
	de = debugfs_create_file("pmgc0", DBGFS_RW_MODE, current_dentry,
			(void *)&pm_data[index*NUM_PMRS_PER_CORE+12],
			&perfmon_fops);

	/* Special Purpose Registers - special since not memory mapped */
	de = debugfs_create_file("dbsr", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+0],
			&spr_fops);
	de = debugfs_create_file("dbcr0", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+1],
			&spr_fops);
	de = debugfs_create_file("dbcr1", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+2],
			&spr_fops);
	de = debugfs_create_file("dbcr2", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+3],
			&spr_fops);
	de = debugfs_create_file("dbcr4", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+4],
			&spr_fops);
	de = debugfs_create_file("iac1", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+5],
			&spr_fops);
	de = debugfs_create_file("iac2", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+6],
			&spr_fops);
	de = debugfs_create_file("dac1", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+7],
			&spr_fops);
	de = debugfs_create_file("dac2", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+8],
			&spr_fops);
	de = debugfs_create_file("devent", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+9],
			&spr_fops);
	de = debugfs_create_file("ddam", DBGFS_WO_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+10],
			&spr_fops);
	de = debugfs_create_file("npidr", DBGFS_RW_MODE, current_dentry,
			(void *)&spr_data[index*NUM_SPRS_PER_CORE+11],
			&spr_fops);

	return 0;
}
