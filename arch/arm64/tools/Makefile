# SPDX-License-Identifier: GPL-2.0

gen := arch/$(ARCH)/include/generated
kapi := $(gen)/asm
uapi := $(gen)/uapi/asm

syscall-32 := $(src)/syscall_32.tbl
syscall-64 := $(obj)/syscall_64.tbl
ABIS_unistd32.h := common,32
ABIS_unistd64.h := common,64,renameat,newstat,rlimit,mmu,clone3,memfd_secret --emit-nr
ABIS_syscalls32.h := common,32
ABIS_syscalls64.h := common,64,renameat,newstat,rlimit,mmu,clone3,memfd_secret
syshdr := $(srctree)/scripts/syscallhdr.sh
sysnr := $(srctree)/scripts/syscallnr.sh
systbl := $(srctree)/scripts/syscalltbl.sh

kapisyshdr-y := cpucap-defs.h sysreg-defs.h unistd32.h unistd-nr32.h syscalls32.h syscalls64.h
uapisyshdr-y := unistd64.h
kapi-hdrs-y := $(addprefix $(kapi)/, $(kapisyshdr-y))
uapi-hdrs-y := $(addprefix $(uapi)/, $(uapisyshdr-y))

targets += $(addprefix ../../../, $(kapi-hdrs-y) $(uapi-hdrs-y))

PHONY += kapi uapi

all: $(syscall64) kapi uapi

kapi:   $(kapi-hdrs-y)
uapi:   $(uapi-hdrs-y)

quiet_cmd_gen_cpucaps = GEN     $@
      cmd_gen_cpucaps = mkdir -p $(dir $@); $(AWK) -f $(real-prereqs) > $@

quiet_cmd_gen_sysreg = GEN     $@
      cmd_gen_sysreg = mkdir -p $(dir $@); $(AWK) -f $(real-prereqs) > $@

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --abis $(ABIS_$(notdir $@)) $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis $(ABIS_$(notdir $@)) $< $@

quiet_cmd_sysnr  = SYSNR   $@
      cmd_sysnr  = $(CONFIG_SHELL) $(sysnr) --prefix compat_ $< $@

quiet_cmd_cpp_tbl_h = SYSTBL  $@
      cmd_cpp_tbl_h = $(CPP) $(cpp_flags) -P -D__GEN_SYSCALL_TBL -o $@ $<

$(kapi)/cpucap-defs.h: $(src)/gen-cpucaps.awk $(src)/cpucaps FORCE
	$(call if_changed,gen_cpucaps)

$(kapi)/sysreg-defs.h: $(src)/gen-sysreg.awk $(src)/sysreg FORCE
	$(call if_changed,gen_sysreg)

$(kapi)/unistd32.h: $(syscall-32) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(uapi)/unistd64.h: $(syscall-64) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/unistd-nr32.h: $(syscall-32) $(sysnr) FORCE
	$(call if_changed,sysnr)

$(kapi)/syscalls32.h: $(syscall-32) $(systbl) FORCE
	$(call if_changed,systbl)

$(kapi)/syscalls64.h: $(syscall-64) $(systbl) FORCE
	$(call if_changed,systbl)

CPPFLAGS_syscall_64.lds := -D __GEN_SYSCALL_TBL

$(obj)/syscall_64.tbl: $(srctree)/include/uapi/asm-generic/unistd.h FORCE
	$(call if_changed_dep,cpp_tbl_h)
