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

#include "dcsr_corenet.h"

/* Driver Initialization Functions */
int dcsr_corenet1_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct cndc_1 *ptr = (struct cndc_1 *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_CORENET_NAME);

	/* Debug status control */
	DBGFS_CREATE_RW_X32("ctarm", current_dentry, &ptr->ctarm);
	DBGFS_CREATE_RW_X32("ctcr1", current_dentry, &ptr->ctcr1);
	DBGFS_CREATE_RW_X32("cwmsk", current_dentry, &ptr->cwmsk);
	DBGFS_CREATE_RW_X32("ctscr", current_dentry, &ptr->ctscr);
	for (i = 0; i < CNDC_NO_EVENT_COMPARATORS; ++i) {
		sprintf(reg_name, "cc%ddecr1", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->comp[i].cc_decr[0]);
		sprintf(reg_name, "cc%ddecr2", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->comp[i].cc_decr[1]);
	}
	DBGFS_CREATE_RW_X32("cpmsr1", current_dentry, &ptr->cpmsr1);
	for (i = 0; i < CNDC_NO_REF_EVENTS; ++i) {
		sprintf(reg_name, "cprescr%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cprescr[i]);
	}

	return 0;
}

/* Driver Initialization Functions */
int dcsr_corenet2_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct cndc_2 *ptr = (struct cndc_2 *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	current_dentry = dev->current_dentry;
	if (!current_dentry)
		CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
						DEBUGFS_CORENET_NAME);

	/* Debug status control */
	DBGFS_CREATE_RW_X32("cdbcr0", current_dentry, &ptr->cdbcr0);
	DBGFS_CREATE_RW_X32("cdbcr1", current_dentry, &ptr->cdbcr1);
	DBGFS_CREATE_RW_X32("cdbcr2", current_dentry, &ptr->cdbcr2);
	DBGFS_CREATE_RW_X32("cdbcr3", current_dentry, &ptr->cdbcr3);
	for (i = 0; i < CNDC_NO_ADDRESS_COMPARATORS; ++i) {
		sprintf(reg_name, "cdac%dh", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->addr_comp[i].cdac_h);
		sprintf(reg_name, "cdac%dl", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->addr_comp[i].cdac_l);
	}
	for (i = 0; i < CNDC_NO_TRANS_COMPARATORS; ++i) {
		sprintf(reg_name, "ctac%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ctac[i]);
	}
	DBGFS_CREATE_RW_X32("cdvchh", current_dentry, &ptr->cdvchh);
	DBGFS_CREATE_RW_X32("cdvchl", current_dentry, &ptr->cdvchl);
	DBGFS_CREATE_RW_X32("cdvclh", current_dentry, &ptr->cdvclh);
	DBGFS_CREATE_RW_X32("cdvcll", current_dentry, &ptr->cdvcll);
	DBGFS_CREATE_RW_X32("perfmon_enable", current_dentry,
			&ptr->perfmon_enable);
	DBGFS_CREATE_RW_X32("cdpmcr", current_dentry, &ptr->cdpmcr);

	return 0;
}
