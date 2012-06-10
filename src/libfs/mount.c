#include <fs.h>
#include <mount.h>

LIST_HEAD(super_blocks);

static struct super_block *get_host_sb(struct file_system_type *type, 
	int flags, const char *dev_name, void *data);
static void kill_host_sb(struct super_block *host_sb);

const struct file_system_type hostfs_fs_type = {
	.name		= "hostfs",
	.get_sb		= get_host_sb,
	.kill_sb	= kill_host_sb
};

static const struct super_block hostfs_sb = {
	.s_dev	= 0,
	.s_type = &hostfs_fs_type,
	.s_id	= "hostfs"
};

int init_hostfs(void) {
	int err=0;
	
	list_add_tail(&hostfs_sb.s_list, &super_blocks);
	
	return err;
}

static struct super_block *get_host_sb(struct file_system_type *type, 
	int flags, const char *dev_name, void *data) {

	return &hostfs_sb;
}

static void kill_host_sb(struct super_block *host_sb) {
		
}
