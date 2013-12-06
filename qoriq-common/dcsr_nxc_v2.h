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

#ifndef DCSR_NXC_V2_H
#define DCSR_NXC_V2_H

#include "common.h"

/* size of nxc struct */
#define NXC_V2_STRUCT_SIZE		0x1000

/* size of nxc hit gen struct */
#define NXC_V2_HIT_GEN_STRUCT_SIZE	0x100

/* Number of counting units in the NXC */
#define NXC_V2_NO_OF_HITGENS		3
/* Number of mask units in a HitGen */
#define NXC_V2_HG_NO_OF_MASK_UNITS	5

/* structure defines the memory map of the NXC HitGen control block */
struct nxc_hit_gen_v2 {
	/* HitGen Configuration Register 0 */
	u32 hgcfg0;
	/* HitGen Mask Unit Configuration Registers */
	u32 hgcfg[NXC_V2_HG_NO_OF_MASK_UNITS];
	/* HitGen EC Configuration Registers */
	u32 hgecr[NXC_V2_HG_NO_OF_MASK_UNITS];
	u8  reserved1[0x30-0x2c];
	/* HitGen Comparator A Compare Value Hi 0 */
	u32 cmpavalhi0;
	/* HitGen Comparator A Compare Value Hi 1 */
	u32 cmpavalhi1;
	/* HitGen Comparator A Compare Value Hi 2 */
	u32 cmpavalhi2;
	u8  reserved2[0x40-0x3c];
	/* HitGen Comparator A Compare Value Lo 0 */
	u32 cmpavalmsklo0;
	/* HitGenm Comparator A Compare Value Lo 1 */
	u32 cmpavalmsklo1;
	/* HitGenm Comparator A Compare Value Lo 2 */
	u32 cmpavalmsklo2;
	u8  reserved3[0x50-0x4c];
	/* HitGenm ComparatorB Compare Value Hi and Lo */
	u32 cmpbvalhilo;
	/* HitGenm ComparatorB Compare Value and Mask for masked compare */
	u32 cmpbvalmsk;
	/* HitGenm ComparatorB Compare Value for vector compare */
	u32 cmpbvector;
	u8  reserved4[0x60-0x5c];
	/* HitGenm ComparatorB Compare Values for Match0/1 */
	u32 cmpcval;
	/* HitGenm ComparatorB Compare Value and Mask for masked compare */
	u32 cmpcvalmsk;
	u8  reserved5[0x100-0x68];
} PACKED;
CTASSERT(sizeof(struct nxc_hit_gen_v2) == NXC_V2_HIT_GEN_STRUCT_SIZE);

/* structure defines the memory map of the NXC control block */
struct nxc_v2 {
	u32 nxccr0; /* Nexus Trace Message Control Register 0 */
	u8  reserved1[0x100-0x004];

	u32 fccfg0; /* NXC Filter Control Configuration Register 0 */
	u32 fccfg1; /* NXC Filter Control Configuration Register 1 */
	u32 fccfg2; /* NXC Filter Control Configuration Register 2 */
	u32 fccfg3; /* NXC Filter Control Configuration Register 3 */
	u32 fccfg4; /* NXC Filter Control Configuration Register 4 */
	u32 fccfg5; /* NXC Filter Control Configuration Register 5 */
	u32 fccfg6; /* NXC Filter Control Configuration Register 6 */
	u8  reserved2[0x400-0x11c];

	struct nxc_hit_gen_v2 hit_gen[NXC_V2_NO_OF_HITGENS];

	u8  reserved3[0x1000-0x700];
} PACKED;
CTASSERT(sizeof(struct nxc_v2) == NXC_V2_STRUCT_SIZE);

#endif  /* DCSR_NXC_V2_H */
