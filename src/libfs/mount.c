#include <fs.h>
#include <mount.h>

struct file_system_type *fs_type_list=NULL;

struct file_system_type hostfs_fs_type = {
	.name		= "hostfs",
	.get_sb		= get_host_sb,
	.kill_sb	= kill_host_sb
};

static struct superblock hostfs_sb = {
	.s_dev	= 0,
	.s_type = hostfs_fs_type,
	.s_id	= "hostfs",
};

int init_hostfs(void) {
	int err=0
	
	fs_type_list=hostfs_fs_type;
	INIT_LIST_HEAD(&hostfs_sb->s_list)
	
	return err;
}

struct super_block *get_host_sb(struct file_system_type *type, 
	int flags, const char *dev_name, void *data) {

	return &hostfs_sb;
}

void kill_host_sb(struct super_block *host_sb) {
	
}
