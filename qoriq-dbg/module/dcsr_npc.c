/*
 * Copyright (C) 2010, 2011, 2012, 2013 Freescale Semiconductor, Inc.
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
#include "dcsr_npc_v1.h"
#include "dcsr_npc_v2.h"
#include "dcsr_npc_trace.h"

/* Debugfs Initialization Function */
int dcsr_npc_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct npc_v1 *ptr = (struct npc_v1 *)dev->mem_ptr[0];

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

	dcsr_npc_trace_init(parent_dentry, dev);

	return 0;
}

/* Gen 2 Debug IP Central-NPC */
int dcsr_cnpc_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct npc_v2 *ptr = (struct npc_v2 *)dev->mem_ptr[0];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_CNPC_NAME);

	DBGFS_CREATE_RW_X32("ncr", current_dentry, &ptr->ncr);
	DBGFS_CREATE_RW_X32("nst", current_dentry, &ptr->nst);
	DBGFS_CREATE_RW_X32("tbsr", current_dentry, &ptr->tbsr);
	DBGFS_CREATE_RW_X32("oqcr", current_dentry, &ptr->oqcr);
	DBGFS_CREATE_RW_X32("tscr", current_dentry, &ptr->tscr);
	DBGFS_CREATE_RW_X32("fcr", current_dentry, &ptr->fcr);
	DBGFS_CREATE_RW_X32("sfr1", current_dentry, &ptr->sfr[0]);
	DBGFS_CREATE_RW_X32("sfr2", current_dentry, &ptr->sfr[1]);
	DBGFS_CREATE_RW_X32("sfr3", current_dentry, &ptr->sfr[2]);
	DBGFS_CREATE_RW_X32("sfr4", current_dentry, &ptr->sfr[3]);
	DBGFS_CREATE_RW_X32("mtfr1", current_dentry, &ptr->mtfr[0]);
	DBGFS_CREATE_RW_X32("mtfr2", current_dentry, &ptr->mtfr[1]);
	DBGFS_CREATE_RW_X32("mtfr3", current_dentry, &ptr->mtfr[2]);
	DBGFS_CREATE_RW_X32("mtfr4", current_dentry, &ptr->mtfr[3]);
	DBGFS_CREATE_RW_X32("cdr", current_dentry, &ptr->cdr);
	DBGFS_CREATE_RW_X32("cdsr", current_dentry, &ptr->cdsr);
	DBGFS_CREATE_RW_X32("cscr", current_dentry, &ptr->cscr);
	DBGFS_CREATE_RW_X32("cssr", current_dentry, &ptr->cssr);
	DBGFS_CREATE_RW_X32("stcr1", current_dentry, &ptr->stcr[0]);
	DBGFS_CREATE_RW_X32("stcr2", current_dentry, &ptr->stcr[1]);
	DBGFS_CREATE_RW_X32("stcr3", current_dentry, &ptr->stcr[2]);
	DBGFS_CREATE_RW_X32("stcr4", current_dentry, &ptr->stcr[3]);
	DBGFS_CREATE_RW_X32("mbalo", current_dentry, &ptr->mbalo);
	DBGFS_CREATE_RW_X32("mbahi", current_dentry, &ptr->mbahi);
	DBGFS_CREATE_RW_X32("mcr", current_dentry, &ptr->mcr);
	DBGFS_CREATE_RW_X32("mpxfr", current_dentry, &ptr->mpxfr);
	DBGFS_CREATE_RW_X32("apbalo", current_dentry, &ptr->apbalo);
	DBGFS_CREATE_RW_X32("apbahi", current_dentry, &ptr->apbahi);
	DBGFS_CREATE_RW_X32("apcr", current_dentry, &ptr->apcr);
	DBGFS_CREATE_RW_X32("apxfr", current_dentry, &ptr->apxfr);
	DBGFS_CREATE_RW_X32("wmkr1", current_dentry, &ptr->wmkr[0]);
	DBGFS_CREATE_RW_X32("wmkr2", current_dentry, &ptr->wmkr[1]);
	DBGFS_CREATE_RW_X32("wmkr3", current_dentry, &ptr->wmkr[2]);
	DBGFS_CREATE_RW_X32("wmkr4", current_dentry, &ptr->wmkr[3]);
	DBGFS_CREATE_RW_X32("sbcsr", current_dentry, &ptr->sbcsr);
	DBGFS_CREATE_RO_X32("sbrar", current_dentry, &ptr->sbrar);
	DBGFS_CREATE_RW_X32("mccr", current_dentry, &ptr->mccr);
	DBGFS_CREATE_RW_X32("mcsr1", current_dentry, &ptr->mma[0].mcsr);
	DBGFS_CREATE_RW_X32("mmar1hi", current_dentry, &ptr->mma[0].mmarhi);
	DBGFS_CREATE_RW_X32("mmar1lo", current_dentry, &ptr->mma[0].mmarlo);
	DBGFS_CREATE_RW_X32("mmdr1", current_dentry, &ptr->mma[0].mmdr);
	DBGFS_CREATE_RW_X32("mcsr2", current_dentry, &ptr->mma[1].mcsr);
	DBGFS_CREATE_RW_X32("mmar2hi", current_dentry, &ptr->mma[1].mmarhi);
	DBGFS_CREATE_RW_X32("mmar2lo", current_dentry, &ptr->mma[1].mmarlo);
	DBGFS_CREATE_RW_X32("mmdr2", current_dentry, &ptr->mma[1].mmdr);
	DBGFS_CREATE_RW_X32("mcsr3", current_dentry, &ptr->mma[2].mcsr);
	DBGFS_CREATE_RW_X32("mmar3hi", current_dentry, &ptr->mma[2].mmarhi);
	DBGFS_CREATE_RW_X32("mmar3lo", current_dentry, &ptr->mma[2].mmarlo);
	DBGFS_CREATE_RW_X32("mmdr3", current_dentry, &ptr->mma[2].mmdr);

	return 0;
}

