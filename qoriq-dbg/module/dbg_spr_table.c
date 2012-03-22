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

#include "dbg_spr.h"
#include "asm/reg_booke.h"

/* Create a listing of accessible Special Purpose Registers per core
 */
const struct spr_register spr_data[] = {
		/* Core 0 */
		{
		  .core = 0,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 0,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 0,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 0,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 0,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 0,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 0,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 0,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 0,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 0,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 0,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 0,
		  .spr = SPRN_NPIDR,
		},

		/* Core 1 */
		{
		  .core = 1,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 1,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 1,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 1,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 1,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 1,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 1,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 1,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 1,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 1,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 1,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 1,
		  .spr = SPRN_NPIDR,
		},

		/* Core 2 */
		{
		  .core = 2,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 2,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 2,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 2,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 2,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 2,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 2,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 2,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 2,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 2,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 2,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 2,
		  .spr = SPRN_NPIDR,
		},

		/* Core 3 */
		{
		  .core = 3,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 3,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 3,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 3,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 3,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 3,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 3,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 3,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 3,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 3,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 3,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 3,
		  .spr = SPRN_NPIDR,
		},

		/* Core 4 */
		{
		  .core = 4,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 4,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 4,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 4,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 4,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 4,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 4,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 4,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 4,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 4,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 4,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 4,
		  .spr = SPRN_NPIDR,
		},

		/* Core 5 */
		{
		  .core = 5,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 5,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 5,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 5,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 5,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 5,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 5,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 5,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 5,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 5,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 5,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 5,
		  .spr = SPRN_NPIDR,
		},

		/* Core 6 */
		{
		  .core = 6,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 6,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 6,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 6,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 6,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 6,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 6,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 6,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 6,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 6,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 6,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 6,
		  .spr = SPRN_NPIDR,
		},

		/* Core 7 */
		{
		  .core = 7,
		  .spr = SPRN_DBSR,
		},
		{
		  .core = 7,
		  .spr = SPRN_DBCR0,
		},
		{
		  .core = 7,
		  .spr = SPRN_DBCR1,
		},
		{
		  .core = 7,
		  .spr = SPRN_DBCR2,
		},
		{
		  .core = 7,
		  .spr = SPRN_DBCR4,
		},
		{
		  .core = 7,
		  .spr = SPRN_IAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 7,
		  .spr = SPRN_IAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 7,
		  .spr = SPRN_DAC1,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 7,
		  .spr = SPRN_DAC2,
#ifdef CONFIG_PPC64
		  .size64 = 1,
#endif
		},
		{
		  .core = 7,
		  .spr = SPRN_DEVENT,
		},
		{
		  .core = 7,
		  .spr = SPRN_DDAM,
		},
		{
		  .core = 7,
		  .spr = SPRN_NPIDR,
		},

};
