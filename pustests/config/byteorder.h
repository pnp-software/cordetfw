/**
 * @file   byteorder.h
 * @author Armin Luntzer (armin.luntzer@univie.ac.at),
 * @date   2015
 *
 * @copyright GPLv2
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * This is a set of macros for consistent endianess conversion. They work
 * for both little and big endian cpus.
 *
 * conversion of XX-bit integers (16- or 32-) between native CPU format
 * and little/big endian format:
 *	cpu_to_[bl]eXX(uintXX_t x)
 *	[bl]eXX_to_cpu(uintXX_t x)
 *
 * the same, but change in situ:
 *	cpu_to_[bl]eXXs(uintXX_t x)
 *	[bl]eXX_to_cpus(uintXX_t x)
 *
 *
 * This is based on the byte order macros from the linux kernel, see:
 * include/linux/byteorder/generic.h
 * include/uapi/linux/swab.h
 * include/uapi/linux/byteorder/big_endian.h
 * include/uapi/linux/byteorder/little_endian.h
 * by @author Linus Torvalds et al.
 *
 */
#ifndef BYTEORDER_H
#define BYTEORDER_H

#include <stdint.h>



#ifdef __BIG_ENDIAN
#undef __BIG_ENDIAN
#endif

#ifdef __LITTLE_ENDIAN
#undef __LITTLE_ENDIAN
#endif

#if (__sparc__)
#ifndef __BIG_ENDIAN
#define __BIG_ENDIAN 4321
#endif
#endif

#if (__i386__ || __x86_64__)
#ifndef __LITTLE_ENDIAN
#define __LITTLE_ENDIAN 1234
#endif
#endif


#define ___constant_swab16(x) ((uint16_t)(			\
	(((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |		\
	(((uint16_t)(x) & (uint16_t)0xff00U) >> 8)))

#define ___constant_swab32(x) ((uint32_t)(			\
	(((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |	\
	(((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |	\
	(((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |	\
	(((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24)))


#ifdef USE_BUILTIN_BSWAP
#if GCC_VERSION >= 40400
#define __HAVE_BUILTIN_BSWAP32__
#endif
#if GCC_VERSION >= 40800
#define __HAVE_BUILTIN_BSWAP16__
#endif
#endif /* USE_BUILTIN_BSWAP */


static inline __attribute__((const)) uint16_t __fswab16(uint16_t val)
{
#ifdef __HAVE_BUILTIN_BSWAP16__
  return __builtin_bswap16(val);
#else
  return ___constant_swab16(val);
#endif
}


static inline __attribute__((const)) uint32_t __fswab32(uint32_t val)
{
#ifdef __HAVE_BUILTIN_BSWAP32__
  return __builtin_bswap32(val);
#else
  return ___constant_swab32(val);
#endif
}


/**
 * @brief return a byteswapped 16-bit value
 * @param x value to byteswap
 */

#define __swab16(x)				\
	(__builtin_constant_p((uint16_t)(x)) ?	\
	___constant_swab16(x) :			\
	__fswab16(x))


/**
 * @brief return a byteswapped 32-bit value
 * @param x a value to byteswap
 */

#define __swab32(x)				\
	(__builtin_constant_p((uint32_t)(x)) ?	\
	___constant_swab32(x) :			\
	__fswab32(x))


/**
 * @brief return a byteswapped 16-bit value from a pointer
 * @param p a pointer to a naturally-aligned 16-bit value
 */
static inline uint16_t __swab16p(const uint16_t *p)
{
  return __swab16(*p);
}


/**
 * @brief return a byteswapped 32-bit value from a pointer
 * @param p a pointer to a naturally-aligned 32-bit value
 */
static inline uint32_t __swab32p(const uint32_t *p)
{
  return __swab32(*p);
}


/**
 * @brief byteswap a 16-bit value in-place
 * @param p a pointer to a naturally-aligned 16-bit value
 */

static inline void __swab16s(uint16_t *p)
{
  *p = __swab16p(p);
}


/**
 * @brief byteswap a 32-bit value in-place
 * @param p a pointer to a naturally-aligned 32-bit value
 */

static inline void __swab32s(uint32_t *p)
{
  *p = __swab32p(p);
}



#ifdef __BIG_ENDIAN

#define __cpu_to_le16(x)   ((uint16_t)__swab16((x)))
#define __cpu_to_le32(x)   ((uint32_t)__swab32((x)))

#define __cpu_to_le16s(x)  __swab16s((x))
#define __cpu_to_le32s(x)  __swab32s((x))

#define __cpu_to_be16(x)   ((uint16_t)(x))
#define __cpu_to_be32(x)   ((uint32_t)(x))

#define __cpu_to_be16s(x)  { (void)(x); }
#define __cpu_to_be32s(x)  { (void)(x); }



#define __le16_to_cpu(x)   __swab16((uint16_t)(x))
#define __le32_to_cpu(x)   __swab32((uint32_t)(x))

#define __le16_to_cpus(x)  __swab16s((x))
#define __le32_to_cpus(x)  __swab32s((x))

#define __be16_to_cpu(x)   ((uint16_t)(x))
#define __be32_to_cpu(x)   ((uint32_t)(x))

#define __be16_to_cpus(x)  { (void)(x); }
#define __be32_to_cpus(x)  { (void)(x); }

#endif /* __BIG_ENDIAN */


#ifdef __LITTLE_ENDIAN

#define __cpu_to_le16(x)   ((uint16_t)(x))
#define __cpu_to_le32(x)   ((uint32_t)(x))

#define __cpu_to_le16s(x)  { (void)(x); }
#define __cpu_to_le32s(x)  { (void)(x); }

#define __cpu_to_be16(x)   ((uint16_t)__swab16((x)))
#define __cpu_to_be32(x)   ((uint32_t)__swab32((x)))

#define __cpu_to_be16s(x)  __swab16s((x))
#define __cpu_to_be32s(x)  __swab32s((x))



#define __le16_to_cpu(x)  ((uint16_t)(x))
#define __le32_to_cpu(x)  ((uint32_t)(x))

#define __le32_to_cpus(x) { (void)(x); }
#define __le16_to_cpus(x) { (void)(x); }

#define __be16_to_cpu(x)  __swab16((uint16_t)(uint16_t)(x))
#define __be32_to_cpu(x)  __swab32((uint32_t)(uint32_t)(x))

#define __be16_to_cpus(x) __swab16s((x))
#define __be32_to_cpus(x) __swab32s((x))

#endif /* __LITTLE_ENDIAN */



/** these are the conversion macros */

/** convert cpu order to little endian */
#define cpu_to_le16  __cpu_to_le16
#define cpu_to_le32  __cpu_to_le32

/** in-place convert cpu order to little endian */
#define cpu_to_le16s __cpu_to_le16s
#define cpu_to_le32s __cpu_to_le32s

/** convert cpu order to big endian */
#define cpu_to_be16  __cpu_to_be16
#define cpu_to_be32  __cpu_to_be32

/** in-place convert cpu order to big endian */
#define cpu_to_be16s __cpu_to_be16s
#define cpu_to_be32s __cpu_to_be32s


/* same, but in reverse */

/** convert little endian to cpu order*/
#define le16_to_cpu  __le16_to_cpu
#define le32_to_cpu  __le32_to_cpu

/** in-place convert little endian to cpu order*/
#define le16_to_cpus __le16_to_cpus
#define le32_to_cpus __le32_to_cpus

/** convert big endian to cpu order*/
#define be16_to_cpu  __be16_to_cpu
#define be32_to_cpu  __be32_to_cpu

/** in-place convert big endian to cpu order*/
#define be16_to_cpus __be16_to_cpus
#define be32_to_cpus __be32_to_cpus



#endif /* BYTEORDER_H */
