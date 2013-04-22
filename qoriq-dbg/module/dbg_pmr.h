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

#ifndef DBG_PERFMON_H
#define DBG_PERFMON_H

#include "linux/types.h"
#include "asm/reg_fsl_emb.h"
#include "common.h"

#ifndef PMRN_PMC4
#define PMRN_PMC4	0x014	/* Performance Monitor Counter 4 */
#endif

#ifndef PMRN_PMC5
#define PMRN_PMC5	0x015	/* Performance Monitor Counter 5 */
#endif

#ifndef PMRN_PMLCA4
#define PMRN_PMLCA4	0x094	/* PM Local Control A4 */
#endif

#ifndef PMRN_PMLCA5
#define PMRN_PMLCA5	0x095	/* PM Local Control A5 */
#endif

#ifndef PMRN_PMLCB4
#define PMRN_PMLCB4	0x114	/* PM Local Control B4 */
#endif

#ifndef PMRN_PMLCB5
#define PMRN_PMLCB5	0x115	/* PM Local Control B5 */
#endif


/* define the PMRs to be used */
enum PMR {
	PMR_PMC0,
	PMR_PMC1,
	PMR_PMC2,
	PMR_PMC3,
	PMR_PMC4,
	PMR_PMC5,
	PMR_PMLCA0,
	PMR_PMLCA1,
	PMR_PMLCA2,
	PMR_PMLCA3,
	PMR_PMLCA4,
	PMR_PMLCA5,
	PMR_PMLCB0,
	PMR_PMLCB1,
	PMR_PMLCB2,
	PMR_PMLCB3,
	PMR_PMLCB4,
	PMR_PMLCB5,
	PMR_PMGC0,
	PMR_MAX /* number of PMRs */
};

/* Define a data group that contains the following */
struct pmr_register {
	int core;		/* Core number */
	int pmr;		/* PMR number */
	u32 val;		/* value to read/write */
};

/* initialize an array of pmr_register */
void pmr_reg_init(struct pmr_register *regs, int core_id);

/* define the file ops for the PerfMon registers */
extern const struct file_operations perfmon_fops;

#endif /* DBG_PERFMON_H */
