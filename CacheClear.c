// SPDX-License-Identifier: GPL-2.0
/**
 * Copyright (c) 2023 Michael T. Kloos <michael@michaelkloos.com>
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL-2.0");
MODULE_AUTHOR("Michael T. Kloos");
MODULE_DESCRIPTION("Adds a simple syscall to run the WBINVD instruction for benchmarking.  "
                   "May not be safe and should only be loaded when need.  ");
MODULE_VERSION("0.1");

//static int modFileOpen(struct inode *inode, struct file *filp);
//static int modFileRelease(struct inode *inode, struct file *filp);
static long modFileIoctl(struct file *filp, unsigned int cmd, unsigned long arg);

static const struct file_operations echelon_fops = {
	.owner   = THIS_MODULE,
	//.read             = NULL,
	//.write            = NULL,
	//.open             = modFileOpen,
	//.release          = modFileRelease,
	//.llseek           = NULL,
	//.flush            = NULL,
	.unlocked_ioctl   = modFileIoctl,
};
static struct miscdevice echelon_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "ClearCache",
	.fops = &echelon_fops,
	//.next = NULL,
	//.prev = NULL,
};

/*
static int modFileOpen(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "ClearCache: open\n");
	return 0;
}
static int modFileRelease(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "ClearCache: release\n");
	return 0;
}
*/
static long modFileIoctl(struct file *filp, unsigned int cmd, unsigned long arg) {
	printk(KERN_INFO "ClearCache: ioctl(file, %u, %lu)\n", cmd, arg);
	if (cmd == 1) {
		printk(KERN_INFO "ClearCache: Clearing Cache\n");
		__asm__ __volatile__ ("MFENCE \n"
		                      "LFENCE \n"
		                      "WBINVD \n");
	}
	return 0;
}

static int __init modInit(void) {
	int retval;

	printk(KERN_INFO "Loading CacheClear module...");

	retval = misc_register(&echelon_dev);
	if (retval) {
		goto fail_handler;
	}

	printk(KERN_INFO "Done\n");
	printk(KERN_INFO "Assigned minor number: %d\n", echelon_dev.minor);
	return 0;

	fail_handler:
	printk(KERN_INFO "Failed\n");
	return 1;
}

static void __exit modDestroy(void) {
	misc_deregister(&echelon_dev);
	printk(KERN_INFO "Unloaded CacheClear module.\n");
}

module_init(modInit);
module_exit(modDestroy);
