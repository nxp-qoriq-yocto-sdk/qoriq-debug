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

#ifndef DBG_SPR_H
#define DBG_SPR_H

#include "linux/types.h"
#include "asm/reg_fsl_emb.h"
#include "common.h"

#define SPRN_IAC5	565	/* Instr Addr Compare */
#define SPRN_IAC6	566	/* Instr Addr Compare */
#define SPRN_IAC7	567	/* Instr Addr Compare */
#define SPRN_IAC8	568	/* Instr Addr Compare */
#define SPRN_DEVENT	975	/* Debug Event Select Register */
#define SPRN_DDAM	576	/* Debug Data Acquisition Message Register */
#define SPRN_NPIDR	517	/* Nexus Process ID Register */
#define SPRN_NSPD	983	/* Nexus SPR Data Register */
#define SPRN_NSPC	984	/* Nexus SPR Config Register */
#define SPRN_DBRR0	700	/* Debug Resource Request Register */
#define SPRN_EDBRAC0	638	/* Debug Resource Request Register */
#define SPRN_DBCR5	564	/* Debug Control Register 5 */

/* define the SPRs to be used */
enum SPR {
	SPR_DBSR,
	SPR_DBCR0,
	SPR_DBCR1,
	SPR_DBCR2,
	SPR_DBCR4,
#if defined(CORE_E6500)
	SPR_DBCR5,
	SPR_DBRR0,
	SPR_EDBRAC0,
#endif
	SPR_IAC1,
	SPR_IAC2,
#if defined(CORE_E6500)
	SPR_IAC3,
	SPR_IAC4,
	SPR_IAC5,
	SPR_IAC6,
	SPR_IAC7,
	SPR_IAC8,
#endif
	SPR_DAC1,
	SPR_DAC2,
	SPR_NSPD,
	SPR_NSPC,
	SPR_DEVENT,
	SPR_DDAM,
	SPR_NPIDR,
	SPR_MAX /* number of SPRs */
};

/* Define a data group that contains the following */
struct spr_register {
	int core;		/* Core number */
	int spr;		/* SPR number  */
	int size64;		/* >0 SPR is 64bit, default 0 */
#ifdef CONFIG_PPC64
	u64 val;		/* value to read/write */
#else
	u32 val;		/* value to read/write */
#endif
};

/* initialize an array of spr_register */
void spr_reg_init(struct spr_register *regs, int core_id);

/* define the file ops for the SPRs */
extern const struct file_operations spr_fops;

#endif /* DBG_SPR_H */
