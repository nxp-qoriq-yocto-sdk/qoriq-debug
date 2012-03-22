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

#include "dbg_perfmon.h"
#include "asm/reg_fsl_emb.h"

/* Create a listing of all possible PMRNs per core
 */
const struct perfmon_register pm_data[] = {
		/* Core 0 */
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 0,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 1 */
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 1,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 2 */
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 2,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 3 */
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 3,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 4 */
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 4,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 5 */
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 5,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 6 */
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 6,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
		/* Core 7 */
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMC0,
		  .write_pmr = PMRN_PMC0,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMC1,
		  .write_pmr = PMRN_PMC1,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMC2,
		  .write_pmr = PMRN_PMC2,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMC3,
		  .write_pmr = PMRN_PMC3,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCA0,
		  .write_pmr = PMRN_PMLCA0,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCA1,
		  .write_pmr = PMRN_PMLCA1,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCA2,
		  .write_pmr = PMRN_PMLCA2,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCA3,
		  .write_pmr = PMRN_PMLCA3,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCB0,
		  .write_pmr = PMRN_PMLCB0,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCB1,
		  .write_pmr = PMRN_PMLCB1,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCB2,
		  .write_pmr = PMRN_PMLCB2,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMLCB3,
		  .write_pmr = PMRN_PMLCB3,
		},
		{
		  .core = 7,
		  .read_pmr = PMRN_UPMGC0,
		  .write_pmr = PMRN_PMGC0,
		},
};
