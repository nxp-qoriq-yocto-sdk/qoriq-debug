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

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/seq_file.h>
#include <linux/io.h>

#include "dcsr_npc.h"
#include "dcsr_npc_trace.h"

/* Private Fwd Decls */
static int npc_buf_open(struct inode *inode, struct file *file);
static int npc_buf_raw_open(struct inode *inode, struct file *file);

/* FILE Operation Functions */
const struct file_operations npc_trace_fops = {
		.owner		= THIS_MODULE,
		.open		= npc_buf_open,
		.read		= seq_read,
		.llseek		= seq_lseek,
		.release	= single_release,
};

const struct file_operations npc_trace_raw_fops = {
		.owner		= THIS_MODULE,
		.open		= npc_buf_raw_open,
		.read		= seq_read,
		.llseek		= seq_lseek,
		.release	= single_release,
};

/* NPC global pointers */
struct npc *npc_ptr;
/* Trace buffer is an array of u32  */
u32 *npc_trace_ptr;

/* Driver Initialization Functions */
int dcsr_npc_trace_init(struct dentry *parent_dentry, struct dbg_devices *dbg_devs)
{
	int ret = 0;
	struct dentry *current_dentry;
	struct dentry *de;

	/* copy the pointers to data */
	npc_trace_ptr = (u32 *)dbg_devs->npc_trace.mem_ptr;
	npc_ptr = (struct npc *)dbg_devs->npc.mem_ptr;

	if (npc_ptr == 0 || npc_trace_ptr == 0)
		return ret;

	current_dentry = dbg_devs->npc.current_dentry;
	if (!current_dentry) {
		CREATE_CURRENT_DBGFS_DIR(parent_dentry, &dbg_devs->npc,
						DEBUGFS_NPC_NAME);
	}

	/* Special since not a simple memory mapped register */
	de = debugfs_create_file("trace_buffer", DBGFS_RO_MODE, current_dentry,
					(void *)NULL, &npc_trace_fops);
	if (IS_ERR_OR_NULL(de))
		return -ENOMEM;

	de = debugfs_create_file("trace_buffer_raw", DBGFS_RO_MODE, current_dentry,
					(void *)NULL, &npc_trace_raw_fops);
	if (IS_ERR_OR_NULL(de))
		return -ENOMEM;

	return ret;
}

/* read NPC trace buffer from start_index to end_index */
static int read_npc_buf_range(struct seq_file *m,
		unsigned int start_index,
		unsigned int end_index)
{
	unsigned int i, j;
	unsigned int index;
	u32 val1, val2, val3;

	for (i = start_index; i < end_index; i++) {
		for (j = 0; j < 4; j++) {
			/* access buffer by words */
			index = 0x800*j + 4*i;
			val1 = npc_trace_ptr[index];
			val2 = npc_trace_ptr[index + 1];
			val3 = npc_trace_ptr[index + 2];

			/* remove the ECC byte and shift all */
			val1 = (val1 << 8) | (val2 >> 24);
			val2 = (val2 << 8) | (val3 >> 24);

			seq_printf(m, "0x%08x\n0x%08x\n", val1, val2);
		}
	}

	return 0;
}

/* read the NPC trace buffer */
static int read_npc_buf(struct seq_file *m,
		unsigned int start_index, unsigned int overflowed)
{
	int ret;
	static unsigned int max_index = NPC_TRACE_MAX_INDEX;
	if (overflowed)
		ret = read_npc_buf_range(m, start_index, max_index);

	ret = read_npc_buf_range(m, 0, start_index);
	return ret;
}

/* FILE Show (on open) function */
static int npc_buf_show(struct seq_file *m, void *v)
{
	u32 nst;
	unsigned int index;
	unsigned int overflowed;

	nst = in_be32(&npc_ptr->nst);
	index = nst & NPC_NST_QWA_MASK;
	overflowed = nst & NPC_NST_TOV_MASK;

	/* read out the trace buffer */
	read_npc_buf(m, index, overflowed);

	return 0;
}

static int npc_buf_raw_show(struct seq_file *m, void *v)
{
	unsigned int index = NPC_TRACE_MAX_INDEX;
	unsigned int overflowed = 0;

	/* read out the entire trace buffer */
	read_npc_buf(m, index, overflowed);

	return 0;
}

/* Simple file open function */
static int npc_buf_open(struct inode *inode, struct file *file)
{
	return single_open(file, npc_buf_show, NULL);
}

static int npc_buf_raw_open(struct inode *inode, struct file *file)
{
	return single_open(file, npc_buf_raw_show, NULL);
}
