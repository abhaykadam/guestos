#include <fs.h>
#include <buffer_head.h>
#include <bfs.h>
#include <bfs_fs.h>
#include <bfs_fs.h>
#include <bfs_fs_sb.h>
#include <bio.h>
#include <types.h>
#include <dlist.h>
#include <stdlib.h>
#include <string.h>

struct super_block *build_sb_from_bfs_sb(const struct buffer_head *bh) {
	struct super_block *sb;
	sb = (struct super_block *)
		malloc(sizeof(struct super_block));

	struct bfs_sb_info *bfs_sb_i;
	bfs_sb_i = (struct bfs_sb_info *)
		malloc(sizeof(struct bfs_sb_info));

	struct bfs_super_block *bfs_sb;
	bfs_sb = (struct bfs_super_block *)bh;

	bfs_sb_i->s_inodes_per_block	= bfs_sb->s_inode_size / (1024<<bfs_sb->s_log_block_size);
	bfs_sb_i->s_blocks_per_group	= bfs_sb->s_blocks_per_group;
	bfs_sb_i->s_inodes_per_group	= bfs_sb->s_inodes_per_group;
	bfs_sb_i->s_itb_per_group	= bfs_sb->s_inodes_per_group
						/ bfs_sb_i->s_inodes_per_block;
	bfs_sb_i->s_inode_size		= bfs_sb->s_inode_size;
	bfs_sb_i->s_sbh			= bh;
	bfs_sb_i->s_bs			= (struct bfs_super_block *)bh;


	sb->s_blocksize			= 1024<<bfs_sb->s_log_block_size;
	strcpy(sb->s_id,bfs_sb->s_volume_name);
	sb->s_fs_info			= bfs_sb_i;

	return sb;
}


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
	int i;

	struct bfs_inode *new_inode = 
		(struct bfs_inode *) malloc(sizeof(struct bfs_inode));
			
	new_inode->i_mode	= inode->i_mode;
	new_inode->i_uid	= inode->i_uid;
	new_inode->i_size	= inode->i_size;
	new_inode->i_atime	= inode->i_atime;
	new_inode->i_ctime	= inode->i_mtime;
	new_inode->i_mtime	= inode->i_mtime;
	new_inode->i_gid	= inode->i_gid;
	new_inode->i_blocks	= inode->i_blocks;

	for (i=0; i < BFS_N_BLOCKS; ++i) {
		new_inode->i_block[i] = bfs_i(inode)->i_data[i]; 
	}
	

	struct bfs_inode *b_inode = bfs_get_inode(sb, i_no, bh);

	copy_inode(b_inode, new_inode);
	
	struct bio *bio;
	bio->bi_sector = bfs_itable_fblock(sb) + 
			(i_no / bfs_inodes_per_block(sb)) 
			* bfs_block_size(sb);

	bio->bi_bdev = sb->s_bdev;
	bio->bi_size = bfs_block_size(sb);
	bio->bi_ops = &biops;	
	bio->bi_type = BI_write;
	bio->bi_buff = bh;

	kbuffer_io(bio)	;
}

/**
 * bfs_delete_inode - delets inode and its related data 
 * 			from memory as well as from disk
 * @inode: inode to be deleted
 *
 * Deletes the VFS inode in memory and the file data
 * and metadata on disk
 */
static void bfs_delete_inode(struct inode *inode) {
	/* not yet developed */
	return;
}

extern const struct super_operations bfs_sops = {
	.alloc_inode	= bfs_alloc_inode,
	.destroy_inode	= bfs_destroy_inode,
	.write_inode	= bfs_write_inode
};
