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

#include "dcsr_dpaa.h"

/* Driver Initialization Function */
int dcsr_dpaa_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct dpaa *ptr = (struct dpaa *)dev->mem_ptr;
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_DPAA_NAME);

	/* Debug status control */
	DBGFS_CREATE_RW_X32("dpehcr", current_dentry, &ptr->dpehcr);
	DBGFS_CREATE_RW_X32("dprcr", current_dentry, &ptr->dprcr);
	DBGFS_CREATE_RW_X32("qpehcr", current_dentry, &ptr->qpehcr);
	DBGFS_CREATE_RW_X32("qprcr", current_dentry, &ptr->qprcr);
	for (i = 0; i < DPAA_NO_OF_QMAN_SP; ++i) {
		sprintf(reg_name, "qsphsr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->qsphsr[i]);
	}
	for (i = 0; i < DPAA_NO_OF_QMAN_DCP; ++i) {
		sprintf(reg_name, "qdcphsr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->qdcphsr[i]);
	}
	DBGFS_CREATE_RW_X32("fmhsr0", current_dentry, &ptr->fmhsr0);
	DBGFS_CREATE_RW_X32("fmhsr1", current_dentry, &ptr->fmhsr1);
	for (i = 0; i < DPAA_NO_OF_QOER; ++i) {
		sprintf(reg_name, "dpqoer%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dpqoer[i]);
	}
	for (i = 0; i < DPAA_NO_OF_FOER; ++i) {
		sprintf(reg_name, "dpfoer%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dpfoer[i]);
	}
	for (i = 0; i < DPAA_NO_OF_EGCR; ++i) {
		sprintf(reg_name, "dpegcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dpegcr[i]);
	}
	for (i = 0; i < DPAA_NO_OF_GECR; ++i) {
		sprintf(reg_name, "dpgecr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dpgecr[i]);
	}
	for (i = 0; i < DPAA_NO_OF_GCR; ++i) {
		sprintf(reg_name, "dpgcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dpgcr[i]);
	}
	DBGFS_CREATE_RW_X32("dpepgcr", current_dentry, &ptr->dpepgcr);
	DBGFS_CREATE_RW_X32("dppescr", current_dentry, &ptr->dppescr);
	for (i = 0; i < DPAA_NO_OF_DPRESCR; ++i) {
		sprintf(reg_name, "dprescr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dprescr[i]);
	}
	DBGFS_CREATE_RW_X32("dptarm", current_dentry, &ptr->dptarm);
	DBGFS_CREATE_RW_X32("dptgcr", current_dentry, &ptr->dptgcr);
	DBGFS_CREATE_RW_X32("dptftcr1", current_dentry, &ptr->dptftcr1);
	DBGFS_CREATE_RW_X32("dptftcr2", current_dentry, &ptr->dptftcr2);
	DBGFS_CREATE_RW_X32("dpctscr", current_dentry, &ptr->dpctscr);
	DBGFS_CREATE_RW_X32("dpctdcr", current_dentry, &ptr->dpctdcr);
	DBGFS_CREATE_RW_X32("dpwmsk", current_dentry, &ptr->dpwmsk);

	return 0;
}
