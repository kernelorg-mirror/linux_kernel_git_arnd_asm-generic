# SPDX-License-Identifier: GPL-2.0

GENERIC_VDSO_MK_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
GENERIC_VDSO_DIR := $(dir $(GENERIC_VDSO_MK_PATH))

c-gettimeofday-$(CONFIG_GENERIC_GETTIMEOFDAY) := $(addprefix $(GENERIC_VDSO_DIR), gettimeofday.c)

# This cmd checks that the vdso library does not contain dynamic relocations.
# It has to be called after the linking of the vdso library and requires it
# as a parameter.
#
# As a workaround for some GNU ld ports which produce unneeded R_*_NONE
# dynamic relocations, ignore R_*_NONE.
quiet_cmd_vdso_check = VDSOCHK $@
      cmd_vdso_check = :
