#include <hostfs_super.h>
#include <stdlib.h>

static struct inode *hostfs_alloc_inode(struct super_block *sb) {
	struct inode *inode;

	inode = (struct inode *) malloc (sizeof(struct inode));

	if (inode==NULL)
		return NULL;

	
	return inode;
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
	list_del(&hostfs_sb->s_list);
}

const struct super_operations hostfs_sops = {
	.alloc_inode	= hostfs_alloc_inode,
	.destroy_inode	= hostfs_destroy_inode,
	.write_inode	= hostfs_write_inode,
	.delete_inode	= hostfs_delete_inode,
	.put_super	= hostfs_put_super
};
