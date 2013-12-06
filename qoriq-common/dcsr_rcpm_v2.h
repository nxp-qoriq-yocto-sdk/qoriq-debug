/*
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
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

#ifndef DCSR_RCPM_V2_H
#define DCSR_RCPM_V2_H

#include "common.h"

#define RCPM_v2_STRUCT_SIZE		0x2000
#define RCPM_v2_NO_OF_CONTROL_ELEM	24
#define RCPM_v2_NO_OF_CORE_GROUPS	12
#define RCPM_v2_NO_OF_DEV_EVENTS	10
#define RCPM_v2_NO_OF_EPU_EVENTS	16
#define RCPM_v2_NO_OF_CATTACR		3

/* structure defines the memory map of the RCPM control block */
struct rcpm_v2 {
	u8 reserved[0x00c];
	/* Device Run Control Debug Status Register */
	u32 dcdsr0;
	u8 reserved0[0x100-0x010];
	/* Run Control Debug Status Register m */
	u32 cdsr[RCPM_v2_NO_OF_CONTROL_ELEM];
	u8 reserved1[0x300-0x160];
	/* Core Group Configuration Register n */
	struct {
		u32 reserved[3];
		u32 cgcrl;	/* Core Group Configuration Registers */
	} cgcr[RCPM_v2_NO_OF_CORE_GROUPS];
	u8 reserved2[0x500-0x3c0];
	/* Core Event Status Registers for EPU Events */
	u32 cesre[RCPM_v2_NO_OF_CONTROL_ELEM];
	u8 reserved3[0x700-0x560];
	/* Core Event Status Registers for Device Events */
	u32 cesrd[RCPM_v2_NO_OF_CONTROL_ELEM];
	u8 reserved4[0x900-0x760];
	/* Core Group Action Control Register n for EPU Events */
	u32 cgacre[RCPM_v2_NO_OF_EPU_EVENTS];
	u8 reserved5[0x980-0x940];
	/* Device Action Control Register n for EPU Events */
	u32 dacre[RCPM_v2_NO_OF_EPU_EVENTS];
	u8 reserved6[0xa00-0x9c0];
	/* Core Group Action Control Register n for Device Events */
	u32 cgacrd[RCPM_v2_NO_OF_DEV_EVENTS];
	u8 reserved7[0xa48-0xa28];
	/* Thread WRS Status Register 2 */
	u32 twrssr02;
	u32 twrssr01;
	u8 reserved8[0xa80-0xa50];
	/* Device Action Control Register n for Device Events */
	u32 dacrd[RCPM_v2_NO_OF_DEV_EVENTS];
	u8 reserved9[0xb00-0xaa8];
	/* Core State Action Control Register n  */
	u32 csttacr[RCPM_v2_NO_OF_CATTACR];
	u8 reserved10[0x1000-0xb0c];
	u8 reserved11[0x2000-0x1000];
} PACKED;
CTASSERT(sizeof(struct rcpm_v2) == RCPM_v2_STRUCT_SIZE);

#endif  /* DCSR_RCPM_V2_H */
