# SPDX-License-Identifier: GPL-2.0
out := arch/$(SRCARCH)/include/generated/asm
uapi := arch/$(SRCARCH)/include/generated/uapi/asm

# Create output directory if not already present
$(shell mkdir -p $(out) $(uapi))

syscall32 := $(src)/syscall_32.tbl
syscall64 := $(src)/syscall_64.tbl

syshdr := $(srctree)/scripts/syscallhdr.sh
systbl := $(srctree)/scripts/syscalltbl.sh
offset :=
prefix :=

quiet_cmd_syshdr = SYSHDR  $@
      cmd_syshdr = $(CONFIG_SHELL) $(syshdr) --abis $(abis) --emit-nr \
		$(if $(offset),--offset $(offset)) \
		$(if $(prefix),--prefix $(prefix)) \
		$< $@
quiet_cmd_systbl = SYSTBL  $@
      cmd_systbl = $(CONFIG_SHELL) $(systbl) --abis $(abis) $< $@

quiet_cmd_hypercalls = HYPERCALLS $@
      cmd_hypercalls = $(CONFIG_SHELL) '$<' $@ $(filter-out $<, $(real-prereqs))

$(uapi)/unistd_32.h: abis := i386
$(uapi)/unistd_32.h: $(syscall32) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(out)/unistd_compat_32.h: abis := i386
$(out)/unistd_compat_32.h: prefix := 32_
$(out)/unistd_compat_32.h: $(syscall32) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(uapi)/unistd_x32.h: abis := common,x32
$(uapi)/unistd_x32.h: offset := __X32_SYSCALL_BIT
$(uapi)/unistd_x32.h: $(syscall64) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(uapi)/unistd_64.h: abis := common,64
$(uapi)/unistd_64.h: $(syscall64) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(out)/unistd_compat_x32.h: abis := x32
$(out)/unistd_compat_x32.h: prefix := x32_
$(out)/unistd_compat_x32.h: $(syscall64) $(syshdr) FORCE
	$(call if_changed,syshdr)

$(out)/syscall_table_32.h: abis := i386
$(out)/syscall_table_32.h: $(syscall32) $(systbl) FORCE
	$(call if_changed,systbl)
$(out)/syscall_table_64.h: abis := common,64
$(out)/syscall_table_64.h: $(syscall64) $(systbl) FORCE
	$(call if_changed,systbl)
$(out)/syscall_table_x32.h: abis := common,x32
$(out)/syscall_table_x32.h: $(syscall64) $(systbl) FORCE
	$(call if_changed,systbl)

$(out)/xen-hypercalls.h: $(srctree)/scripts/xen-hypercalls.sh FORCE
	$(call if_changed,hypercalls)

$(out)/xen-hypercalls.h: $(srctree)/include/xen/interface/xen*.h

uapisyshdr-y			+= unistd_32.h unistd_64.h unistd_x32.h
syshdr-y			+= syscall_table_32.h
syshdr-$(CONFIG_X86_64)		+= unistd_compat_32.h unistd_compat_x32.h
syshdr-$(CONFIG_X86_64)		+= syscall_table_64.h
syshdr-$(CONFIG_X86_X32_ABI)	+= syscall_table_x32.h
syshdr-$(CONFIG_XEN)		+= xen-hypercalls.h

uapisyshdr-y	:= $(addprefix $(uapi)/, $(uapisyshdr-y))
syshdr-y	:= $(addprefix $(out)/, $(syshdr-y))
targets		+= $(addprefix ../../../../, $(uapisyshdr-y) $(syshdr-y))

PHONY += all
all: $(uapisyshdr-y) $(syshdr-y)
	@:
