#ifndef PIC_H
#define PIC_H

#include <inttypes.h>
#include <pthread.h>
#include <stdbool.h>

#define __NR_INTR_MAX		256
#define __NR_INTR_MASK_MIN	32
#define __NR_INTR_MASK_MAX	255

typedef void (*isr_ptr_t)(void);

/* 
 *Interrupt vectors 
 */
enum {
	__NR_div_zero,			/* 0 - divide-by-zero */
	__NR_debuger,			/* 1 - debugger call (single-step) */
	__NR_nmi,			/* 2 - non-maskable interrupt */
	__NR_breakpoint,		/* 3 - breakpoint */ 
	__NR_into,			/* 4 - overflow */
	__NR_bounds,			/* 5 - bound range exceeded */
	__NR_invalid_opcode,		/* 6 - invalid opecodedevice not available */
	__NR_device_unavail,		/* 7 - device not available */
	__NR_double_fault,		/* 8 - double fault */
	__NR_cp_seg_overrun,		/* 9 - coprossessor segment overrun */
	__NR_invalid_tss,		/* 10 - invalid task state segment */
	__NR_seg_absent,		/* 11 - segment not present */
	__NR_stack_fault,		/* 12 - stack exception */
	__NR_genrl_protection,		/* 13 - general protection fault */
	__NR_page_fault,		/* 14 - page fault */
	__NR_reserved,			/* 15 - reserved */
	__NR_fpe,			/* 16 - floating-point error */
	__NR_alignmnt_check,		/* 17 - alignment check */
	__NR_machine_check,		/* 18 - machine check */
	__NR_simd_fpe,			/* 19 - simd floating point exception */
	__NR_disk_irq=46,		/* interrupt request (irq) line for disk */
};

/*
 * A bitmap for registering raised interrupt
 * requests. The system can handle total of
 * 256 interrupt requests or intrs 
 */

struct intr_line {
	uint64_t	intr[4];	/* for total of 256 intrrupt lines */
	bool		intr_masked;	/* masked interrupt flag. (only
					   interrupts in the range 32-255 can be masked) */
	pthread_mutex_t	intr_mutex;	/* use to protect interrupt bitmap */
	
} intr_line;

int raise_intr(int intr_num);


#endif
