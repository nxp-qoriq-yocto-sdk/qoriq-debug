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

#ifndef DCSR_CORENET_V1_H
#define DCSR_CORENET_V1_H

#include "common.h"

/* Number of reference event selection registers */
#define CNDC_NO_REF_EVENTS			4
/* Number of CNDC Event Comparators */
#define CNDC_NO_EVENT_COMPARATORS		4
/* Number of CNDC comparator debug event control registers */
#define CNDC_NO_COMPARATORS_CONTROL_REGS	2
/* Number of CNDC Address Comparators */
#define CNDC_NO_ADDRESS_COMPARATORS		4
/* Number of CNDC Event Comparators */
#define CNDC_NO_TRANS_COMPARATORS		4

/* size of cndc section 1 struct */
#define CNDC1_STRUCT_SIZE		0x1000
/* size of cndc section 2 struct */
#define CNDC2_STRUCT_SIZE		0x1000

/* CNDC Compare Debug Event Control Register */
struct cndc_comp {
	u32 cc_decr[CNDC_NO_COMPARATORS_CONTROL_REGS];
	u32 reserved[0x02];
} PACKED;
CTASSERT(sizeof(struct cndc_comp) == 0x10);

/* CNDC memory map section 1 in the DCSR block */
struct cndc_1 {
	u32 reserved1[0x18];
	u32 ctarm;
	u32 ctcr1;
	u32 reserved2[0x06];
	u32 cwmsk;
	u32 reserved7[0x2];
	u32 ctscr;
	u32 reserved3[0x1c];

	struct cndc_comp comp[CNDC_NO_EVENT_COMPARATORS];
	u32 reserved4[0x1B0];

	u32 cpmsr1;
	u32 reserved5[0x03];

	u32 cprescr[CNDC_NO_REF_EVENTS];
	u32 reserved6[0x1F8];
} PACKED;
CTASSERT(sizeof(struct cndc_1) == CNDC1_STRUCT_SIZE);

/* Debug address compare registers */
struct cndc_addr_comp {
	u32 cdac_h;
	u32 cdac_l;
};

/* CNDC memory map section 2 */
struct cndc_2 {
	u32 reserved1[0x3C0];
	/* CoreNetCCM_AP Debug Control Registers */
	u32 cdbcr0; /* enables CDACs */
	u32 cdbcr1; /* CDBCR1 - config for CDACs 1/2*/
	u32 cdbcr2; /* CDBCR2 - config for CDACs 3/4*/
	u32 cdbcr3; /* data compare */

	/* Debug Address Compare registers */
	struct cndc_addr_comp addr_comp[CNDC_NO_ADDRESS_COMPARATORS];

	/*Transaction Attribute Compare Registers */
	u32 ctac[CNDC_NO_TRANS_COMPARATORS];
	u32 reserved2[0x4];

	/* Data Value Compare Registers */
	u32 cdvchh;
	u32 cdvchl;
	u32 cdvclh;
	u32 cdvcll;
	u32 reserved3[0x8];
	u32 perfmon_enable;
	u32 reserved4[0x3];

	/* Performance Monitor Control Register */
	u32 cdpmcr;
	u32 reserved5[0x1B];
} PACKED;
CTASSERT(sizeof(struct cndc_2) == CNDC2_STRUCT_SIZE);

#endif  /* DCSR_CORENET_V1_H */
