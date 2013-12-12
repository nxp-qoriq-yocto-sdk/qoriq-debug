/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
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

#include "ccsr_devcfg.h"

/* Driver Initialization Function */
int ccsr_devcfg_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	return ccsr_devcfg_v2_init(parent_dentry, dev);
}

/* Driver Initialization Function */
int ccsr_devcfg_v2_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct device_cfg_v2 *ptr = (struct device_cfg_v2 *)dev->mem_ptr[0];
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev, DEBUGFS_DEVCFG_NAME);

	DBGFS_CREATE_RO_X32("pvr", current_dentry, &ptr->pvr);
	DBGFS_CREATE_RO_X32("svr", current_dentry, &ptr->svr);

	for (i = 0; i < DEVCFG_NUM_RCW_WORDS; ++i) {
		sprintf(reg_name, "rcw%d", i);
		DBGFS_CREATE_RO_X32(reg_name, current_dentry, &ptr->rcw[i]);
	}

	return 0;
}
