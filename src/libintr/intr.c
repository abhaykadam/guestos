#include <isr.h>

void init_ivt(void) {
		isr_table[__NR_div_zero] = isr_div_by_zero;
}
