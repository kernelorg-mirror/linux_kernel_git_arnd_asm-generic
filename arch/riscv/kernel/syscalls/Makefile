# SPDX-License-Identifier: GPL-2.0
kapi := arch/$(SRCARCH)/include/generated/asm
uapi := arch/$(SRCARCH)/include/generated/uapi/asm

$(shell mkdir -p $(uapi) $(kapi))

syscall := include/uapi/asm-generic/unistd.h
syshdr := $(srctree)/scripts/syscallhdr.sh
systbl := $(srctree)/scripts/syscalltbl.sh

abis_32 := common,riscv,32,mmu,clone3,memfd_secret
abis_64 := common,riscv,64,newstat,rlimit,mmu,clone3,memfd_secret

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --abis ${abis_$*} --emit-nr $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis ${abis_$*} $< $@

$(uapi)/unistd_%.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/syscall_table_%.h: $(syscall) $(systbl) FORCE
	$(call if_changed,systbl)

uapisyshdr-y		+= unistd_32.h unistd_64.h
kapisyshdr-y		+= syscall_table_32.h		\
			   syscall_table_64.h

uapisyshdr-y	:= $(addprefix $(uapi)/, $(uapisyshdr-y))
kapisyshdr-y	:= $(addprefix $(kapi)/, $(kapisyshdr-y))
targets		+= $(addprefix ../../../../, $(uapisyshdr-y) $(kapisyshdr-y))

PHONY += all
all: $(uapisyshdr-y) $(kapisyshdr-y)
	@:
