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

#ifndef CCSR_FMAN_V1_H
#define CCSR_FMAN_V1_H

#include "common.h"

/* FMAN Constants */
#define FMAN_NUM_DEBUG_FLOWS	3
#define FMAN_NUM_DEBUG_TRAPS	4
#define FMAN_NUM_DEBUG_EVENT_TRAPS	5
#define FMAN_NUM_REGS_PER_FRAME	4

/* Fman common registers */
struct fman_common {
	/* BMI registers common for all ports */
	u8 reserved1[0x90];
	/* FMBM Debug Trap Counters */
	u32 fmbm_dtc[FMAN_NUM_DEBUG_FLOWS];
	u32 reserved2;
	/*FMBM Debug Compare Value */
	u32 fmbm_dcv[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_REGS_PER_FRAME];
	/*FMBM Debug Compare Mask */
	u32 fmbm_dcm[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_REGS_PER_FRAME];
	/* FMBM_GDE Global Debug Enable */
	u32 fmbm_gde;
	u8 reserved7[0x2FC];

	/* QMI registers common for all ports */
	u8 reserved3[0x80];
	/* FMQM_DTRC Debug Trace Configuration Register */
	u32 fmqm_dtrc;
	/* FMQM_EFDDD Enqueue Frame Descriptor Dynamic Debug */
	u32 fmqm_efddd;
	u8 reserved4[8];
	/* FMQM_DTCA1 Debug Trap Configuration A1 Register */
	u32 fmqm_dtca1;
	u8 reserved5[0x36C];
	u8 reserved6[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_common) == 0x1000);

/* Fman Rx port */
struct fman_rx {
	/* BMI registers */
	u8 reserved1[0x300];
	/* FMBM_RDCFG Rx Debug Configuration Flow A */
	u32 fmbm_rdcfg_a;
	/* FMBM_RDCFG Rx Debug Configuration Flow B */
	u32 fmbm_rdcfg_b;
	/* FMBM_RDCFG Rx Debug Configuration Flow C */
	u32 fmbm_rdcfg_c;
	u8 reserved2[0xF4];

	/* QMI registers */
	u8 reserved3[0x400];

	/* reserved */
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_rx) == 0x1000);

/* Fman Tx port */
struct fman_tx {
	/* BMI registers */
	u8 reserved1[0x300];
	/* FMBM_TDCFG Tx Debug Configuration Flow A */
	u32 fmbm_tdcfg_a;
	/* FMBM_TDCFG Tx Debug Configuration Flow B */
	u32 fmbm_tdcfg_b;
	/* FMBM_TDCFG Tx Debug Configuration Flow C */
	u32 fmbm_tdcfg_c;
	u8 reserved2[0xF4];
	/* QMI registers */
	u8 reserved3[0x400];
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_tx) == 0x1000);

/* Fman O/H port (Offline Parsing/Host Command) */
struct fman_oh {
	u8 reserved1[0x300];
	/* FMBM_ODCFG O/H Debug Configuration Flow A */
	u32 fmbm_odcfg_a;
	/* FMBM_ODCFG O/H Debug Configuration Flow B */
	u32 fmbm_odcfg_b;
	/* FMBM_ODCFG O/H Debug Configuration Flow C */
	u32 fmbm_odcfg_c;
	u8 reserved2[0xF4];
	u8 reserved3[0x400];
	u8 reserved4[0x800];
} PACKED;
CTASSERT(sizeof(struct fman_oh) == 0x1000);

/* Fman Rx and Tx ports */
struct fmports {
	/* BMI Common Registers */
	struct fman_common common_reg;
	/* (Offline Parsing/Host Command) Port Registers */
	struct fman_oh ophc[7];
	/* 1G Rx */
	struct fman_rx rx_1G[4];
	u8 reserved1[0x4000];
	/* 10G Rx */
	struct fman_rx rx_10G;
	u8 reserved2[0x17000];
	/* 1G Rx */
	struct fman_tx tx_1G[4];
	u8 reserved3[0x4000];
	/* 10G Tx */
	struct fman_tx tx_10G;
	u8 reserved4[0xF000];
} PACKED;
CTASSERT(sizeof(struct fmports) == 0x40000);

