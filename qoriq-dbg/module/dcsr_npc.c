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

#include "dcsr_npc.h"

/* Driver Initialization Function */
int dcsr_npc_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct npc *ptr = (struct npc *)dev->mem_ptr;

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_NPC_NAME);

	DBGFS_CREATE_RW_X32("ncr", current_dentry, &ptr->ncr);
	DBGFS_CREATE_RW_X32("nst", current_dentry, &ptr->nst);
	DBGFS_CREATE_RW_X32("sfr", current_dentry, &ptr->sfr);
	DBGFS_CREATE_RW_X32("mtfr", current_dentry, &ptr->mtfr);
	DBGFS_CREATE_RW_X32("mbalo", current_dentry, &ptr->mbalo);
	DBGFS_CREATE_RW_X32("mbahi", current_dentry, &ptr->mbahi);
	DBGFS_CREATE_RW_X32("mcr", current_dentry, &ptr->mcr);
	DBGFS_CREATE_RW_X32("stcr1", current_dentry, &ptr->stcr1);
	DBGFS_CREATE_RW_X32("stcr2", current_dentry, &ptr->stcr2);
	DBGFS_CREATE_RW_X32("stcr3", current_dentry, &ptr->stcr3);
	DBGFS_CREATE_RW_X32("stcr4", current_dentry, &ptr->stcr4);
	DBGFS_CREATE_RW_X32("cssr", current_dentry, &ptr->cssr);
	DBGFS_CREATE_RW_X32("cdr", current_dentry, &ptr->cdr);
	DBGFS_CREATE_RW_X32("mcsr1", current_dentry, &ptr->mcsr1);
	DBGFS_CREATE_RW_X32("mmar1hi", current_dentry, &ptr->mmar1hi);
	DBGFS_CREATE_RW_X32("mmar1lo", current_dentry, &ptr->mmar1lo);
	DBGFS_CREATE_RW_X32("mmdr1", current_dentry, &ptr->mmdr1);
	DBGFS_CREATE_RW_X32("mcsr2", current_dentry, &ptr->mcsr2);
	DBGFS_CREATE_RW_X32("mmar2hi", current_dentry, &ptr->mmar2hi);
	DBGFS_CREATE_RW_X32("mmar2lo", current_dentry, &ptr->mmar2lo);
	DBGFS_CREATE_RW_X32("mmdr2", current_dentry, &ptr->mmdr2);
	DBGFS_CREATE_RW_X32("mcsr3", current_dentry, &ptr->mcsr3);
	DBGFS_CREATE_RW_X32("mmar3hi", current_dentry, &ptr->mmar3hi);
	DBGFS_CREATE_RW_X32("mmar3lo", current_dentry, &ptr->mmar3lo);
	DBGFS_CREATE_RW_X32("mmdr3", current_dentry, &ptr->mmdr3);

	return 0;
}
