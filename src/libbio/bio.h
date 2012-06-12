#ifndef BIO_H
#define BIO_H

#include <fs.h>
#include <buffer_head.h>
#include <types.h>

enum bio_type {
	BI_read,
	BI_write
};

struct bio {
	sector_t		bi_sector;	/* first sector on disk of i/o operation */
	struct block_device	*bi_bdev;	/* pointer to the block descriptor device */
	blksize_t		bi_size;	/* size of data to transfer */
	struct bio_operations	*bi_ops;	/* set of operation pointers */
	enum bio_type		bi_type;	/* type of i/o operation */
	struct buffer_head	*bi_buff;	/* kernel buffer */
};

struct bio_operations {
	int (*read_block) (struct bio *bio);
	int (*write_block) (struct bio *bio);
};

extern struct bio_operations biops;

#endif
