#include <bio.h>
#include <dctrl.h>
#include <pthread.h>

extern struct dctrl dc;

void kbuffer_io(struct bio *bio) {

	pthread_mutex_lock(&dc.dc_mutex);

	dc.dc_bio = bio;
	dc.dc_bdev = bio->bi_bdev;
	dc.dc_bio->bi_finished = false;

	/* signal disk conroller to start the i/o */
	pthread_cond_signal(&dc.dc_io_req);

	pthread_mutex_unlock(&dc.dc_mutex);

	/* busy waiting for i/o completion.
	tried too many times to avoid this.
	but, finally!
	*/
	while (dc.dc_bio->bi_finished==false)
		;
}
