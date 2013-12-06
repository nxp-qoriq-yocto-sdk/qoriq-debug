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

#ifndef CCSR_RCPM_V2_H
#define CCSR_RCPM_V2_H

#include "common.h"

#define RCPM_2_STRUCT_SIZE		0x1000

/* structure defines the memory map of the RCPM control block */
struct rcpm_2 {
	/* Thread PH10 Status Registers */
	u32 tph10sr[4];	/* register numbered from high address*/
	/* Thread PH10 Set Control Registers */
	u32 tph10setr[4];	/* register numbered from high address*/
	/* Thread PH10 Clear Control Registers */
	u32 tph10clrr[4];	/* register numbered from high address*/
	/* Thread PH10 Previous State Registers */
	u32 tph10psr[4];	/* register numbered from high address*/
	/* Thread Wait Status Registers */
	u32 twaitsr[4];	/* register numbered from high address*/
	u8 reserved1[0xb0-0x50];
	/* Physical Core PH15 Status Register */
	u32 pcph15sr;
	/* Physical Core PH15 Set Control Register */
	u32 pcph15setr;
	/* Physical Core PH15 Clear Control Register */
	u32 pcph15clrr;
	/* Physical Core PH15 Previous State Register */
	u32 pcph15psr;
	u8 reserved2[0xd0-0xc0];
	/* Physical Core PH20 Status Register */
	u32 pcph20sr;
	/* Physical Core PH20 Set Control Register */
	u32 pcph20setr;
	/* Physical Core PH20 Clear Control Register */
	u32 pcph20clrr;
	/* Physical Core PH20 Previous State Register */
	u32 pcph20psr;
	/* Physical Core PW20 State Register */
	u32 pcpw20sr;
	u8 reserved3[0xf0-0xe4];
	/* Physical Core PH30 Status Register */
	u32 pcph30sr;
	/* Physical Core PH30 Set Control Register */
	u32 pcph30setr;
	/* Physical Core PH30 Clear Control Register */
	u32 pcph30clrr;
	/* Physical Core PH30 Previous State Register */
	u32 pcph30psr;
	u8 reserved11[0x1000-0x100];
} PACKED;
CTASSERT(sizeof(struct rcpm_2) == RCPM_2_STRUCT_SIZE);

#endif  /* CCSR_RCPM_V2_H */
