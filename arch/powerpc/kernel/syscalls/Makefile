# SPDX-License-Identifier: GPL-2.0
kapi := arch/$(SRCARCH)/include/generated/asm
uapi := arch/$(SRCARCH)/include/generated/uapi/asm

$(shell mkdir -p $(uapi) $(kapi))

syscall := $(src)/syscall.tbl
syshdr := $(srctree)/scripts/syscallhdr.sh
systbl := $(srctree)/scripts/syscalltbl.sh

abis_32  := common,nospu,32
abis_64  := common,nospu,64
abis_spu := common,spu

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --emit-nr --abis $(abis_$*) $< $@

quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis $(abis_$*) $< $@

$(uapi)/unistd_%.h: $(syscall) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(kapi)/syscall_table_%.h: $(syscall) $(systbl) FORCE
	$(call if_changed,systbl)

uapisyshdr-y		+= unistd_32.h unistd_64.h
kapisyshdr-y		+= syscall_table_32.h		\
			   syscall_table_64.h		\
			   syscall_table_spu.h

uapisyshdr-y	:= $(addprefix $(uapi)/, $(uapisyshdr-y))
kapisyshdr-y	:= $(addprefix $(kapi)/, $(kapisyshdr-y))
targets		+= $(addprefix ../../../../, $(uapisyshdr-y) $(kapisyshdr-y))

PHONY += all
all: $(uapisyshdr-y) $(kapisyshdr-y)
	@:
