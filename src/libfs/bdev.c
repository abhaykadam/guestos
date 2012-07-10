#include <bdev.h>
#include <dlist.h>

LIST_HEAD(block_devices);

static void __add_blkdev (const struct block_device *bdev) {
	dlist_add_tail(&bdev->bd_list, &block_devices);
}

void add_blkdev (const struct block_device *bdev) {
	__add_blkdev (bdev);
}
