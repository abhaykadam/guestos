#include <hostfs_super.h>
#include <memory.h>

const struct super_operations = hostfs_sops = {
	
};

static struct inode *hostfs_alloc_inode(struct super_block *sb) {
	struct inode *inode;

	inode = (struct inode *) malloc (sizeof(struct inode));

	if (inode==NULL)
		return NULL;

	
	return inode;
}

static void ext2_destroy_inode(struct inode *inode) {
	free(inode);
}
