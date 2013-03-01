/*
 * Copyright (C) 2010, 2011, 2012 Freescale Semiconductor, Inc.
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

#include "dcsr_ocn.h"

/* Driver Initialization Function */
int dcsr_ocn_init(struct dentry *parent_dentry, struct dbg_device *dev)
{
	int i;
	struct dentry *current_dentry;
	struct dentry *de;
	struct ocn *ptr = (struct ocn *)dev->mem_ptr[0];
	char reg_name[DBFS_REG_NAME_LEN];

	CREATE_CURRENT_DBGFS_DIR(parent_dentry, dev,
					DEBUGFS_OCN_NAME);

	/* Debug status control */
	DBGFS_CREATE_RW_X32("ocdicr0", current_dentry, &ptr->ocdicr0);
	for (i = 0; i < OCN_NUM_REF_INPUT_MUX; ++i) {
		sprintf(reg_name, "ocrimcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ocrimcr[i]);
	}
	for (i = 0; i < OCN_NUM_GEN_INPUT_MUX; ++i) {
		sprintf(reg_name, "ocgimcr%d", i);
		DBGFS_CREATE_RW_X32(reg_name, current_dentry,
				&ptr->ocgimcr[i]);
	}

	return 0;
}
