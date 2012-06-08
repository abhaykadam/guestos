#ifndef	ISR_H
#define ISR_H

#define __NR_IRQ_MAX	256

typedef void (*isr_ptr_t)(void);

extern void init_ivt(void);

extern void isr_ni_handler(void);
extern void isr_div_by_zero(void);

isr_ptr_t isr_table[__NR_IRQ_MAX];


#endif
