#include <bio.h>
#include <buffer_head.h>
#include <types.h>
#include <fcntl.h>
#include <unistd.h>

static int read_dblock (struct bio *bio) {
	const char *disk_name = bio->bi_bdev->bd_name;
	char *buffer = bio->bi_buff->b_data;
	blksize_t blk_size = bio->bi_size;
	sector_t blk_off= bio->bi_sector*blk_size;

	if (buffer ==0)
		return -1;

	int fd = open(disk_name, O_RDONLY);
	if(fd == -1)
		return -1;

	int ret = pread(fd, buffer, blk_size, blk_off);
	if (ret == -1)
		return -1;

	return 0;
}


static int write_dblock (struct bio *bio) {
	const char *disk_name = bio->bi_bdev->bd_name;
	char *buffer = bio->bi_buff->b_data;
	blksize_t blk_size = bio->bi_size;
	sector_t blk_off= bio->bi_sector*blk_size;

	if (buffer ==0)
		return -1;

	int fd = open(disk_name, O_WRONLY);
	if(fd == -1)
		return -1;

	int ret = pwrite(fd, buffer, blk_size, blk_off);
	if (ret == -1)
		return -1;

	return 0;	
}

struct bio_operations biops = {
	.read_block	= read_dblock,
	.write_block	= write_dblock
};
