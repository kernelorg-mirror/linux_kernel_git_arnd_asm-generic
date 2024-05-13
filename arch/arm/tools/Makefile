# SPDX-License-Identifier: GPL-2.0
#
# linux/arch/arm/tools/Makefile
#
# Copyright (C) 2001 Russell King
#

gen := arch/$(ARCH)/include/generated
kapi := $(gen)/asm
sysnr := $(src)/syscallnr.sh
syscall := $(src)/syscall.tbl

kapi-hdrs-y := $(kapi)/unistd-nr.h
kapi-hdrs-y += $(kapi)/mach-types.h

targets += $(addprefix ../../../,$(gen-y) $(kapi-hdrs-y))

PHONY += kapi

kapi:	$(kapi-hdrs-y) $(gen-y)

# Create output directory if not already present
$(shell mkdir -p $(kapi))

quiet_cmd_gen_mach = GEN     $@
      cmd_gen_mach = $(AWK) -f $(real-prereqs) > $@

$(kapi)/mach-types.h: $(src)/gen-mach-types $(src)/mach-types FORCE
	$(call if_changed,gen_mach)

# custom __NR_syscalls definition for aligning table size
quiet_cmd_sysnr  = SYSNR   $@
      cmd_sysnr  = $(CONFIG_SHELL) $(sysnr) $< $@

$(kapi)/unistd-nr.h: $(syscall) $(sysnr) FORCE
	$(call if_changed,sysnr)
