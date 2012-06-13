#include <isr.h>

void init_ivt(void) {
		isr_table[__NR_div_zero] = isr_div_by_zero;
		isr_table[__NR_disk_irq] = isr_disk_irq;
}
