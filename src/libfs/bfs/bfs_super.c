#include <fs.h>
#include <bfs.h>
#include <types.h>
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
	list_del(&inode->i_list);
	free(inode);
}

static void bfs_write_inode(struct inode *inode) {
	struct bfs_inode_info *bi = BFS_I(inode);
	struct super_block *sb = inode->i_sb;
	unsigned long i_no = inode->i_ino;
	uid_t uid = inode->i_uid;
	gid_t gid = inode->i_gid;
	struct buffer_head *bh;
}

static const struct super_operations bfs_sops = {
	.alloc_inode	= bfs_alloc_inode,
	.destroy_inode	= bfs_destroy_inode,
	.write_inode	= bfs_write_inode
};
