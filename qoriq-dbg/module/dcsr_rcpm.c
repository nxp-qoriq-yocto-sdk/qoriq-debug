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

#include "dcsr_rcpm.h"

/* Driver Initialization Function */
int dcsr_rcpm_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct rcpm *ptr = (struct rcpm *)dev->mem_ptr[0];
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_RCPM_NAME);

	for (i = 0; i < RCPM_NO_OF_CORE_GROUPS; ++i) {
		sprintf(reg_name, "cgcr%dl", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cgcr[i].cgcrl);
	}
	for (i = 0; i < RCPM_NO_OF_SCU; ++i) {
		sprintf(reg_name, "cgacre%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cgacre[i]);
		sprintf(reg_name, "dacre%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dacre[i]);
	}
	for (i = 0; i < RCPM_NO_OF_CATTACR; ++i) {
		sprintf(reg_name, "csttacr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->csttacr[i]);
	}

	return 0;
}

/* Driver Initialization Function */
int dcsr_rcpm_v2_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct rcpm_v2 *ptr = (struct rcpm_v2 *)dev->mem_ptr[0];
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_RCPM_NAME);

	for (i = 0; i < RCPM_v2_NO_OF_CORE_GROUPS; ++i) {
		sprintf(reg_name, "cg%dcr0", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cgcr[i].cgcrl);
	}
	for (i = 0; i < RCPM_v2_NO_OF_CONTROL_ELEM; ++i) {
		sprintf(reg_name, "cesre%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cesre[i]);
		sprintf(reg_name, "cesrd%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cesrd[i]);
	}
	for (i = 0; i < RCPM_v2_NO_OF_EPU_EVENTS; ++i) {
		sprintf(reg_name, "cgacre%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cgacre[i]);
		sprintf(reg_name, "dacre%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dacre[i]);
	}
	for (i = 0; i < RCPM_v2_NO_OF_DEV_EVENTS; ++i) {
		sprintf(reg_name, "cgacrd%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->cgacrd[i]);
		sprintf(reg_name, "dacrd%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->dacrd[i]);
	}
	for (i = 0; i < RCPM_v2_NO_OF_CATTACR; ++i) {
		sprintf(reg_name, "csttacr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->csttacr[i]);
	}

	/* Run Control */
	DBGFS_CREATE_RO_X32("twrssr02", current_dentry,
			&ptr->twrssr02);
	DBGFS_CREATE_RO_X32("twrssr01", current_dentry,
			&ptr->twrssr01);
	DBGFS_CREATE_RO_X32("dcdsr0", current_dentry,
			&ptr->dcdsr0);
	for (i = 0; i < RCPM_v2_NO_OF_CONTROL_ELEM; ++i) {
		sprintf(reg_name, "cdsr%d", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry,
				&ptr->cdsr[i]);
	}

	return 0;
}
