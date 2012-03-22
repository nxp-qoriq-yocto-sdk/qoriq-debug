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

#ifndef DBG_SPR_H
#define DBG_SPR_H

#include "linux/types.h"

/* define the number of Special Purpose Registers per core */
#define NUM_SPRS_PER_CORE 12

//define SPRN_DBCR4	563	/* Debug Control Register 4 */
#define SPRN_DEVENT	975	/* Debug Event Select Register */
#define SPRN_DDAM	576	/* Debug Data Acquisition Message Register */
#define SPRN_NPIDR	517	/* Nexus Process ID Register */

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

/* define the file ops for the SPRs */
extern const struct file_operations spr_fops;

/* Listing of all SPRs per core */
extern const struct spr_register spr_data[];

#endif /* DBG_SPR_H */
