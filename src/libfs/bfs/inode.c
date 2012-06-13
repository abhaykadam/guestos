#include <bio.h>

static struct bfs_inode *__bfs_get_inode(struct super_block *sb,
	unsigned long ino, struct buffer_head *bh) {

	struct bio *bio;
	bio->bi_sector = BFS_ITABLE_FBLOCK(sb) + 
			(ino / BFS_INODES_PER_BLOCK(sb)) 
			* BFS_BLOCK_SIZE(sb);

	bio->bi_bdev = sb->s_bdev;
	bio->bi_size = BFS_BLOCK_SIZE(sb);
	bio->bi_ops = &biops;	
	bio->bi_type = BI_read;
	bio->bi_buff = bh;

	
}


struct bfs_inode *bfs_get_inode(struct super_block *sb,
	unsigned long ino, struct buffer_head *bh) {

	return __bfs_get_inode(sb, ino, bh);
}
