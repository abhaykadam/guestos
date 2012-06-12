#include <pic.h>

static inline bool irq_masked(intr) {
	return intr >= __NR_INTR_MASK_MIN 
		&& intr <= __NR_INTR_MASK_MAX
		&& intr_line.intr_masked;
}		

static inline void set_bit(int nr, void *addr) {
	asm volatile ("btsl %1,%0" 
			: "+m" (*(uint64_t *)addr) 
			: "Jr" (nr)
	);
}

static void reset_all_intrs(void) {
	pthread_mutex_lock(&intr_line.intr_mutex);

	/* reset all interrupt lines. i.e.,
	   set them to zero */
	intr_line.intr[0] = 0;
	intr_line.intr[1] = 0;
	intr_line.intr[2] = 0;
	intr_line.intr[3] = 0;

	/* unmaked the interrupts */
	intr_line.intr_masked = false;

	pthread_mutex_unlock(&intr_line.intr_mutex);
}

void init_pic(void) {
	/* initialize mutex for the intr bitmap */
	pthread_mutex_init(&intr_line.intr_mutex, NULL);
	
	reset_all_intrs();
}

int raise_intr(int intr_num) {
	pthread_mutex_lock(&intr_line.intr_mutex);

	if (irq_masked(intr_num));
		return -1;

	if (intr_num < 64) {
		set_bit(intr_num, &intr_line.intr[0]);
	} else if (intr_num >= 64 && intr_num < 128) {
		set_bit(intr_num%64, &intr_line.intr[1]);	
	} else if (intr_num >= 128 && intr_num < 192) {
		set_bit(intr_num%128, &intr_line.intr[2]);	
	} else {
		set_bit(intr_num%192, &intr_line.intr[3]);	
	}

	pthread_mutex_unlock(&intr_line.intr_mutex);
	
	return 0;
}
