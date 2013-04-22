/*
 * Copyright (C) 2010, 2011, 2012, 2013 Freescale Semiconductor, Inc.
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

#include <linux/fs.h>
#include <linux/uaccess.h>

#include "dbg_pmr.h"

void pmr_reg_init(struct pmr_register *regs, int core_id)
{
	int i;
	for (i = 0; i < PMR_MAX; i++)
		regs[i].core = core_id;

	regs[PMR_PMC0].pmr = PMRN_PMC0;
	regs[PMR_PMC1].pmr = PMRN_PMC1;
	regs[PMR_PMC2].pmr = PMRN_PMC2;
	regs[PMR_PMC3].pmr = PMRN_PMC3;
	regs[PMR_PMC4].pmr = PMRN_PMC4;
	regs[PMR_PMC5].pmr = PMRN_PMC5;
	regs[PMR_PMLCA0].pmr = PMRN_PMLCA0;
	regs[PMR_PMLCA1].pmr = PMRN_PMLCA1;
	regs[PMR_PMLCA2].pmr = PMRN_PMLCA2;
	regs[PMR_PMLCA3].pmr = PMRN_PMLCA3;
	regs[PMR_PMLCA4].pmr = PMRN_PMLCA4;
	regs[PMR_PMLCA5].pmr = PMRN_PMLCA5;
	regs[PMR_PMLCB0].pmr = PMRN_PMLCB0;
	regs[PMR_PMLCB1].pmr = PMRN_PMLCB1;
	regs[PMR_PMLCB2].pmr = PMRN_PMLCB2;
	regs[PMR_PMLCB3].pmr = PMRN_PMLCB3;
	regs[PMR_PMLCB4].pmr = PMRN_PMLCB4;
	regs[PMR_PMLCB5].pmr = PMRN_PMLCB5;
	regs[PMR_PMGC0].pmr = PMRN_PMGC0;
}

/* Fwd declarations */
static int pm_open_generic(struct inode *inode, struct file *file);
static ssize_t pm_write(struct file *file, const char __user *user_buf,
			size_t count, loff_t *ppos);
static ssize_t pm_read(struct file *file, char __user *userbuf,
		size_t count, loff_t *ppos);

/* define the file ops for the PerfMon registers */
const struct file_operations perfmon_fops = {
	.write = pm_write,
	.read = pm_read,
	.open = pm_open_generic,
};

/* define the open file op for the PerfMon registers */
static int pm_open_generic(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return 0;
}

static void _read_pmr(void *info)
{
	struct pmr_register* pm = (struct pmr_register *)info;
	switch (pm->pmr) {
	case PMRN_PMC0:
		pm->val = mfpmr(PMRN_PMC0);
		break;
	case PMRN_PMC1:
		pm->val = mfpmr(PMRN_PMC1);
		break;
	case PMRN_PMC2:
		pm->val = mfpmr(PMRN_PMC2);
		break;
	case PMRN_PMC3:
		pm->val = mfpmr(PMRN_PMC3);
		break;
	case PMRN_PMC4:
		pm->val = mfpmr(PMRN_PMC4);
		break;
	case PMRN_PMC5:
		pm->val = mfpmr(PMRN_PMC5);
		break;
	case PMRN_PMLCA0:
		pm->val = mfpmr(PMRN_PMLCA0);
		break;
	case PMRN_PMLCA1:
		pm->val = mfpmr(PMRN_PMLCA1);
		break;
	case PMRN_PMLCA2:
		pm->val = mfpmr(PMRN_PMLCA2);
		break;
	case PMRN_PMLCA3:
		pm->val = mfpmr(PMRN_PMLCA3);
		break;
	case PMRN_PMLCA4:
		pm->val = mfpmr(PMRN_PMLCA4);
		break;
	case PMRN_PMLCA5:
		pm->val = mfpmr(PMRN_PMLCA5);
		break;
	case PMRN_PMLCB0:
		pm->val = mfpmr(PMRN_PMLCB0);
		break;
	case PMRN_PMLCB1:
		pm->val = mfpmr(PMRN_PMLCB1);
		break;
	case PMRN_PMLCB2:
		pm->val = mfpmr(PMRN_PMLCB2);
		break;
	case PMRN_PMLCB3:
		pm->val = mfpmr(PMRN_PMLCB3);
		break;
	case PMRN_PMLCB4:
		pm->val = mfpmr(PMRN_PMLCB4);
		break;
	case PMRN_PMLCB5:
		pm->val = mfpmr(PMRN_PMLCB5);
		break;
	case PMRN_PMGC0:
		pm->val = mfpmr(PMRN_PMGC0);
		break;
	default:
		printk(KERN_ERR "Read of unknown PMR(%d) attempted\n", pm->pmr);
		break;
	};
}

