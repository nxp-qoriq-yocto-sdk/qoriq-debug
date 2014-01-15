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

#ifndef CCSR_BMAN_V2_H
#define CCSR_BMAN_V2_H

#include "common.h"

/* number of buffer pools */
#define BMAN_V2_NUM_POOLS		64
/* number of performance monitors */
#define BMAN_V2_NUM_PERF_MONITORS	8
/* Number of words containing error data */
#define BMAN_V2_NUM_DATA_ERROR_WORDS	8

/* BMAN configuration registers */
struct bman_v2 {
	/* Software portal depletion entry threshold */
	u32 bman_pool_swdet[BMAN_V2_NUM_POOLS];
	/* Hardware portal depletion entry threshold */
	u32 bman_pool_hwdet[BMAN_V2_NUM_POOLS];
	/* Software portal depletion exit threshold */
	u32 bman_pool_swdxt[BMAN_V2_NUM_POOLS];
	/* Hardware portal depletion exit threshold */
	u32 bman_pool_hwdxt[BMAN_V2_NUM_POOLS];
	/* Software portal depletion count */
	u32 bman_pool_sdcnt[BMAN_V2_NUM_POOLS];
	/* Hardware portal depletion count */
	u32 bman_pool_hdcnt[BMAN_V2_NUM_POOLS];
	/* Snapshot of content in pool N */
	u32 bman_pool_content[BMAN_V2_NUM_POOLS];
	/* Head pointer for pool N */
	u32 bman_pool_hdptr[BMAN_V2_NUM_POOLS];

	/* Free Buffer Proxy Record registers */
	/* Free pool count */
	u32 fbpr_fpc;
	/* Free pool low watermark interrupt threshold*/
	u32 fbpr_fp_lwit;
	/* Head pointer for FNPR list */
	u32 fbpr_hdptr;
	u8 reserved1[0x900-0x80c];

	/* Performance Monitor Configuration */
	/* Command performance monitor configuration */
	u32 bman_cmd_pm_cfg[BMAN_V2_NUM_PERF_MONITORS];
	/* Free list performance monitor configuration */
	u32 bman_fl_pm_cfg[BMAN_V2_NUM_PERF_MONITORS];
	/* Free list performance monitor configuration */
	u32 bman_cmd_pm_cfg_cfifo[BMAN_V2_NUM_PERF_MONITORS];
	u8 reserved2[0xA00-0x960];

	/* Error capture registers */
	u8  reserved3[0xA04-0xA00];
	/* Error capture information register */
	u32 bman_ecir;
	u8 reserved4[0xA30-0xA08];
	/* Single bit ECC error threshold register */
	u32 bman_sbet;
	/* Corruption error capture register */
	u32 bman_cecr;
	/* Corruption error address register */
	u32 bman_cear;
	u8 reserved0[0xA44-0xA3C];
	/* Access error capture register */
	u32 bman_aecr;
	/* Access error address register */
	u32 bman_aear;
	u8 reserved5[0xA80-0xA4C];

	/* Single bit ECC error count 0 register */
	u32 bman_sbec0;
	u8 reserved6[0xBF8-0xA84];

	/* ID/Revision registers */
	/* Bman IP Block 1 register */
	u32 bman_ip_rev_1;
	/* Bman IP Block 2 register */
	u32 bman_ip_rev_2;

	/* External Memory Configuration registers */
	/* Data structure extended base address register */
	u32 fbpr_bare;
	/* Data structure base address register */
	u32 fbpr_bar;
	u8 reserved7[0xC10-0xC08];
	/* Data structure attributes register */
	u32 fbpr_ar;
	u8 reserved8[0xD04-0xC14];
	/* Bman Source ID register */
	u32 bman_srcidr;
	/* Bman Logical I/O device number register */
	u32 bman_liodnr;
	u8 reserved9[0xE00-0xD0C];

	/* Bman Interrupt and Error registers */
	/* Error interrupt status register */
	u32 bman_err_isr;
	/* Error interrupt enable register */
	u32 bman_err_ier;
	/* Error interrupt status disable register */
	u32 bman_err_isdr;
	/* Error interrupt inhibit register */
	u32 bman_err_iir;
	/* Error interrupt force register */
	u32 bman_err_ifr;
	u8 reserved10[0x1000-0xe14];
} PACKED;
/* check addresses and size */
CTASSERT(offsetof(struct bman_v2, bman_ecir) == 0xA04);
CTASSERT(offsetof(struct bman_v2, bman_sbet) == 0xA30);
CTASSERT(offsetof(struct bman_v2, bman_ip_rev_1) == 0xBF8);
CTASSERT(sizeof(struct bman_v2) == 0x1000);

#endif /* CCSR_BMAN_V2_H */
