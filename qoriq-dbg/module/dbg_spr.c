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

#include <linux/fs.h>
#include <linux/uaccess.h>

#include "dbg_spr.h"
#include "asm/reg_fsl_emb.h"

/* Fwd declarations */
static int spr_open_generic(struct inode *inode, struct file *file);
static ssize_t spr_write(struct file *file, const char __user *user_buf,
			size_t count, loff_t *ppos);
static ssize_t spr_read(struct file *file, char __user *userbuf,
		size_t count, loff_t *ppos);

/* define the file operations  */
const struct file_operations spr_fops = {
	.write = spr_write,
	.read = spr_read,
	.open = spr_open_generic,
};

/* define the open file operation */
static int spr_open_generic(struct inode *inode, struct file *file)
{
	file->private_data = inode->i_private;
	return 0;
}

static void _read_spr(void *info)
{
	struct spr_register* spr = (struct spr_register *)info;

	switch (spr->spr) {
	case SPRN_DBSR:
		spr->val = mfspr(SPRN_DBSR);
		break;
	case SPRN_DBCR0:
		spr->val = mfspr(SPRN_DBCR0);
		break;
	case SPRN_DBCR1:
		spr->val = mfspr(SPRN_DBCR1);
		break;
	case SPRN_DBCR2:
		spr->val = mfspr(SPRN_DBCR2);
		break;
	case SPRN_DBCR4:
		spr->val = mfspr(SPRN_DBCR4);
		break;
	case SPRN_IAC1:
		spr->val = mfspr(SPRN_IAC1);
		break;
	case SPRN_IAC2:
		spr->val = mfspr(SPRN_IAC2);
		break;
	case SPRN_DAC1:
		spr->val = mfspr(SPRN_DAC1);
		break;
	case SPRN_DAC2:
		spr->val = mfspr(SPRN_DAC2);
		break;
	case SPRN_DEVENT:
		spr->val = mfspr(SPRN_DEVENT);
		break;
	case SPRN_DDAM:
		spr->val = 0; /* DDAM is WO */
		break;
	case SPRN_NPIDR:
		spr->val = mfspr(SPRN_NPIDR);
		break;
	default:
		break;
	};
}

static void _write_spr(void *info)
{
	struct spr_register* spr = (struct spr_register *)info;

	switch (spr->spr) {
	case SPRN_DBSR:
		mtspr(SPRN_DBSR, spr->val);
		break;
	case SPRN_DBCR0:
		mtspr(SPRN_DBCR0, spr->val);
		break;
	case SPRN_DBCR1:
		mtspr(SPRN_DBCR1, spr->val);
		break;
	case SPRN_DBCR2:
		mtspr(SPRN_DBCR2, spr->val);
		break;
	case SPRN_DBCR4:
		mtspr(SPRN_DBCR4, spr->val);
		break;
	case SPRN_IAC1:
		mtspr(SPRN_IAC1, spr->val);
		break;
	case SPRN_IAC2:
		mtspr(SPRN_IAC2, spr->val);
		break;
	case SPRN_DAC1:
		mtspr(SPRN_DAC1, spr->val);
		break;
	case SPRN_DAC2:
		mtspr(SPRN_DAC2, spr->val);
		break;
	case SPRN_DEVENT:
		mtspr(SPRN_DEVENT, spr->val);
		break;
	case SPRN_DDAM:
		mtspr(SPRN_DDAM, spr->val);
		break;
	case SPRN_NPIDR:
		mtspr(SPRN_NPIDR, spr->val);
		break;
	default:
		break;
	};
}

/* perform the read operation on a enabled cpu */
static int read_spr(struct spr_register *spr)
{
	if (!cpu_online(spr->core)) {
		printk(KERN_ERR "Core %d is not online\n", spr->core);
		return -1;
	}
	return smp_call_function_single(spr->core, _read_spr, spr, 1);
}

/* perform the write operation on a enabled cpu */
static void write_spr(struct spr_register *spr)
{
	if (cpu_online(spr->core))
		smp_call_function_single(spr->core, _write_spr, spr, 1);
	else
		printk(KERN_ERR "Core %d is not online\n", spr->core);
}

/* Write the Special Purpose Register */
static ssize_t spr_write(struct file *file, const char __user *userbuf,
			size_t count, loff_t *ppos)
{
	int ret;
	struct spr_register *spr = file->private_data;

#ifdef CONFIG_PPC64
	ret = kstrtou64_from_user(userbuf, count, 0, &spr->val);
#else
	ret = kstrtou32_from_user(userbuf, count, 0, &spr->val);
#endif
	if (!ret) {
		write_spr(spr);
	}

	return count;
}

#define BUFFER_SIZE 32
/* Read the Special Purpose Register  */
static ssize_t spr_read(struct file *file, char __user *userbuf,
			size_t count, loff_t *ppos)
{
	struct spr_register *spr = file->private_data;
	char buf[BUFFER_SIZE];
	int num = 0;

	if (!read_spr(spr)) {
#ifdef CONFIG_PPC64
		if (spr->size64)
			num = snprintf(buf, sizeof(buf)-1, "0x%016llx\n", spr->val);
		else
			num = snprintf(buf, sizeof(buf)-1, "0x%08llx\n", spr->val);
#else
		num = snprintf(buf, sizeof(buf)-1, "0x%08x\n", spr->val);
#endif
	}

	return simple_read_from_buffer(userbuf, count, ppos, buf, num);
}
