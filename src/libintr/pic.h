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
	__NR_div_zero,			/* divide-by-zero */
	__NR_debuger,			/* debugger call (single-step) */
	__NR_nmi,			/* non-maskable interrupt */
	__NR_breakpoint,		/* breakpoint */ 
	__NR_into,			/* overflow */
	__NR_bounds,			/* bound range exceeded */
	__NR_invalid_opcode,		/* invalid opecodedevice not available */
	__NR_device_unavail,		/* device not available */
	__NR_double_fault,		/* double fault */
	__NR_cp_seg_overrun,		/* coprossessor segment overrun */
	__NR_invalid_tss,		/* invalid task state segment */
	__NR_seg_absent,		/* segment not present */
	__NR_stack_fault,		/* stack exception */
	__NR_genrl_protection,		/* general protection fault */
	__NR_page_fault,		/* page fault */
	__NR_reserved,			/* reserved */
	__NR_fpe,			/* floating-point error */
	__NR_alignmnt_check,		/* alignment check */
	__NR_machine_check,		/* machine check */
	__NR_simd_fpe,			/* simd floating point exception */
	__NR_disk_irq=14,		/* interrupt request (irq) line for disk */
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
