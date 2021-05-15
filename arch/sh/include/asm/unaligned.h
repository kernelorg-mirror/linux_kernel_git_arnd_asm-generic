/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __ASM_SH_UNALIGNED_H
#define __ASM_SH_UNALIGNED_H

#include <asm-generic/unaligned.h>

#ifdef CONFIG_CPU_SH4A
/*
 * SH-4A has support for unaligned 32-bit loads, and 32-bit loads only.
 * Support for 64-bit accesses are done through shifting and masking
 * relative to the endianness. Unaligned stores are not supported by the
 * instruction encoding, so these continue to use the packed
 * struct.
 *
 * The same note as with the movli.l/movco.l pair applies here, as long
 * as the load is guaranteed to be inlined, nothing else will hook in to
 * r0 and we get the return value for free.
 *
 * NOTE: Due to the fact we require r0 encoding, care should be taken to
 * avoid mixing these heavily with other r0 consumers, such as the atomic
 * ops. Failure to adhere to this can result in the compiler running out
 * of spill registers and blowing up when building at low optimization
 * levels. See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34777.
 */
static __always_inline u32 sh4a_get_unaligned_cpu32(const u8 *p)
{
	unsigned long unaligned;

	__asm__ __volatile__ (
		"movua.l	@%1, %0\n\t"
		 : "=z" (unaligned)
		 : "r" (p)
	);

	return unaligned;
}

/*
 * Even though movua.l supports auto-increment on the read side, it can
 * only store to r0 due to instruction encoding constraints, so just let
 * the compiler sort it out on its own.
 */
static inline u64 sh4a_get_unaligned_cpu64(const u8 *p)
{
#ifdef __LITTLE_ENDIAN
	return (u64)sh4a_get_unaligned_cpu32(p + 4) << 32 |
		    sh4a_get_unaligned_cpu32(p);
#else
	return (u64)sh4a_get_unaligned_cpu32(p) << 32 |
		    sh4a_get_unaligned_cpu32(p + 4);
#endif
}

static inline u32 sh4a_get_unaligned_le32(const void *p)
{
	return le32_to_cpu(sh4a_get_unaligned_cpu32(p));
}

static inline u64 sh4a_get_unaligned_le64(const void *p)
{
	return le64_to_cpu(sh4a_get_unaligned_cpu64(p));
}

static inline u32 sh4a_get_unaligned_be32(const void *p)
{
	return be32_to_cpu(sh4a_get_unaligned_cpu32(p));
}

static inline u64 sh4a_get_unaligned_be64(const void *p)
{
	return be64_to_cpu(sh4a_get_unaligned_cpu64(p));
}

#define get_unaligned_le32(p) sh4a_get_unaligned_le32(p)
#define get_unaligned_le64(p) sh4a_get_unaligned_le64(p)
#define get_unaligned_be32(p) sh4a_get_unaligned_be32(p)
#define get_unaligned_be64(p) sh4a_get_unaligned_be64(p)

#endif /* CONFIG_CPU_SH4A */
#endif /* __ASM_SH_UNALIGNED_SH4A*/
