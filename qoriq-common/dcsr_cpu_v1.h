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

#ifndef DCSR_CPU_V1_H
#define DCSR_CPU_V1_H

#include "common.h"

/* size of core_proxy struct */
#define CORE_PROXY_STRUCT_SIZE	0x1000

/* number of PM capture counters */
#define NUM_CORE_PM_COUNTERS	4

struct core_proxy {
	/* Debug Status */
	/* Processor Run Status Register (PRSR) */
	u32 prsr;
	u8 reserved1[0x4];
	/* Machine State Register */
	u32 msr;
	/* External Debug Status Register (EDBSR0) */
	u32 edbsr0;
	/* External Debug Status Register (EDBSR1) */
	u32 edbsr1;
	/* External Debug Exception Syndrome Register */
	u32 edesr;
	/* Processor Version Register */
	u32 pvr;
	/* External Debug Status Register Mask 0 */
	u32 edbsrmsk0;
	u8  reserved2[0x8];
	/* Program Counter Capture Register High */
	u32 pcch;
	/* Program Counter Capture Register Low */
	u32 pccl;
	/* Perfmon Capture Count Register 0-3 */
	u32 pmcc[NUM_CORE_PM_COUNTERS];
	u8  reserved3[0xC0];

	/* Debug Control */
	/* External Debug Control Register 0 (EDBCR0) */
	u32 edbcr0;
	u8  reserved4[0xFC];
	u8  reserved5[0x100];
	u8  reserved8[0x100];

	/* Nexus */
	u8  reserved9[0x8];
	/* Nexus Development Control Register 1 (DC1) */
	u32 dc1;
	/* Nexus Development Control Register 2 (DC2) */
	u32 dc2;
	u8  reserved10[0x4];
	/* Nexus Development Control Register 4 (DC4) */
	u32 dc4;
	u8  reserved11[0x14];
	/* Watchpoint Trigger Register 1 (WT1) */
	u32 wt1;
	u8  reserved12[0x28];
	/* Watchpoint Mask Register (WMSK) */
	u32 wmsk;
	/* Nexus Overrun Control Register (OVCR) */
	u32 ovcr;
	u8  reserved13[0xA0];
	u8  reserved14[0x100];
	u8  reserved15[0x100];
	u8  reserved16[0x900];
} PACKED;
CTASSERT(sizeof(struct core_proxy) == CORE_PROXY_STRUCT_SIZE);

#define CPU_DC1_OTS_MASK		0x01000000
#define CPU_DC1_OTS_SHIFT		24
#define CPU_DC1_POTD_MASK		0x00004000
#define CPU_DC1_POTD_SHIFT		14
#define CPU_DC1_TSEN_MASK		0x00003000
#define CPU_DC1_TSEN_SHIFT		12
#define CPU_DC1_TSEN_EN_MASK		0x00002000
#define CPU_DC1_TSEN_EN_SHIFT		13
#define CPU_DC1_TSEN_CRS_MASK		0x00001000
#define CPU_DC1_TSEN_CRS_SHIFT		12
#define CPU_DC1_EOC_MASK		0x00000C00
#define CPU_DC1_EOC_SHIFT		10
#define CPU_DC1_EIC_MASK		0x00000300
#define CPU_DC1_EIC_SHIFT		8
#define CPU_DC1_TM_MASK			0x0000003f
#define CPU_DC1_TM_SHIFT		0
#define CPU_DC1_TM_OWN_MASK		0x00000001
#define CPU_DC1_TM_OWN_SHIFT		0
#define CPU_DC1_TM_DAT_MASK		0x00000002
#define CPU_DC1_TM_DAT_SHIFT		1
#define CPU_DC1_TM_PGM_MASK		0x00000004
#define CPU_DC1_TM_PGM_SHIFT		2
#define CPU_DC1_TM_WTC_MASK		0x00000008
#define CPU_DC1_TM_WTC_SHIFT		3
#define CPU_DC1_TM_DQM_MASK		0x00000020
#define CPU_DC1_TM_DQM_SHIFT		5
#define CPU_DC4_PTMARK_MASK		0x80000000
#define CPU_DC4_PTMARK_SHIFT		31
#define CPU_DC4_EVCDM_MASK		0x000007FF
#define CPU_DC4_EVCDM_SHIFT		0
#define CPU_DC2_EWC4_MASK		0xf0000000
#define CPU_DC2_EWC4_SHIFT		28
#define CPU_DC2_EWC3_MASK		0x0f000000
#define CPU_DC2_EWC3_SHIFT		24
#define CPU_DC2_EWC2_MASK		0x00f00000
#define CPU_DC2_EWC2_SHIFT		20
#define CPU_DC2_EWC1_MASK		0x000f0000
#define CPU_DC2_EWC1_SHIFT		16
#define CPU_DC2_EWC0_MASK		0x00003fff
#define CPU_DC2_EWC0_SHIFT		0x0
#define CPU_WT1_PTS_MASK		0xf0000000
#define CPU_WT1_PTS_SHIFT		28
#define CPU_WT1_PTE_MASK		0x0f000000
#define CPU_WT1_PTE_SHIFT		24
#define CPU_WT1_DTS_MASK		0x00f00000
#define CPU_WT1_DTS_SHIFT		20
#define CPU_WT1_DTE_MASK		0x000f0000
#define CPU_WT1_DTE_SHIFT		16
#define CPU_WMSK_WEM_MASK		0x00003fff
#define CPU_WMSK_WEM_SHIFT		0
#define CPU_OVCR_STEN_MASK		0x00000001
#define CPU_OVCR_STEN_SHIFT		0x0
#define CPU_OVCR_SPTHOLD_MASK		0x30000000
#define CPU_OVCR_SPTHOLD_SHIFT		0x1c
#define CPU_OVCR_SPEN_MASK		0x003f0000
#define CPU_OVCR_SPEN_SHIFT		0x10
#define CPU_OVCR_STTHOLD_MASK		0x00003000
#define CPU_OVCR_STTHOLD_SHIFT		0xc

#endif  /* DBG_CPU_V1_H */
