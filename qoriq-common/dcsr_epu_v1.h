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
#ifndef DCSR_EPU_V1_H
#define DCSR_EPU_V1_H

#include "common.h"

/* Number of counting units in the EPU */
#define EPU_NO_OF_COUNTERS		32
#define EPU_NO_OF_SCU_EVENTS		16
#define EPU_NO_OF_COUNTER_GROUPS	4
#define EPU_NO_OF_EVENT_GROUPS		3
#define EPU_NO_PROC_INTRPTS		2

/* control block for SCU */
struct scu_ctrl {
	u32 epsmcr;
	u32 reserved;
};

/* structure defines the memory map of the EPU control block */
struct epu {
	/* Global Control Register */
	u32 epgcr;
	u8 reserved1[0x10-0x04];
	/* Event Status Register */
	u32 epesr;
	u8 reserved2[0x20-0x14];
	/* Interrupt Status Registers */
	u32 episr[EPU_NO_PROC_INTRPTS];
	u8 reserved2a[0x30-0x28];
	/* Counter Interrupt Status Register */
	u32 epctrisr;
	u8 reserved3[0x40-0x34];
	/* Counter Capture Status Register */
	u32 epctrcsr;
	u8 reserved4[0x50-0x44];
	/* EVT Pin Direction Control Register */
	u32 epepdcr;
	u8 reserved6[0x100-0x54];
	/* Event Processor Input Mux Control Register */
	u32 epimcr[EPU_NO_OF_COUNTERS];
	u8 reserved7[0x200-0x180];
	/* Event Processor SCU MUX Control Registers */
	struct scu_ctrl scu_ctrl[EPU_NO_OF_SCU_EVENTS];
	u8 reserved8[0x300-0x280];
	/* Event Processor Event Control Registers */
	u32 epecr[EPU_NO_OF_SCU_EVENTS];
	u8 reserved9[0x400-0x340];
	/* Event Processor Action Control Registers */
	u32 epacr[EPU_NO_OF_SCU_EVENTS];
	u8 reserved10[0x480-0x440];
	/* Event Processor Group Action Control Registers */
	u32 epgacr[EPU_NO_OF_SCU_EVENTS];
	u8 reserved11[0x540-0x4c0];
	/* Event Processor Counter Group Configuration Registers */
	u32 epctrgcr[EPU_NO_OF_COUNTER_GROUPS];
	u8 reserved12[0x580-0x550];
	/* Event Processor Event Group Configuration Registers */
	u32 epegcr[EPU_NO_OF_EVENT_GROUPS];
	u8 reserved13[0x600-0x58c];
	u8 reserved15[0x800-0x600];
	/* Event Processor Counter Control Registers */
	u32 epccr[EPU_NO_OF_COUNTERS];
	u8 reserved16[0x900-0x880];
	/* Event Processor Counter Compare Registers */
	u32 epcmpr[EPU_NO_OF_COUNTERS];
	u8 reserved17[0xA00-0x980];
	/* Event Processor Counter Registers */
	u32 epctr[EPU_NO_OF_COUNTERS];
	u8 reserved18[0xB00-0xA80];
	/* Event Processor Counter Capture Registers */
	u32 epcapr[EPU_NO_OF_COUNTERS];
	u8 reserved19[0xF00-0xB80];
	u8 reserved20[0x1000-0xF00];
} PACKED;
CTASSERT(sizeof(struct epu) == 0x1000);

#define EPU_EPGCR_GCE_SHIFT		0x1f
#define EPU_EPGCR_GCE_MASK		0x80000000

#define EPU_EPIMCR_ISEL_MASK		0xfc000000
#define	EPU_EPIMCR_ISEL_SHIFT		0x1a
#define	EPU_EPIMCR_ISEL_END		0x40

#define EPU_EPISR_EV15_MASK		0x00010000
#define EPU_EPISR_EV15_SHIFT		16

#define EPU_EPSMCR_CONTROL_ISEL0_MASK	0x7f000000
#define EPU_EPSMCR_CONTROL_ISEL0_SHIFT	0x18
#define EPU_EPSMCR_CONTROL_ISEL1_MASK	0x007f0000
#define EPU_EPSMCR_CONTROL_ISEL1_SHIFT	0x10
#define EPU_EPSMCR_CONTROL_ISEL2_MASK	0x00007f00
#define EPU_EPSMCR_CONTROL_ISEL2_SHIFT	0x8
#define EPU_EPSMCR_CONTROL_ISEL3_MASK	0x0000007f
#define EPU_EPSMCR_CONTROL_ISEL3_SHIFT	0x0

#define EPU_EPECR_CONTROL_IC0_MASK	0xc0000000
#define EPU_EPECR_CONTROL_IC0_SHIFT	0x1e
#define EPU_EPECR_CONTROL_IC1_MASK	0x30000000
#define EPU_EPECR_CONTROL_IC1_SHIFT	0x1c
#define EPU_EPECR_CONTROL_IC2_MASK	0xc000000
#define EPU_EPECR_CONTROL_IC2_SHIFT	0x1a
#define EPU_EPECR_CONTROL_IC3_MASK	0x3000000
#define EPU_EPECR_CONTROL_IC3_SHIFT	0x18
#define EPU_EPECR_CONTROL_IIE0_MASK	0x8000
#define EPU_EPECR_CONTROL_IIE0_SHIFT	0xf
#define EPU_EPECR_CONTROL_IIE1_MASK	0x4000
#define EPU_EPECR_CONTROL_IIE1_SHIFT	0xe
#define EPU_EPECR_CONTROL_IIE2_MASK	0x2000
#define EPU_EPECR_CONTROL_IIE2_SHIFT	0xd
#define EPU_EPECR_CONTROL_IIE3_MASK	0x1000
#define EPU_EPECR_CONTROL_IIE3_SHIFT	0xc
#define EPU_EPECR_CONTROL_CIC_MASK	0xc0
#define EPU_EPECR_CONTROL_CIC_SHIFT	0x6
#define EPU_EPECR_CONTROL_ICE_MASK	0x20
#define EPU_EPECR_CONTROL_ICE_SHIFT	0x5
#define EPU_EPECR_CONTROL_EDE_MASK	0x10
#define EPU_EPECR_CONTROL_EDE_SHIFT	0x4
#define EPU_EPECR_CONTROL_SSE_MASK	0x4
#define EPU_EPECR_CONTROL_SSE_SHIFT	0x2
#define EPU_EPECR_CONTROL_STS_MASK	0x1
#define EPU_EPECR_CONTROL_STS_SHIFT	0x0

