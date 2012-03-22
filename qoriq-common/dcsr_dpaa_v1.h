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

#ifndef DCSR_DPAA_V1_H
#define DCSR_DPAA_V1_H

#include "common.h"

/* Number of QMAN Softare Portals */
#define DPAA_NO_OF_QMAN_SP		10
/* Number of QMAN Direct Connect Portals */
#define DPAA_NO_OF_QMAN_DCP		4
/* Number of Queue Operation Event Registers */
#define DPAA_NO_OF_QOER			4
/* Number of Frame Operation Event Registers */
#define DPAA_NO_OF_FOER			8
/* Number of Event Generation Control Registers */
#define DPAA_NO_OF_EGCR			4
/* Number of Group Event Control Registers */
#define DPAA_NO_OF_GECR			4
/* Number of Group Configuration Registers */
#define DPAA_NO_OF_GCR			4
/* Number of Reference Event Selection Control Registers */
#define DPAA_NO_OF_DPRESCR		2

/* The Data Path Debug Register Memory Map */
struct dpaa {
	/* Data Path External Halt Control Register */
	u32 dpehcr;
	/* Data Path Resume Control Register */
	u32 dprcr;
	/* QMan Portal External Halt Control Register */
	u32 qpehcr;
	/* QMan Portal Resume Control Register */
	u32 qprcr;
	/* QMan Software Portal Halt Status Registers 0-9 */
	u32 qsphsr[DPAA_NO_OF_QMAN_SP];
	u32 reserved1[0x02];
	/* QMan Direct Connect Portal Halt Status Registers 0-3*/
	u32 qdcphsr[DPAA_NO_OF_QMAN_DCP];
	u32 reserved2[0x04];
	/* FMan 1 Halt Control Status Register */
	u32 fmhsr0;
	/* FMan 2 Halt Control Status Register */
	u32 fmhsr1;
	u32 reserved3[0x26];

	/* Data Path Queue Operation Event Registers 0 - 3 */
	u32 dpqoer[DPAA_NO_OF_QOER];
	u32 reserved4[0x04];
	/* Data Path Frame Operation Event Registers 0 - 7 */
	u32 dpfoer[DPAA_NO_OF_FOER];
	u32 reserved5[0x08];
	/* Data Path Event Generation Control Registers 0 - 3 */
	u32 dpegcr[DPAA_NO_OF_EGCR];
	u32 reserved6[0x04];
	/* Data Path Group Event Control Registers 0 - 3 */
	u32 dpgecr[DPAA_NO_OF_GECR];
	u32 reserved7[0x04];
	/* Data Path Group Configuration Registers 0 - 3 */
	u32 dpgcr[DPAA_NO_OF_GCR];
	u32 reserved8[0x04];
	/* Data Path Event Port General Control Register */
	u32 dpepgcr;
	/* Data Path Performance Event Selection Control Register */
	u32 dppescr;
	/* Data Path Reference Event Selection Control Register 1, 2 */
	u32 dprescr[DPAA_NO_OF_DPRESCR];
	u32 reserved9[0x0C];

	/* Data Path Trace Armed Register */
	u32 dptarm;
	/* Data Path Trace General Control Register */
	u32 dptgcr;
	/* Data Path Trace Filter Trigger Control Register 1 */
	u32 dptftcr1;
	/* Data Path Trace Filter Trigger Control Register 2 */
	u32 dptftcr2;
	/* Data Path Circuit Trace Static Control Register */
	u32 dpctscr;
	/* Data Path Circuit Trace Dynamic Control Register */
	u32 dpctdcr;
	u32 reserved10[0x02];
	/* Data Path Watchpoint Mask Control Register */
	u32 dpwmsk;
	u32 reserved11[0x377];
} PACKED;
CTASSERT(sizeof(struct dpaa) == 0x1000);

#endif  /* DCSR_DPAA_V1_H */
