#include <fs.h>
#include <buffer_head.h>
#include <bfs.h>
#include <bfs_fs.h>
#include <bio.h>
#include <types.h>
#include <dlist.h>
#include <stdlib.h>

/**
 * bfs_alloc_inode - creates a new inode
 * @sb: parent superblock for the inode
 *
 * A new inode is created under given superblock
 */

static struct inode *bfs_alloc_inode(struct super_block *sb) {
	struct inode *inode;

	inode = (struct inode *) malloc (sizeof(struct inode));

	if (inode==NULL)
		return NULL;

	
	return inode;
}

/**
 * bfs_destroy_inode - removes inode from memory
 * @inode: the inode to be detroyed
 *
 * First, the given inode is deleted from the
 * alive list of inodes, and then it's "free"d
 * from the memory
 */

static void bfs_destroy_inode(struct inode *inode) {
	dlist_del(&inode->i_list);
	free(inode);
}

/**
 * bfs_write_inode - writes inode to the volume
 * @inode: the inode to be written
 *
 * As, filesystem can access just the blocks from
 * the disk, we need to load the whole block, where 
 * the inode resides, in memory. Then after copying
 * the latest inode in the buffer space, we will
 * writeback the whole block to the volume
 */

static void bfs_write_inode(struct inode *inode) {
	struct super_block *sb = inode->i_sb;
	unsigned long i_no = inode->i_ino;
	struct buffer_head *bh;

	struct bfs_inode *b_inode = bfs_get_inode(sb, i_no, bh);

	inode_copy(b_inode, inode);

	struct bio *bio;
	bio->bi_sector = BFS_ITABLE_FBLOCK(sb) + 
			(i_no / BFS_INODES_PER_BLOCK(sb)) 
			* BFS_BLOCK_SIZE(sb);

	bio->bi_bdev = sb->s_bdev;
	bio->bi_size = BFS_BLOCK_SIZE(sb);
	bio->bi_ops = &biops;	
	bio->bi_type = BI_write;
	bio->bi_buff = bh;

	kbuffer_io(bio)	;
}

static const struct super_operations bfs_sops = {
	.alloc_inode	= bfs_alloc_inode,
	.destroy_inode	= bfs_destroy_inode,
	.write_inode	= bfs_write_inode
};
