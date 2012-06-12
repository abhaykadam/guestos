#ifndef UTILS_TYPES_H
#define UTILS_TYPES_H

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

#endif
