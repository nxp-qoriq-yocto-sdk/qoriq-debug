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
	struct fman *ptr = (struct fman *)dev->mem_ptr[0];
	char flowchar[FMAN_NUM_DEBUG_FLOWS] = {'a', 'b', 'c'};
	char reg_name[DBFS_REG_NAME_LEN];

	/* FMAN id uses a 1 based index */
	dev->dbgfs_dir_index = dev->dt_idx + 1;

	CREATE_CURRENT_DBGFS_DIR_INDEXED(parent_dentry, dev,
					DEBUGFS_FMAN_NAME, dev->dbgfs_dir_index);

	/* BMI common */
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

	/* QMI common */
	DBGFS_CREATE_RW_X32("fmqm_gc", current_dentry,
			&ptr->ports.common_reg.fmqm_gc);
	DBGFS_CREATE_RW_X32("fmqm_etfc", current_dentry,
			&ptr->ports.common_reg.fmqm_etfc);
	DBGFS_CREATE_RW_X32("fmqm_dtfc", current_dentry,
			&ptr->ports.common_reg.fmqm_dtfc);
	DBGFS_CREATE_RW_X32("fmqm_dc0", current_dentry,
			&ptr->ports.common_reg.fmqm_dc0);
	DBGFS_CREATE_RW_X32("fmqm_dc1", current_dentry,
			&ptr->ports.common_reg.fmqm_dc1);
	DBGFS_CREATE_RW_X32("fmqm_dc2", current_dentry,
			&ptr->ports.common_reg.fmqm_dc2);
	DBGFS_CREATE_RW_X32("fmqm_dc3", current_dentry,
			&ptr->ports.common_reg.fmqm_dc3);
	DBGFS_CREATE_RW_X32("fmqm_dtrc", current_dentry,
			&ptr->ports.common_reg.fmqm_dtrc);
	DBGFS_CREATE_RW_X32("fmqm_efddd", current_dentry,
			&ptr->ports.common_reg.fmqm_efddd);
	for (i = 0; i < FMAN_NUM_DEBUG_FLOWS; ++i) {
		sprintf(reg_name, "fmqm_dtc%c1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].cfg1);
		sprintf(reg_name, "fmqm_dtv%c1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].val1);
		sprintf(reg_name, "fmqm_dtm%c1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].mask1);
		sprintf(reg_name, "fmqm_dtc%c", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].cnt);
		sprintf(reg_name, "fmqm_dtc%c2", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].cfg2);
		sprintf(reg_name, "fmqm_dtv%c2", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].val2);
		sprintf(reg_name, "fmqm_dtm%c2", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.common_reg.fmqm_dt[i].mask2);
	}

	/* FMan O/H Ports */
	for (i = 0; i < FMAN_NUM_OH_PORTS; ++i) {
		sprintf(reg_name, "fmbm_odcfg_%d_1", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.ophc[i].fmbm_odcfg_a);
		sprintf(reg_name, "fmbm_odcfg_%d_2", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.ophc[i].fmbm_odcfg_b);
		sprintf(reg_name, "fmbm_odcfg_%d_3", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.ophc[i].fmbm_odcfg_c);
	}

	/* FMan RX/TX Ports */
	for (i = 0; i < FMAN_NUM_TX_PORTS; ++i) {
		sprintf(reg_name, "fmbm_rdcfg_%d_1", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.rx[i].fmbm_rdcfg_a);
		sprintf(reg_name, "fmbm_rdcfg_%d_2", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.rx[i].fmbm_rdcfg_b);
		sprintf(reg_name, "fmbm_rdcfg_%d_3", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.rx[i].fmbm_rdcfg_c);

		sprintf(reg_name, "fmbm_tdcfg_%d_1", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.tx[i].fmbm_tdcfg_a);
		sprintf(reg_name, "fmbm_tdcfg_%d_2", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.tx[i].fmbm_tdcfg_b);
		sprintf(reg_name, "fmbm_tdcfg_%d_3", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ports.tx[i].fmbm_tdcfg_c);
	}

	/* FMan Policer */
	DBGFS_CREATE_RW_X32("fmpl_dtrcr", current_dentry, &ptr->policer.dtrcr);
	for (i = 0; i < FMAN_NUM_DEBUG_FLOWS; ++i) {
		sprintf(reg_name, "fmpl_f%cdbtcr0", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbtcr0);
		sprintf(reg_name, "fmpl_f%cdbvalr0", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbvalr0);
		sprintf(reg_name, "fmpl_f%cdbtmr0", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbtmr0);
		sprintf(reg_name, "fmpl_f%cdbtmc", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbtmc);
		sprintf(reg_name, "fmpl_f%cdbtcr1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbtcr1);
		sprintf(reg_name, "fmpl_f%cdbvalr1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbvalr1);
		sprintf(reg_name, "fmpl_f%cdbtmr1", flowchar[i]);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->policer.dt[i].dbtmr1);
	}

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
	DBGFS_CREATE_RW_X32("fmfp_tsc1", current_dentry, &ptr->fpm.tsc1);
	DBGFS_CREATE_RW_X32("fmfp_tsc2", current_dentry, &ptr->fpm.tsc2);
	DBGFS_CREATE_RO_X32("fmfp_tsp", current_dentry, &ptr->fpm.tsp);
	DBGFS_CREATE_RO_X32("fmfp_tsf", current_dentry, &ptr->fpm.tsf);
	DBGFS_CREATE_RO_X32("fmfp_ip_rev_1", current_dentry, &ptr->fpm.ip_rev1);
	DBGFS_CREATE_RO_X32("fmfp_ip_rev_2", current_dentry, &ptr->fpm.ip_rev2);
	DBGFS_CREATE_RW_X32("fmfp_cldc", current_dentry, &ptr->fpm.cldc);
	DBGFS_CREATE_RW_X32("fmfp_clfabc", current_dentry, &ptr->fpm.clfabc);
	DBGFS_CREATE_RW_X32("fmfp_clfcc", current_dentry, &ptr->fpm.clfcc);
	DBGFS_CREATE_RW_X32("fmfp_clfaval", current_dentry, &ptr->fpm.clfaval);
	DBGFS_CREATE_RW_X32("fmfp_clfbval", current_dentry, &ptr->fpm.clfbval);
	DBGFS_CREATE_RW_X32("fmfp_clfcval", current_dentry, &ptr->fpm.clfcval);
	DBGFS_CREATE_RW_X32("fmfp_clfamsk", current_dentry, &ptr->fpm.clfamsk);
	DBGFS_CREATE_RW_X32("fmfp_clfbmsk", current_dentry, &ptr->fpm.clfbmsk);
	DBGFS_CREATE_RW_X32("fmfp_clfcmsk", current_dentry, &ptr->fpm.clfcmsk);
	DBGFS_CREATE_RW_X32("fmfp_clfamc", current_dentry, &ptr->fpm.clfamc);
	DBGFS_CREATE_RW_X32("fmfp_clfbmc", current_dentry, &ptr->fpm.clfbmc);
	DBGFS_CREATE_RW_X32("fmfp_clfcmc", current_dentry, &ptr->fpm.clfcmc);

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
