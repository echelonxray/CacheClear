// SPDX-License-Identifier: GPL-2.0
/**
 * Copyright (c) 2023 Michael T. Kloos <michael@michaelkloos.com>
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL-2.0");
MODULE_AUTHOR("Michael T. Kloos");
MODULE_DESCRIPTION("Adds a simple syscall to run the WBINVD instruction for benchmarking.  "
                   "May not be safe and should only be loaded when need.  ");
MODULE_VERSION("0.1");

static int __init modInit(void) {
    printk(KERN_INFO "Loading CacheClear module.\n");
    return 0;
}

static void __exit modDestroy(void) {
    printk(KERN_INFO "Unloading CacheClear module.\n");
}

module_init(modInit);
module_exit(modDestroy);