#define EPU_EPACR_CONTROL_IC_MASK	0x60000000
#define EPU_EPACR_CONTROL_IC_SHIFT	0x1d
#define EPU_EPACR_CONTROL_DC_MASK	0x18000000
#define EPU_EPACR_CONTROL_DC_SHIFT	0x1b
#define EPU_EPACR_CONTROL_MC_MASK	0x6000000
#define EPU_EPACR_CONTROL_MC_SHIFT	0x19
#define EPU_EPACR_CONTROL_CTC_MASK	0x1000000
#define EPU_EPACR_CONTROL_CTC_SHIFT	0x18
#define EPU_EPACR_CONTROL_WTC_MASK	0x800000
#define EPU_EPACR_CONTROL_WTC_SHIFT	0x17
#define EPU_EPACR_CONTROL_PXIE_MASK	0x10000
#define EPU_EPACR_CONTROL_PXIE_SHIFT	0x10
#define EPU_EPACR_CONTROL_PXC0_MASK	0x8000
#define EPU_EPACR_CONTROL_PXC0_SHIFT	0xf
#define EPU_EPACR_CONTROL_PXC1_MASK	0x4000
#define EPU_EPACR_CONTROL_PXC1_SHIFT	0xe
#define EPU_EPACR_CONTROL_PXC2_MASK	0x2000
#define EPU_EPACR_CONTROL_PXC2_SHIFT	0xd
#define EPU_EPACR_CONTROL_PXC3_MASK	0x1000
#define EPU_EPACR_CONTROL_PXC3_SHIFT	0xc
#define EPU_EPACR_CONTROL_PXC4_MASK	0x800
#define EPU_EPACR_CONTROL_PXC4_SHIFT	0xb
#define EPU_EPACR_CONTROL_PXC5_MASK	0x400
#define EPU_EPACR_CONTROL_PXC5_SHIFT	0xa
#define EPU_EPACR_CONTROL_PXC6_MASK	0x200
#define EPU_EPACR_CONTROL_PXC6_SHIFT	0x9
#define EPU_EPACR_CONTROL_PXC7_MASK	0x100
#define EPU_EPACR_CONTROL_PXC7_SHIFT	0x8
#define EPU_EPACR_CONTROL_PXC8_MASK	0x80
#define EPU_EPACR_CONTROL_PXC8_SHIFT	0x7
#define EPU_EPACR_CONTROL_PXC9_MASK	0x40
#define EPU_EPACR_CONTROL_PXC9_SHIFT	0x6
#define EPU_EPACR_CONTROL_PXC10_MASK	0x20
#define EPU_EPACR_CONTROL_PXC10_SHIFT	0x5
#define EPU_EPACR_CONTROL_PXC11_MASK	0x10
#define EPU_EPACR_CONTROL_PXC11_SHIFT	0x4

#define EPU_EPCCR_CONTROL_EN_MASK      0x80000000
#define EPU_EPCCR_CONTROL_EN_SHIFT     0x1f
#define EPU_EPCCR_CONTROL_EDE_MASK     0x40000000
#define EPU_EPCCR_CONTROL_EDE_SHIFT    0x1e
#define EPU_EPCCR_CONTROL_ISEL_MASK    0x30000000
#define EPU_EPCCR_CONTROL_ISEL_SHIFT   0x1c
#define EPU_EPCCR_CONTROL_GEV_MASK     0x2000000
#define EPU_EPCCR_CONTROL_GEV_SHIFT    0x19
#define EPU_EPCCR_CONTROL_LEV_MASK     0x800000
#define EPU_EPCCR_CONTROL_LEV_SHIFT    0x17
#define EPU_EPCCR_CONTROL_AC_MASK      0xf0000
#define EPU_EPCCR_CONTROL_AC_SHIFT     0x10

#define EPU_EPGACR_CONTROL_CTSTARTC_MASK      0x70000
#define EPU_EPGACR_CONTROL_CTSTARTC_SHIFT     0x10
#define EPU_EPGACR_CONTROL_CTSTOPC_MASK       0x7000
#define EPU_EPGACR_CONTROL_CTSTOPC_SHIFT      0xc
#define EPU_EPGACR_CONTROL_CTRC_MASK          0x700
#define EPU_EPGACR_CONTROL_CTRC_SHIFT         0x8
#define EPU_EPGACR_CONTROL_CTCC_MASK          0x70
#define EPU_EPGACR_CONTROL_CTCC_SHIFT         0x4
#define EPU_EPGACR_CONTROL_ERC_MASK           0x7
#define EPU_EPGACR_CONTROL_ERC_SHIFT          0x0

#endif /* DCSR_EPU_V1_H */
