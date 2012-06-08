#include <isr.h>

void init_ivt(void) {
		isr_table[0] = isr_div_by_zero;
}
