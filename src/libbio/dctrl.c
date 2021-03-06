#include <dctrl.h>
#include <pthread.h>
#include <signal.h>
#include <bio.h>
#include <pic.h>
#include <stdbool.h>

int init_disk_controller(struct dctrl *dc) {
	int rc;

	/* initialize mutext and condition variable 
		for disk controller */
	pthread_mutex_init(&dc->dc_mutex, NULL);
	pthread_cond_init (&dc->dc_io_req, NULL);

	/* create a disk controller thread */
	rc = pthread_create(&dc->dc_thread, NULL, disk_controller, dc);
	if (rc)
		return -1;
	
	return 0;	
}

int close_disk_controller(struct dctrl *dc) {
	pthread_kill(dc->dc_thread, SIGTERM);
	
	pthread_join(dc->dc_thread, &dc->dc_status);		

	pthread_exit(NULL);
}

static void dcontroller_terminate(int param) {
	/* currently does nothing */
	return;
}

static void *disk_controller(void *a_dc) {
	/* registers a sigterm handler */
	signal(SIGTERM, dcontroller_terminate);

	struct dctrl *dc = (struct dctrl *)a_dc;

	while (true) {
		pthread_mutex_lock(&dc->dc_mutex);
	
		/* registers the handles for the i/o operations */	
		dc->dc_bio->bi_ops = &biops;
		struct bio_operations *io = dc->dc_bio->bi_ops;
	
		/* wait for i/o request from the kernel */
		pthread_cond_wait( &dc->dc_io_req, &dc->dc_mutex);
	
		/* checking with what kernel wants */
		switch(dc->dc_bio->bi_type) {
		case BI_read:
			/* if the kernel asked to read something */
			(io->read_block)(dc->dc_bio);
			break;

		case BI_write:
			/* if the kernel asked to write something */
			(io->write_block)(dc->dc_bio);
			break;
		}

		/* inform kernel that its task is served */	
		raise_intr(__NR_disk_irq);

		pthread_mutex_unlock(&dc->dc_mutex);
	}


	pthread_exit(NULL);
}
