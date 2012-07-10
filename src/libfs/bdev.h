#ifndef BDEV_H
#define BDEV_H

#include <dlist.h>
#include <sys/types.h>

struct block_device{
	dev_t			bd_dev;
	struct super_block	*bd_super;
	unsigned		bd_block_size;
	const char		*bd_name;
	struct list_head	bd_list;
};

extern void add_blkdev (const struct block_device *bdev);

#endif
