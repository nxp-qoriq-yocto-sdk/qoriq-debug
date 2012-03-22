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

#include "dcsr_nxc.h"

/* Driver Initialization Function */
int dcsr_nxc_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i, j;
	struct dentry *current_dentry;
	struct dentry *de;
	struct nxc *ptr = (struct nxc *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_NXC_NAME);

	DBGFS_CREATE_RW_X32("nxccr0", current_dentry, &ptr->nxccr0);
	DBGFS_CREATE_RW_X32("fccfg0", current_dentry, &ptr->fccfg0);
	DBGFS_CREATE_RW_X32("fccfg1", current_dentry, &ptr->fccfg1);
	DBGFS_CREATE_RW_X32("fccfg2", current_dentry, &ptr->fccfg2);
	DBGFS_CREATE_RW_X32("fccfg3", current_dentry, &ptr->fccfg3);
	DBGFS_CREATE_RW_X32("fccfg4", current_dentry, &ptr->fccfg4);
	for (i = 0; i < NXC_NO_OF_HITGENS; ++i) {
		sprintf(reg_name, "hg%dcfg0", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].hgcfg0);
		sprintf(reg_name, "cmpAValHi%d_msb", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpavalhi_msb);
		sprintf(reg_name, "cmpAValHi%d_lsb", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpavalhi_lsb);
		sprintf(reg_name, "cmpAValMskLo%d_msb", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpavalmsklo_msb);
		sprintf(reg_name, "cmpAValMskLo%d_lsb", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpavalmsklo_lsb);
		sprintf(reg_name, "cmpBValHiLo%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpbvalhilo);
		sprintf(reg_name, "cmpBValMsk%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpbvalmsk);
		sprintf(reg_name, "cmpBVector%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpbvector);
		sprintf(reg_name, "cmpCVal%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpcval);
		sprintf(reg_name, "cmpCValMsk%d", i+1);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->hit_gen[i].cmpcvalmsk);
		for (j = 0; j < NXC_HG_NO_OF_MASK_UNITS; ++j) {
			sprintf(reg_name, "hg%dcfg%d", i+1, j+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->hit_gen[i].hgmsk_cfg[j]);
				sprintf(reg_name, "hg%decr%d", i+1, j+1);
			DBGFS_CREATE_RW_X32(reg_name, current_dentry,
					&ptr->hit_gen[i].hgecr[j]);
			}
	}

	return 0;
}
