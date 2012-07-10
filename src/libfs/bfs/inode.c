#include <bio.h>
#include <bfs_fs.h>
#include <memory.h>

static inline void __inode_copy (struct bfs_inode *dest, 
	struct bfs_inode *src) {
	memcpy(dest, src, sizeof(struct bfs_inode));
}

inline void inode_copy (struct bfs_inode *dest, 
	struct bfs_inode *src){
	
	__inode_copy(dest, src);
}

static struct bfs_inode *__bfs_get_inode(struct super_block *sb,
	unsigned long ino, struct buffer_head *bh) {

	struct bio *bio;
	bio = (struct bio *)
		malloc(sizeof(struct bio));

	bio->bi_sector = bfs_itable_fblock(sb) + 
			(ino / bfs_inodes_per_block(sb)) 
			* bfs_block_size(sb);

	bio->bi_bdev = sb->s_bdev;
	bio->bi_size = bfs_block_size(sb);
	bio->bi_ops = &biops;	
	bio->bi_type = BI_read;
	bio->bi_buff = bh;

	kbuffer_io(bio)	;

	struct bfs_inode *the_inode = (struct bfs_inode *) bio->bi_buff
		+ (ino % bfs_inodes_per_block(sb))
		* sizeof(struct bfs_inode);

	free(bio);
	return the_inode;
}


struct bfs_inode *bfs_get_inode(struct super_block *sb,
	unsigned long ino, struct buffer_head *bh) {

	return __bfs_get_inode(sb, ino, bh);
}
