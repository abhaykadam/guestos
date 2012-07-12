#include <hostfs.h>
#include <hostfs_super.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>


/**
 * hostfs_alloc_inode - creates a new inode
 * @sb: parent superblock for the inode
 *
 * A new inode is created under given superblock
 */
static struct inode *hostfs_alloc_inode(struct super_block *sb) {
	struct inode *inode;

	inode = (struct inode *) malloc (sizeof(struct inode));
	if (inode==0)
		return 0;
	
	return inode;
}

static void hostfs_read_inode (struct inode *inode) {
	struct hostfs_inode_info *hi_info;
	hi_info = hostfs_i(inode);

	char file[LINE_MAX];
	strcpy(file, hi_info->file);

	struct stat *stat_buf;
	int status;
	status = stat(file, stat_buf);
	if (status) {
		perror("error");
		exit(-1);
	}

	/* fill the inode structure from the filestat */
	inode->i_ino	= stat_buf->st_ino;
	inode->i_uid	= stat_buf->st_uid;
	inode->i_gid	= stat_buf->st_gid;
	inode->i_rdev	= stat_buf->st_rdev;
	inode->i_size	= stat_buf->st_size;
	inode->i_atime	= stat_buf->st_atime;
	inode->i_mtime	= stat_buf->st_mtime;
	inode->i_ctime	= stat_buf->st_ctime;
	inode->i_blocks	= stat_buf->st_blocks;
}

static void hostfs_destroy_inode(struct inode *inode) {
	free(inode);
}

static void hostfs_write_inode(struct inode *inode) {
	/* 
	 * do nothing, because inode stats will be
	 * taken care of by the host OS itself
	 */
}

static void hostfs_delete_inode(struct inode *inode) {
	/*
	 * deletes the given inode from disk.
	 * But, in case of host fs, we need to delete
	 * the file or directory by issueing specific
	 * function(eg., remove())
	 */	
}

static void hostfs_put_super(struct super_block *hostfs_sb) {
	dlist_del(&hostfs_sb->s_list);
}

const struct super_operations hostfs_sops = {
	.alloc_inode	= hostfs_alloc_inode,
	.read_inode	= hostfs_read_inode,
	.destroy_inode	= hostfs_destroy_inode,
	.write_inode	= hostfs_write_inode,
	.delete_inode	= hostfs_delete_inode,
	.put_super	= hostfs_put_super
};