static void _write_pmr(void *info)
{
	struct pmr_register* pm = (struct pmr_register *)info;
	switch (pm->pmr) {
	case PMRN_PMC0:
		mtpmr(PMRN_PMC0, pm->val);
		break;
	case PMRN_PMC1:
		mtpmr(PMRN_PMC1, pm->val);
		break;
	case PMRN_PMC2:
		mtpmr(PMRN_PMC2, pm->val);
		break;
	case PMRN_PMC3:
		mtpmr(PMRN_PMC3, pm->val);
		break;
	case PMRN_PMC4:
		mtpmr(PMRN_PMC4, pm->val);
		break;
	case PMRN_PMC5:
		mtpmr(PMRN_PMC5, pm->val);
		break;
	case PMRN_PMLCA0:
		mtpmr(PMRN_PMLCA0, pm->val);
		break;
	case PMRN_PMLCA1:
		mtpmr(PMRN_PMLCA1, pm->val);
		break;
	case PMRN_PMLCA2:
		mtpmr(PMRN_PMLCA2, pm->val);
		break;
	case PMRN_PMLCA3:
		mtpmr(PMRN_PMLCA3, pm->val);
		break;
	case PMRN_PMLCA4:
		mtpmr(PMRN_PMLCA4, pm->val);
		break;
	case PMRN_PMLCA5:
		mtpmr(PMRN_PMLCA5, pm->val);
		break;
	case PMRN_PMLCB0:
		mtpmr(PMRN_PMLCB0, pm->val);
		break;
	case PMRN_PMLCB1:
		mtpmr(PMRN_PMLCB1, pm->val);
		break;
	case PMRN_PMLCB2:
		mtpmr(PMRN_PMLCB2, pm->val);
		break;
	case PMRN_PMLCB3:
		mtpmr(PMRN_PMLCB3, pm->val);
		break;
	case PMRN_PMLCB4:
		mtpmr(PMRN_PMLCB4, pm->val);
		break;
	case PMRN_PMLCB5:
		mtpmr(PMRN_PMLCB5, pm->val);
		break;
	case PMRN_PMGC0:
		mtpmr(PMRN_PMGC0, pm->val);
		break;
	default:
		printk(KERN_ERR "Write of unknown PMR(%d) attempted\n", pm->pmr);
		break;
	};
}

/* perform the read operation on a enabled cpu */
static int read_pmr(struct pmr_register *pmr)
{
	if (!cpu_online(pmr->core)) {
		printk(KERN_ERR "qoriq-dbg: Core %d is not online\n",
				pmr->core);
		return -1;
	}
	return smp_call_function_single(pmr->core, _read_pmr, pmr, 1);
}

/* perform the write operation on a enabled cpu */
static void write_pmr(struct pmr_register *pmr)
{
	if (cpu_online(pmr->core))
		smp_call_function_single(pmr->core, _write_pmr, pmr, 1);
	else
		printk(KERN_ERR "qoriq-dbg: Core %d is not online\n",
				pmr->core);
}

/* Write the PerfMon registers */
static ssize_t pm_write(struct file *file, const char __user *userbuf,
			size_t count, loff_t *ppos)
{
	int ret;

	struct pmr_register *pmr = file->private_data;

	ret = kstrtou32_from_user(userbuf, count, 0, &pmr->val);
	if (!ret)
		write_pmr(pmr);

	return count;
}

/* use this as the internal buffer size */
#define BUFFER_SIZE 32

/* Read the PerfMon registers */
static ssize_t pm_read(struct file *file, char __user *userbuf,
			size_t count, loff_t *ppos)
{
	struct pmr_register *pmr = file->private_data;
	char buf[BUFFER_SIZE];
	int num = 0;

	if (!read_pmr(pmr))
		num = snprintf(buf, sizeof(buf)-1, "0x%08x\n", pmr->val);

	return simple_read_from_buffer(userbuf, count, ppos, buf, num);
}
