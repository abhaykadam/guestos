#ifndef BITOPS_H
#define BITOPS_H

#define LOCK_PREFIX "\n\tlock; "

static inline void set_bit32(int nr, volatile void *addr) {
	asm volatile (LOCK_PREFIX "btsl %1,%0" 
			: "+m" (*(uint32_t *)addr) 
			: "Ir" (nr)
	);
}

static inline void set_bit64(int nr, volatile void *addr) {
	asm volatile (LOCK_PREFIX "btsl %1,%0" 
			: "+m" (*(uint64_t *)addr) 
			: "Jr" (nr)
	);
}

static inline void clear_bit32(int nr, volatile void *addr) {
	asm volatile (LOCK_PREFIX "btr %1,%0" 
			: "+m" (*(uint64_t *)addr) 
			: "Ir" (nr)
	);
}

static inline void clear_bit64(int nr, volatile void *addr) {
	asm volatile (LOCK_PREFIX "btr %1,%0" 
			: "+m" (*(uint64_t *)addr) 
			: "Jr" (nr)
	);
}

static inline int test_and_clear_bit32(int nr, volatile void *addr) {
	int oldbit;

	asm volatile (LOCK_PREFIX "btr %2,%1\n\t"
			"sbb %0,%0"
			: "=r" (oldbit), "+m" (*(uint64_t *)addr) 
			: "Ir" (nr) : "memory"
	);

	return oldbit;
}

static inline int test_and_clear_bit64(int nr, volatile void *addr) {
	int oldbit;

	asm volatile (LOCK_PREFIX "btr %2,%1\n\t"
			"sbb %0,%0"
			: "=r" (oldbit), "+m" (*(uint64_t *)addr) 
			: "Jr" (nr) : "memory"
	);

	return oldbit;
}


#endif
