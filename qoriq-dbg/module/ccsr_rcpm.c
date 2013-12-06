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

#include "ccsr_rcpm.h"

/* Driver Initialization Function */
int ccsr_rcpm2_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct rcpm_2 *ptr = (struct rcpm_2 *)dev->mem_ptr[0];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_RCPM2_NAME);

	/* registers numbered from high address*/
	DBGFS_CREATE_RO_X32("tph10sr", current_dentry,
			&ptr->tph10sr[3]);
	DBGFS_CREATE_RW_X32("tph10setr", current_dentry,
			&ptr->tph10setr[3]);
	DBGFS_CREATE_RW_X32("tph10clrr", current_dentry,
			&ptr->tph10clrr[3]);
	DBGFS_CREATE_RW_X32("tph10psr", current_dentry,
			&ptr->tph10psr[3]);
	DBGFS_CREATE_RO_X32("twaitsr", current_dentry,
			&ptr->twaitsr[3]);
	DBGFS_CREATE_RO_X32("pcph15sr", current_dentry,
			&ptr->pcph15sr);
	DBGFS_CREATE_RW_X32("pcph15setr", current_dentry,
			&ptr->pcph15setr);
	DBGFS_CREATE_RW_X32("pcph15clrr", current_dentry,
			&ptr->pcph15clrr);
	DBGFS_CREATE_RO_X32("pcph15psr", current_dentry,
			&ptr->pcph15psr);
	DBGFS_CREATE_RO_X32("pcph20sr", current_dentry,
			&ptr->pcph20sr);
	DBGFS_CREATE_RW_X32("pcph20setr", current_dentry,
			&ptr->pcph20setr);
	DBGFS_CREATE_RW_X32("pcph20clrr", current_dentry,
			&ptr->pcph20clrr);
	DBGFS_CREATE_RO_X32("pcph20psr", current_dentry,
			&ptr->pcph20psr);
	DBGFS_CREATE_RO_X32("pcpw20sr", current_dentry,
			&ptr->pcpw20sr);
	DBGFS_CREATE_RO_X32("pcph30sr", current_dentry,
			&ptr->pcph30sr);
	DBGFS_CREATE_RW_X32("pcph30setr", current_dentry,
			&ptr->pcph30setr);
	DBGFS_CREATE_RW_X32("pcph30clrr", current_dentry,
			&ptr->pcph30clrr);
	DBGFS_CREATE_RO_X32("pcph30psr", current_dentry,
			&ptr->pcph30psr);

	return 0;
}
