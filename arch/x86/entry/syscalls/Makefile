# SPDX-License-Identifier: GPL-2.0
out := arch/$(SRCARCH)/include/generated/asm

# Create output directory if not already present
$(shell mkdir -p $(out))

quiet_cmd_hypercalls = HYPERCALLS $@
      cmd_hypercalls = $(CONFIG_SHELL) '$<' $@ $(filter-out $<, $(real-prereqs))

$(out)/xen-hypercalls.h: $(srctree)/scripts/xen-hypercalls.sh FORCE
	$(call if_changed,hypercalls)

$(out)/xen-hypercalls.h: $(srctree)/include/xen/interface/xen*.h

syshdr-$(CONFIG_XEN)		+= xen-hypercalls.h

syshdr-y	:= $(addprefix $(out)/, $(syshdr-y))
targets		+= $(addprefix ../../../../, $(syshdr-y))

PHONY += all
all: $(syshdr-y)
	@:
