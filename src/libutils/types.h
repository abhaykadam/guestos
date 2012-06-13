#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H

#include <stddef.h>

/*
 * The definitions in this header file
 * is borrowed from Linux kernel
 */

typedef struct {
        int counter;
} atomic_t;

#ifdef CONFIG_64BIT
typedef struct {
        long counter;
} atomic64_t;
#endif

/*
 * atomic_read - read atomic variable
 * @v: pointer of type atomic_t
 *
 * Atomically reads the value of @v
 */
static inline int atomic_read(const atomic_t *v) {
	return (*(volatile int *)&(v)->counter);
}

/*
 * The type is used for indexing on 
 * a disk or disk partition
 */;
typedef unsigned long sector_t;

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({                      \
	const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif
