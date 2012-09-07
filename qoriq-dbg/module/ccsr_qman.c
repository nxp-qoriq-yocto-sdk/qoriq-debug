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

#include "ccsr_qman.h"

/* Driver Initialization Function */
int ccsr_qman_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct qman *ptr = (struct qman *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev, DEBUGFS_QMAN_NAME);

	for (i = 0; i < QMAN_SOFT_PORTALS; ++i) {
		/*
		sprintf(reg_name, "qcsp%d_lio_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
		 &ptr->soft_portal_config[i].lio_cfg);
		sprintf(reg_name, "qcsp%d_io_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
		 &ptr->soft_portal_config[i].io_cfg);
		 */
		sprintf(reg_name, "qcsp%d_dd_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->soft_portal_config[i].dd_cfg);
	}

	for (i = 0; i < QMAN_DIRECT_PORTALS; ++i) {
		/*
		sprintf(reg_name, "dcp%d_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
		 &ptr->direct_portal_config[i].dcp_cfg);
		sprintf(reg_name, "dcp%d_dlm_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
		 &ptr->direct_portal_config[i].dlm_cfg);
		sprintf(reg_name, "dcp%d_dlm_avg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
		 &ptr->direct_portal_config[i].dlm_avg);
		 */
		sprintf(reg_name, "dcp%d_dd_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->direct_portal_config[i].dd_cfg);
	}

	DBGFS_CREATE_RW_X32("qman_dd_cfg", current_dentry,
			&ptr->qman_dd_cfg);
	DBGFS_CREATE_RW_X32("qcsp_dd_ihrsr", current_dentry,
			&ptr->qcsp_dd_ihrsr);
	DBGFS_CREATE_RW_X32("qcsp_dd_ihrfr", current_dentry,
			&ptr->qcsp_dd_ihrfr);
	DBGFS_CREATE_RO_X32("qcsp_dd_hasr", current_dentry,
			&ptr->qcsp_dd_hasr);
	DBGFS_CREATE_RW_X32("dcp_dd_ihrsr", current_dentry,
			&ptr->dcp_dd_ihrsr);
	DBGFS_CREATE_RW_X32("dcp_dd_ihrfr", current_dentry,
			&ptr->dcp_dd_ihrfr);
	DBGFS_CREATE_RO_X32("dcp_dd_hasr", current_dentry,
			&ptr->dcp_dd_hasr);

	for (i = 0; i < QMAN_NUM_WQ_SW_DD_CFG_REGS; ++i) {
		sprintf(reg_name, "wq_sc_dd_cfg_%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->wq_sc_dd_cfg[i]);
	}
	for (i = 0; i < QMAN_NUM_WQ_POOL_DD_CFG_REGS; ++i) {
		sprintf(reg_name, "wq_pc_dd_cfg_%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->wq_pc_dd_cfg[i]);
	}
	for (i = 0; i < QMAN_NUM_WQ_DC0_DD_CFG_REGS; ++i) {
		sprintf(reg_name, "wq_dc0_dd_cfg_%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->wq_dc0_dd_cfg[i]);
	}
	for (i = 0; i < QMAN_NUM_WQ_DC1_DD_CFG_REGS; ++i) {
		sprintf(reg_name, "wq_dc1_dd_cfg_%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->wq_dc1_dd_cfg[i]);
	}
	DBGFS_CREATE_RW_X32("wq_dc2_dd_cfg_0", current_dentry,
			&ptr->wq_dc2_dd_cfg[0]);
	DBGFS_CREATE_RW_X32("wq_dc3_dd_cfg_0", current_dentry,
			&ptr->wq_dc3_dd_cfg[0]);
	DBGFS_CREATE_RW_X32("wq_dc4_dd_cfg_0", current_dentry,
			&ptr->wq_dc4_dd_cfg[0]);

	DBGFS_CREATE_RO_X32("qman_ip_rev_1", current_dentry,
			&ptr->qman_ip_rev_1);
	DBGFS_CREATE_RO_X32("qman_ip_rev_2", current_dentry,
			&ptr->qman_ip_rev_2);

	return 0;
}
