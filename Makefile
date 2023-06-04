# SPDX-License-Identifier: GPL-2.0

#
# Copyright (c) 2023 Michael T. Kloos <michael@michaelkloos.com>
#

obj-m = CacheClear.o
all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
