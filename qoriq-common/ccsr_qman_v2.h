/*
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
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

#ifndef CCSR_QMAN_V2_H
#define CCSR_QMAN_V2_H

#include "common.h"

/* number of software portals */
#define QMAN_V2_SOFT_PORTALS	50
/* number of software DD portals */
#define QMAN_V2_SOFT_DD_PORTALS	 3
/* number of direct connect portals */
#define QMAN_V2_DIRECT_PORTALS	6 /* maybe 7?*/
/* Number of Work Queue S/W Debug Configuration Registers */
#define QMAN_V2_NUM_WQ_SW_DD_CFG_REGS	QMAN_V2_SOFT_PORTALS/2
/* Number of Work Queue Pool Debug Configuration Registers */
#define QMAN_V2_NUM_WQ_POOL_DD_CFG_REGS	 8
/* Number of Work Queue Direct Connect[n] Debug Configuration Registers */
#define QMAN_V2_NUM_WQ_DC0_DD_CFG_REGS	8
#define QMAN_V2_NUM_WQ_DC1_DD_CFG_REGS	8
#define QMAN_V2_NUM_WQ_DC2_DD_CFG_REGS	1
#define QMAN_V2_NUM_WQ_DC3_DD_CFG_REGS	1
#define QMAN_V2_NUM_WQ_DC4_DD_CFG_REGS	1
#define QMAN_V2_NUM_WQ_DC5_DD_CFG_REGS	1

/* QMan Software Portal Configuration */
struct qman_v2_soft_portal_config {
	/* QMan Software Portal LIO Configuration */
	u32 lio_cfg;
	/* QMan Software Portal IO Configuration */
	u32 io_cfg;
	/* reserved */
	u32 reserved;
	/* Software Portal Dynamic Debug Configuration */
	u32 dd_cfg;
} PACKED;

/* QMan Direct Connect Portal (DCP) Configuration */
struct qman_v2_direct_portal_config {
	/* DCP Configuration */
	u32 dcp_cfg;
	/* DCP Dynamic Debug Configuration */
	u32 dd_cfg;
	/* DCP Dequeue Latency Monitor Configuration */
	u32 dlm_cfg;
	/* DCP Dequeue Latency Monitor Average */
	u32 dlm_avg;
} PACKED;

/* QMan Software Portal Dynamic Debug */
struct qman_v2_soft_portal_dd {
	/* QMan SP DD Internal Halt Request Status */
	u32 qcsp_dd_ihrsr;
	/* QMan SP DD Internal Halt Request Force */
	u32 qcsp_dd_ihrfr;
	/* QMan SP DD Halt Ack Status */
	u32 qcsp_dd_hasr;
	u32 reserved;
} PACKED;

/* QMAN configuration registers */
struct qman_v2 {
	u8 reserved1[0x200];

	/* Dynamic Debug (DD) Configuration Registers */
	u32 qman_dd_cfg;
	u8  reserved2[0x220-0x204];
	u32 dcp_dd_ihrsr;
	u32 dcp_dd_ihrfr;
	u32 dcp_dd_hasr;

	u8  reserved3[0x240-0x22c];

	/* QMan Software Portal Dynamic debug */
	struct qman_v2_soft_portal_dd
		soft_portal_dd[QMAN_V2_SOFT_DD_PORTALS];

	u8  reserved4[0x300-0x270];

	/* Direct Connect Portal (DCP) Configuration Registers */
	struct qman_v2_direct_portal_config
		direct_portal_config[QMAN_V2_DIRECT_PORTALS];

	u8  reserved5[0x680-0x360];

	/* WQ Channel Pool Dynamic Debug Config n */
	u32 wq_pc_dd_cfg[QMAN_V2_NUM_WQ_POOL_DD_CFG_REGS];
	u8  reserved6[0x6c0-0x6a0];
	/* WQ Direct Connect Port 0 Dynamic Debug Config n */
	u32 wq_dc0_dd_cfg[QMAN_V2_NUM_WQ_DC0_DD_CFG_REGS];
	u8  reserved7[0x700-0x6e0];
	/* WQ Direct Connect Port 1 Dynamic Debug Config n */
	u32 wq_dc1_dd_cfg[QMAN_V2_NUM_WQ_DC1_DD_CFG_REGS];
	u8  reserved8[0x740-0x720];
	/* WQ Direct Connect Port 2 Dynamic Debug Config */
	u32 wq_dc2_dd_cfg[QMAN_V2_NUM_WQ_DC2_DD_CFG_REGS];
	u8  reserved9[0x760-0x744];
	/* WQ Direct Connect Port 3 Dynamic Debug Config */
	u32 wq_dc3_dd_cfg[QMAN_V2_NUM_WQ_DC3_DD_CFG_REGS];
	u8  reserved10[0x780-0x764];
	/* WQ Direct Connect Port 4 Dynamic Debug Config */
	u32 wq_dc4_dd_cfg[QMAN_V2_NUM_WQ_DC4_DD_CFG_REGS];
	u8  reserved11[0x7a0-0x784];
	/* WQ Direct Connect Port 5 Dynamic Debug Config */
	u32 wq_dc5_dd_cfg[QMAN_V2_NUM_WQ_DC5_DD_CFG_REGS];

	u8  reserved12[0xbf8-0x7a4];

	u32 qman_ip_rev_1; /* QM IP Block Revision 1 register */
	u32 qman_ip_rev_2; /* QM IP Block Revision 2 register */

	u8 reserved13[0x1000-0xc00];

	/* QMan Software Portal Configuration */
	struct qman_v2_soft_portal_config
		soft_portal_cfg[QMAN_V2_SOFT_PORTALS];

	u8  reserved14[0x1e00-0x1320];

	/* WQ S/W Channel Dynamic Debug Config n */
	u32 wq_sc_dd_cfg[QMAN_V2_NUM_WQ_SW_DD_CFG_REGS];

	u8  reserved15[0x2000-0x1e64];
} PACKED;
/* check addresses and size */
CTASSERT(offsetof(struct qman_v2, qman_dd_cfg) == 0x200);
CTASSERT(offsetof(struct qman_v2, soft_portal_dd[0].qcsp_dd_ihrsr) == 0x240);
CTASSERT(offsetof(struct qman_v2, direct_portal_config[0].dcp_cfg) == 0x300);
CTASSERT(offsetof(struct qman_v2, wq_pc_dd_cfg[0]) == 0x680);
CTASSERT(offsetof(struct qman_v2, qman_ip_rev_1) == 0xbf8);
CTASSERT(offsetof(struct qman_v2, soft_portal_cfg[0].lio_cfg) == 0x1000);
CTASSERT(offsetof(struct qman_v2, wq_sc_dd_cfg[0]) == 0x1e00);
CTASSERT(offsetof(struct qman_v2, wq_sc_dd_cfg[24]) == 0x1e60);
CTASSERT(sizeof(struct qman_v2) == 0x2000);

#endif /* CCSR_QMAN_V2_H */
