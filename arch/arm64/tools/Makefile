# SPDX-License-Identifier: GPL-2.0

gen := arch/$(ARCH)/include/generated
kapi := $(gen)/asm
uapi := $(gen)/uapi/asm

syscall32 := $(src)/syscall_32.tbl
syshdr := $(srctree)/scripts/syscallhdr.sh
sysnr := $(srctree)/scripts/syscallnr.sh
systbl := $(srctree)/scripts/syscalltbl.sh

kapisyshdr-y := cpucap-defs.h sysreg-defs.h unistd32.h unistd-nr32.h syscalls32.h
kapi-hdrs-y := $(addprefix $(kapi)/, $(kapisyshdr-y))

targets += $(addprefix ../../../, $(kapi-hdrs-y))

PHONY += kapi

kapi:   $(kapi-hdrs-y)

quiet_cmd_gen_cpucaps = GEN     $@
      cmd_gen_cpucaps = mkdir -p $(dir $@); $(AWK) -f $(real-prereqs) > $@

quiet_cmd_gen_sysreg = GEN     $@
      cmd_gen_sysreg = mkdir -p $(dir $@); $(AWK) -f $(real-prereqs) > $@

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --abis common,$* \
		   --offset __NR_SYSCALL_BASE $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis common,$* $< $@

quiet_cmd_sysnr  = SYSNR   $@
      cmd_sysnr  = $(CONFIG_SHELL) $(sysnr) --prefix compat_ $< $@

$(kapi)/cpucap-defs.h: $(src)/gen-cpucaps.awk $(src)/cpucaps FORCE
	$(call if_changed,gen_cpucaps)

$(kapi)/sysreg-defs.h: $(src)/gen-sysreg.awk $(src)/sysreg FORCE
	$(call if_changed,gen_sysreg)

$(kapi)/unistd32.h: $(syscall32) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/unistd-nr%.h: $(syscall32) $(sysnr) FORCE
	$(call if_changed,sysnr)

$(kapi)/syscalls%.h: $(syscall32) $(systbl) FORCE
	$(call if_changed,systbl)
