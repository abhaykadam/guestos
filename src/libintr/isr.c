#include <isr.h>
#include <m2skernel.h>	

extern struct ctx_t *isa_ctx;

void isr_ni_handler(void) {
	printf("Just a dummy handler\n");

	return;
}

void isr_div_by_zero(void) {

	ctx_finish(isa_ctx, ctx_zombie);

	printf ("Process %d terminated due to divide-by-zero\n", isa_ctx->pid);

	return;
}

void isr_disk_irq() {
	
}
