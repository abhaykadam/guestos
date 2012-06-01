#include <fs.h>

static struct file_system_type hostfs_fs_type = {
	.name		= "hostfs",
	.get_sb		= hostfs_get_sb,
	.kill_sb	= kill_litter_super,
};

static struct superblock hostfs_sb = {
	.s_type = hostfs_fs_type,
};

int init_hostfs(void) {
	int err;
	
	err = register_filesystem(&hostfs_fs_type);
	
	return err;
}
