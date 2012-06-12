#ifndef DCTRL_H
#define DCTRL_H

#include <pic.h>
#include <fs.h>
#include <bio.h>

struct dctrl {
	pthread_t		dc_thread;	/* points to the thread of disk controller */
	void			*dc_status;
	struct block_device	*dc_bdev;
	pthread_mutex_t		dc_mutex;
	pthread_cond_t		dc_io_req;
	struct bio		*dc_bio;	
};

int init_disk_controller(struct dctrl *dc);
int close_disk_controller(struct dctrl *dc);

static void *disk_controller(void *at_id);

#endif
