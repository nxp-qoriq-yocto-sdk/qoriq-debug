/*
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
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

#include "ccsr_bman.h"

/* Driver Initialization Function */
int ccsr_bman_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct bman *ptr = (struct bman *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev, DEBUGFS_BMAN_NAME);

	for (i = 0; i < BMAN_NUM_POOLS; ++i) {
		sprintf(reg_name, "bman_pool%d_swdet", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_pool_swdet[i]);
		sprintf(reg_name, "bman_pool%d_hwdet", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_pool_hwdet[i]);
		sprintf(reg_name, "bman_pool%d_swdxt", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_pool_swdxt[i]);
		sprintf(reg_name, "bman_pool%d_hwdxt", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_pool_hwdxt[i]);
		sprintf(reg_name, "bman_pool%d_sdcnt", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->bman_pool_sdcnt[i]);
		sprintf(reg_name, "bman_pool%d_hdcnt", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->bman_pool_hdcnt[i]);
		sprintf(reg_name, "bman_pool%d_content", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->bman_pool_content[i]);
		sprintf(reg_name, "bman_pool%d_hdptr", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->bman_pool_hdptr[i]);
	}

	DBGFS_CREATE_RO_X32("fbpr_fpc", current_dentry,
			&ptr->fbpr_fpc);
	DBGFS_CREATE_RW_X32("fbpr_fp_lwit", current_dentry,
			&ptr->fbpr_fp_lwit);
	DBGFS_CREATE_RO_X32("fbpr_hdptr", current_dentry,
			&ptr->fbpr_hdptr);

	for (i = 0; i < BMAN_NUM_PERF_MONITORS; ++i) {
		sprintf(reg_name, "bman_cmd_pm%d_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_cmd_pm_cfg[i]);
		sprintf(reg_name, "bman_fl_pm%d_cfg", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->bman_fl_pm_cfg[i]);
	}

	DBGFS_CREATE_RW_X32("bman_escr", current_dentry,
			&ptr->bman_escr);
	DBGFS_CREATE_RO_X32("bman_esir", current_dentry,
			&ptr->bman_esir);
	DBGFS_CREATE_RO_X32("bman_eadr", current_dentry,
			&ptr->bman_eadr);

	for (i = 0; i < BMAN_NUM_DATA_ERROR_WORDS; ++i) {
		sprintf(reg_name, "bman_edata%d", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->bman_edata[i]);
	}

	DBGFS_CREATE_RW_X32("bman_sbet", current_dentry,
			&ptr->bman_sbet);
	DBGFS_CREATE_RW_X32("bman_efcr", current_dentry,
			&ptr->bman_efcr);
	DBGFS_CREATE_RO_X32("bman_efar", current_dentry,
			&ptr->bman_efar);
	DBGFS_CREATE_RO_X32("bman_sbec0", current_dentry,
			&ptr->bman_sbec0);
	DBGFS_CREATE_RO_X32("bman_sbec1", current_dentry,
			&ptr->bman_sbec1);

	DBGFS_CREATE_RO_X32("bman_ip_rev_1", current_dentry,
			&ptr->bman_ip_rev_1);
	DBGFS_CREATE_RO_X32("bman_ip_rev_2", current_dentry,
			&ptr->bman_ip_rev_2);
	DBGFS_CREATE_RW_X32("fbpr_bare", current_dentry,
			&ptr->fbpr_bare);
	DBGFS_CREATE_RW_X32("fbpr_bar", current_dentry,
			&ptr->fbpr_bar);
	DBGFS_CREATE_RW_X32("fbpr_ar", current_dentry,
			&ptr->fbpr_ar);
	DBGFS_CREATE_RO_X32("bman_srcidr", current_dentry,
			&ptr->bman_srcidr);
	DBGFS_CREATE_RW_X32("bman_liodnr", current_dentry,
			&ptr->bman_liodnr);

	DBGFS_CREATE_RW_X32("bman_err_isr", current_dentry,
			&ptr->bman_err_isr);
	DBGFS_CREATE_RW_X32("bman_err_ier", current_dentry,
			&ptr->bman_err_ier);
	DBGFS_CREATE_RW_X32("bman_err_isdr", current_dentry,
			&ptr->bman_err_isdr);
	DBGFS_CREATE_RW_X32("bman_err_iir", current_dentry,
			&ptr->bman_err_iir);
	DBGFS_CREATE_RW_X32("bman_err_ifr", current_dentry,
			&ptr->bman_err_ifr);

	return 0;
}
