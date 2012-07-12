#ifndef BUFFER_HEAD
#define BUFFER_HEAD

#include <types.h>

enum bh_state_bits{
	BH_Uptodate,				/* contains valid data */
	BH_Dirty,				/* is dirty */
	BH_Req,					/* has been submitted for i/o */
};

struct buffer_head {
	unsigned long		b_state;	/* buffer state flags */
	sector_t		b_blocknr;	/* start  block number */
	char 			*b_data;	/* pointer to data */
	struct block_device 	*b_dev;		
	atomic_t		b_count;	/* users using thing buffer-head */
};

#endif
