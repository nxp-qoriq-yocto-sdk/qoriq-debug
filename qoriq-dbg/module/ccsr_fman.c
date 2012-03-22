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

#include "ccsr_fman.h"

/* Driver Initialization Function */
int ccsr_fman_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i, x, j, k;
	struct dentry *current_dentry;
	struct dentry *de;
	struct fman *ptr = (struct fman *)dev->mem_ptr;
	char flowchar[FMAN_NUM_DEBUG_FLOWS] = {'a', 'b', 'c'};
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR_INDEXED(parent_dentry, dev,
					DEBUGFS_FMAN_NAME);

	/* BMI, QMI, Parser */
	DBGFS_CREATE_RW_X32("fmbm_gde", current_dentry,
			&ptr->ports.common_reg.fmbm_gde);
	for (i = 0; i < FMAN_NUM_DEBUG_FLOWS; ++i) {
		sprintf(reg_name, "fmbm_dtc_%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmbm_dtc[i]);
		for (x = 0; x < FMAN_NUM_REGS_PER_FRAME; ++x) {
			sprintf(reg_name, "fmbm_dcv_%d_%d", x+1, i+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->ports.common_reg.fmbm_dcv[i][x]);
			sprintf(reg_name, "fmbm_dcm_%d_%d", x+1, i+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->ports.common_reg.fmbm_dcm[i][x]);
		}
	}
	/* FMan Policer */
	DBGFS_CREATE_RW_X32("fmpl_dtrcr", current_dentry, &ptr->policer.dtrcr);
	DBGFS_CREATE_RW_X32("fmpl_fadbtcr", current_dentry,
			&ptr->policer.fadbtcr0);
	/* FMan Key Generator */
	DBGFS_CREATE_RW_X32("fmkg_tpc", current_dentry, &ptr->key_gen.tpc);
	DBGFS_CREATE_RW_X32("fmkg_serc", current_dentry, &ptr->key_gen.serc);
	DBGFS_CREATE_RW_X32("fmkg_dcr", current_dentry, &ptr->key_gen.dcr);
	for (j = 0; j < FMAN_NUM_DEBUG_FLOWS; ++j) {
		sprintf(reg_name, "fmkg_d%dtc", j+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->key_gen.dJtc[j]);
		for (k = 0; k < FMAN_NUM_DEBUG_EVENT_TRAPS; ++k) {
			sprintf(reg_name, "fmkg_d%dt%dcr", j+1, k+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->key_gen.dJtK[j][k].cr);
			sprintf(reg_name, "fmkg_d%dt%dvr", j+1, k+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->key_gen.dJtK[j][k].vr);
			sprintf(reg_name, "fmkg_d%dt%dmr", j+1, k+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->key_gen.dJtK[j][k].mr);
		}
	}
	/* FMan Frame Processing Manager */
	DBGFS_CREATE_RW_X32("fmfp_cldc", current_dentry, &ptr->fpm.cldc);
	DBGFS_CREATE_RW_X32("fmfp_clfabc", current_dentry, &ptr->fpm.clfabc);

	/* FMan Parser */
	DBGFS_CREATE_RW_X32("fmpr_pdc", current_dentry, &ptr->parser.fmpr_pdc);
	for (i = 0; i < FMAN_NUM_DEBUG_FLOWS; ++i) {
		sprintf(reg_name, "fmpr_pd%ctes", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->parser.fmpr_pdtes[i]);

		for (x = 0; x < FMAN_NUM_DEBUG_TRAPS; ++x) {
			sprintf(reg_name, "fmpr_pd%ct%dc", flowchar[i], x);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->parser.debug_flow_trap[i][x].fmpr_pdtc);
			sprintf(reg_name, "fmpr_pd%ct%dv", flowchar[i], x);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->parser.debug_flow_trap[i][x].fmpr_pdtv);
			sprintf(reg_name, "fmpr_pd%ct%dm", flowchar[i], x);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->parser.debug_flow_trap[i][x].fmpr_pdtm);
		}
	}

	return 0;
}