/* Gen 2 Debug IP Satellite-NPC */
int dcsr_snpc_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	struct dentry *current_dentry;
	struct dentry *de;
	struct snpc_v2 *ptr = (struct snpc_v2 *)dev->mem_ptr[0];

	/* SNPC id uses a 1 based index */
	dev->dbgfs_dir_index = dev->dt_idx + 1;

	CREATE_CURRENT_DBGFS_DIR_INDEXED(parent_dentry, dev,
					DEBUGFS_SNPC_NAME, dev->dbgfs_dir_index);

	DBGFS_CREATE_RW_X32("ncr", current_dentry, &ptr->ncr);
	DBGFS_CREATE_RW_X32("nst", current_dentry, &ptr->nst);
	DBGFS_CREATE_RW_X32("tbsr", current_dentry, &ptr->tbsr);
	DBGFS_CREATE_RW_X32("oqcr", current_dentry, &ptr->oqcr);
	DBGFS_CREATE_RW_X32("tscr", current_dentry, &ptr->tscr);
	DBGFS_CREATE_RW_X32("fcr", current_dentry, &ptr->fcr);
	DBGFS_CREATE_RW_X32("sfr1", current_dentry, &ptr->sfr[0]);
	DBGFS_CREATE_RW_X32("sfr2", current_dentry, &ptr->sfr[1]);
	DBGFS_CREATE_RW_X32("sfr3", current_dentry, &ptr->sfr[2]);
	DBGFS_CREATE_RW_X32("sfr4", current_dentry, &ptr->sfr[3]);
	DBGFS_CREATE_RW_X32("mtfr1", current_dentry, &ptr->mtfr[0]);
	DBGFS_CREATE_RW_X32("mtfr2", current_dentry, &ptr->mtfr[1]);
	DBGFS_CREATE_RW_X32("mtfr3", current_dentry, &ptr->mtfr[2]);
	DBGFS_CREATE_RW_X32("mtfr4", current_dentry, &ptr->mtfr[3]);
	DBGFS_CREATE_RW_X32("cdr", current_dentry, &ptr->cdr);
	DBGFS_CREATE_RW_X32("cdsr", current_dentry, &ptr->cdsr);
	DBGFS_CREATE_RW_X32("cscr", current_dentry, &ptr->cscr);
	DBGFS_CREATE_RW_X32("cssr", current_dentry, &ptr->cssr);
	DBGFS_CREATE_RW_X32("stcr1", current_dentry, &ptr->stcr[0]);
	DBGFS_CREATE_RW_X32("stcr2", current_dentry, &ptr->stcr[1]);
	DBGFS_CREATE_RW_X32("stcr3", current_dentry, &ptr->stcr[2]);
	DBGFS_CREATE_RW_X32("stcr4", current_dentry, &ptr->stcr[3]);
	DBGFS_CREATE_RW_X32("wmkr1", current_dentry, &ptr->wmkr[0]);
	DBGFS_CREATE_RW_X32("wmkr2", current_dentry, &ptr->wmkr[1]);
	DBGFS_CREATE_RW_X32("wmkr3", current_dentry, &ptr->wmkr[2]);
	DBGFS_CREATE_RW_X32("wmkr4", current_dentry, &ptr->wmkr[3]);
	DBGFS_CREATE_RW_X32("sbcsr", current_dentry, &ptr->sbcsr);
	DBGFS_CREATE_RO_X32("sbrar", current_dentry, &ptr->sbrar);

	return 0;
}
