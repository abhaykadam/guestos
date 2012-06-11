#ifndef	ISR_H
#define ISR_H

#include <pic.h>

/* Initializes interrupt vector table(IVT) */
extern void init_ivt(void);

/* Interrupt service routines(ISR) */
extern void isr_ni_handler(void);
extern void isr_div_by_zero(void);

/* The table for storing ISRs addresses */
isr_ptr_t isr_table[__NR_INTR_MAX];


#endif
