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
#ifndef DBG_DEVICE_H
#define DBG_DEVICE_H

#include <linux/debugfs.h>
#include <linux/of_platform.h>

/* Max number of components by type in QoriQ Arch */
#define MAX_NUM_CPU		8
#define MAX_NUM_FMAN		2
#define MAX_NUM_DDR		2

/* dbg_device maintains the association between the mapped dcsr memory
 * and the debugfs directory where the device files are located
 */
struct dbg_device {
	/* index number for this device */
	int index;
	/* mapped memory address */
	void *mem_ptr;
	/* current directory */
	struct dentry *current_dentry;
	/* device tree node pointer */
	struct device_node *np;
};

/* maintains information on each sub-device managed by the driver */
struct dbg_devices {
	struct dbg_device bman;
	struct dbg_device cndc1;
	struct dbg_device cndc2;
	struct dbg_device cpu[MAX_NUM_CPU];
	struct dbg_device ddr[MAX_NUM_DDR];
	struct dbg_device dpaa;
	struct dbg_device epu;
	struct dbg_device fman[MAX_NUM_FMAN];
	struct dbg_device nal;
	struct dbg_device npc;
	struct dbg_device npc_trace;
	struct dbg_device nxc;
	struct dbg_device ocn;
	struct dbg_device qman;
	struct dbg_device rcpm;
};
/* maintains information on each sub-device managed by the driver */
extern struct dbg_devices dbg_dev;

#endif /* DBG_DEVICE_H */
