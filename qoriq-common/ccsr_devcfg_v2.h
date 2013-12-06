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

#ifndef CCSR_DEVCFG_V2_H
#define CCSR_DEVCFG_V2_H

#include "common.h"

#define DCFG_V2_STRUCT_SIZE		0x1000

/* number of RCW words */
#define DEVCFG_NUM_RCW_WORDS		16

/* structure defines the memory map of the Device Configuration block */
struct device_cfg_v2 {
	u8 reserved0[0xA0];
	/* Processor Version Register */
	u32 pvr;
	/* System Version Register */
	u32 svr;
	u8 reserved1[0x100 - 0xA8];
	/* Reset Control Word */
	u32 rcw[DEVCFG_NUM_RCW_WORDS];
	u8 reserved2[0x1000-0x140];
} PACKED;
CTASSERT(sizeof(struct device_cfg_v2) == DCFG_V2_STRUCT_SIZE);

#endif  /* CCSR_DEVCFG_V2_H */