/* FMan policer */
struct fmpl {
	u8 reserved1[0x10C];
	/* FMan Policer Debug Trace Configuration Register */
	u32 dtrcr;
	/* FMan Policer Flow A Debug Trap Configuration Register 0 */
	u32 fadbtcr0;
	u8 reserved2[0xEEC];
} PACKED;
CTASSERT(sizeof(struct fmpl) == 0x1000);

/* FMan key generator  Flow Trap Configuration, Value and Mask*/
struct fmkg_flowtrap {
	/* Configuration Register*/
	u32 cr;
	/* Value Register*/
	u32 vr;
	/* Mask Register*/
	u32 mr;
	u8 reserved1[0x4];
} PACKED;

/* FMan key generator  */
struct fmkg {
	u8 reserved1[0x28];
	/* KeyGen Total Packet Counter */
	u32 tpc;
	/* KeyGen Soft Error Capture */
	u32 serc;
	u8 reserved2[0x1d0];
	/* KeyGen Debug Control Register */
	u32 dcr;
	/* KeyGen Debug J Trap Counter */
	u32 dJtc[FMAN_NUM_DEBUG_FLOWS];
	/* KeyGen Debug Flow J Trap K Configuration Register  */
	struct fmkg_flowtrap dJtK[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_DEBUG_EVENT_TRAPS];
	u8 reserved3[0xd00];
} PACKED;
CTASSERT(sizeof(struct fmkg) == 0x1000);

/* Frame Processing Manager */
struct fpm {
	u8 reserved1[0xD0];
	/* FMFP_CLDC FMan Classifier Debug Control */
	u32 cldc;
	u8 reserved2[0x12C];
	/* FMFP_CLFABC FMan Classifier Flow AB Control */
	u32 clfabc;
	u8 reserved3[0xDFC];
} PACKED;
CTASSERT(sizeof(struct fpm) == 0x1000);

/* FMan parser Debug flow Configuration, value and mask registers */
struct fmpr_debug_flow_trap {
	/* FMPR_PDxTnC Parser Debug Flow x Trap n Configuration Register */
	u32 fmpr_pdtc;
	/* FMPR_PDxTnV Parser Debug Flow x Trap n Value Register */
	u32 fmpr_pdtv;
	/* FMPR_PDxTnM Parser Debug Flow x Trap n Mask Register */
	u32 fmpr_pdtm;
};
/* FMan parser */
struct fmpr {
	u8 reserved1[0x8ec];
	/* FMPR_PDxTES Parser Debug Flow x Trap event Statistic Register */
	u32 fmpr_pdtes[FMAN_NUM_DEBUG_FLOWS];
	u8 reserved2[0x8];
	/* FMPR_PDC Parser Debug Control Register */
	u32 fmpr_pdc;
	/* FMPR_PDxTn[CVM] Parser Debug Flow x Trap n Registers */
	struct fmpr_debug_flow_trap
		debug_flow_trap[FMAN_NUM_DEBUG_FLOWS][FMAN_NUM_DEBUG_TRAPS];
	u8 reserved3[0x66c];
} PACKED;
CTASSERT(sizeof(struct fmpr) == 0x1000);

/* Memory mapping for FMan */
struct fman {
	u8 reserved1[0x80000];
	/* BMI, QMI, Parser */
	struct fmports ports;
	/* FMan Policer */
	struct fmpl policer;
	/* FMan Key Generator */
	struct fmkg key_gen;
	u8 reserved2[0x1000];
	/* FMan Frame Processing Manager */
	struct fpm fpm;
	u8 reserved3[0x3000];
	/* FMan Parser */
	struct fmpr parser;
	u8 reserved4[0x38000];
} PACKED;
CTASSERT(sizeof(struct fman) == 0x00100000);

#endif /* CCSR_FMAN_V1_H */
