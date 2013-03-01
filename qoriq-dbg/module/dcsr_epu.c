/*
 * Copyright (C) 2010, 2011, 2012 Freescale Semiconductor, Inc.
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

#include "dcsr_epu.h"

/* Driver Initialization Functions */
int dcsr_epu_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct epu *ptr = (struct epu *)dev->mem_ptr[0];
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_EPU_NAME);

	DBGFS_CREATE_RW_X32("epgcr", current_dentry, &ptr->epgcr);
	DBGFS_CREATE_RW_X32("epesr", current_dentry, &ptr->epesr);
	DBGFS_CREATE_RW_X32("epctrisr", current_dentry, &ptr->epctrisr);
	DBGFS_CREATE_RW_X32("epctrcsr", current_dentry, &ptr->epctrcsr);

	for (i = 0; i < EPU_MAX_PROC_INTRPTS; ++i) {
		sprintf(reg_name, "%s%d", "episr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->episr[i]);
	}
	for (i = 0; i < EPU_NO_OF_COUNTERS; ++i) {
		sprintf(reg_name, "%s%d", "epimcr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epimcr[i]);
		sprintf(reg_name, "%s%d", "epccr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epccr[i]);
		sprintf(reg_name, "%s%d", "epcmpr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epcmpr[i]);
		sprintf(reg_name, "%s%d", "epctr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epctr[i]);
		sprintf(reg_name, "%s%d", "epcapr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epcapr[i]);
	}
	for (i = 0; i < EPU_NO_OF_SCU_EVENTS; ++i) {
		sprintf(reg_name, "%s%d", "epsmcr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->scu_ctrl[i].epsmcr);
		sprintf(reg_name, "%s%d", "epecr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epecr[i]);
		sprintf(reg_name, "%s%d", "epacr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epacr[i]);
		sprintf(reg_name, "%s%d", "epgacr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epgacr[i]);
	}
	for (i = 0; i < EPU_NO_OF_COUNTER_GROUPS; ++i) {
		sprintf(reg_name, "epctrgcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->epctrgcr[i]);
	}
	for (i = 0; i < EPU_NO_OF_EVENT_GROUPS; ++i) {
		sprintf(reg_name, "epegcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epegcr[i]);
	}

#ifdef GEN2_DEBUG
#ifdef GEN2_REV2_DEBUG
	DBGFS_CREATE_RW_X32("epxtrigcr", current_dentry, &ptr->epxtrigcr);
	for (i = 0; i < EPU_NO_EVT_PIN_REGS; ++i) {
		sprintf(reg_name, "%s%d", "epevtcr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epevtcr[i]);
	}
	DBGFS_CREATE_RW_X32("epfsmsr0", current_dentry, &ptr->epfsmsr0);
	for (i = 0; i < EPU_NO_FSM_STATES; ++i) {
		sprintf(reg_name, "%s%d", "epfsmcmpr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epfsmcmpr[i]);
		sprintf(reg_name, "%s%d", "epfsmcr", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->epfsmcr[i]);
	}
	/* registers numbered in decreasing order within memory */
	for (i = 0; i < EPU_NO_RESRV_REGS; ++i) {
		sprintf(reg_name, "%s%d", "eprsv", EPU_NO_RESRV_REGS-1-i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->eprsv[i]);
	}
	for (i = 0; i < EPU_NO_SEMA_REGS; ++i) {
		sprintf(reg_name, "%s%d", "ephsr", EPU_NO_SEMA_REGS-1-i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry, &ptr->ephsr[i]);
	}
#endif
#else
	DBGFS_CREATE_RW_X32("epepdcr", current_dentry, &ptr->epepdcr);
#endif

	return 0;
}
