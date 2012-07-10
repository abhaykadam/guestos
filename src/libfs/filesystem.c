#include <fs.h>
#include <filesystem.h>
#include <bdev.h>
#include <dlist.h>

extern struct list_head block_devices;
extern const struct file_system_type hostfs_fs_type;

LIST_HEAD(fs_types);

struct vfsmount *hostfs_mnt;

static int register_filesystem(struct file_system_type *fs_type) {
	dlist_add_tail(&fs_type->fs_list, &fs_types);
	return 0;
}

void init_filesystem(void) {
	register_filesystem(&hostfs_fs_type);

	/* Mount the host filesystem */
	mount_hostfs(hostfs_mnt);
	
	struct block_device *blk_dev;
	dlist_for_each_entry(blk_dev, &block_devices, bd_list) {
		mount_block_dev(blk_dev);
	}
} 
