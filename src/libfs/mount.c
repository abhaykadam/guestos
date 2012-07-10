#include <bio.h>
#include <bfs_fs.h>
#include <mount.h>
#include <memory.h>
#include <unistd.h>
#include <limits.h>

extern struct list_head block_devices;
extern const struct super_operations bfs_sops;

LIST_HEAD(super_blocks);

static struct super_block *get_host_sb(struct file_system_type *, 
	int , const dev_t , void *, struct vfsmount *);
static void kill_host_sb(struct super_block *);
static struct super_block *get_bfs_sb(struct file_system_type *, 
	int , const dev_t , void *, struct vfsmount *);
static void kill_bfs_sb(struct super_block *);

inline struct vfsmount *alloc_vfsmnt(void) {
	return (struct vfsmount *) malloc(sizeof (struct vfsmount));
}

inline void free_vfsmnt(struct vfsmount *mnt) {
	free(mnt);
}


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

int mount_hostfs(struct vfsmount *hostfs_mnt) {
	int err=0;
	
	hostfs_mnt = alloc_vfsmnt();

	hostfs_mnt->mnt_parent = 0; /* hostfs will be mounted at root.
					so, it won't have parent fs */
	hostfs_mnt->mnt_mountpoint = 0;
	hostfs_mnt->mnt_root = 0;
	hostfs_mnt->mnt_sb = hostfs_fs_type.get_sb(&hostfs_fs_type, 0,0,0,hostfs_mnt);

	
	return err;
}

int mount_block_dev(const struct block_device *bdev) {
	int err=0;

	struct vfsmount *vfsmnt=0;

	vfsmnt = alloc_vfsmnt();

	/* create a directory in hostfs 
	which will be the mount-point
	for mounted the block device */
	char mount_point[LINE_MAX];
	sprintf(mount_point, "./disk%d", bdev->bd_dev);
	
	int status;
	status = mkdir(mount_point, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (status){
		perror("error");
		exit(-1);
	}

	
}

static struct super_block *get_host_sb(struct file_system_type *type, 
	int flags, const dev_t dev, 
	void *data, struct vfsmount *mnt) {

	return &hostfs_sb;
}

static void kill_host_sb(struct super_block *host_sb) {
	/* to do code */	
}

static const struct file_system_type bfs_fs_type = {
	.name		= "bfs",
	.get_sb		= get_bfs_sb,
	.kill_sb	= kill_bfs_sb
};

static struct super_block *get_bfs_sb(struct file_system_type *type, 
	int flags, const dev_t dev, 
	void *data, struct vfsmount *mnt) {

	struct block_device *blk_dev=0;
	bool device_found = false;

	/* search for the block device */
	dlist_for_each_entry(blk_dev, &block_devices, bd_list) {
		if (blk_dev->bd_dev == dev) {
			device_found = true;
			break;
		}
	}

	if (device_found == false)
		return 0;

	
	/* read the superblock of the filesystem */
	struct bio bio;

	struct buffer_head *bh;
	bh = (struct buffer_head *)
		malloc(sizeof(struct buffer_head));

	bh->b_state	= BH_Req;
	bh->b_blocknr	= blk_dev->bd_block_size;
	bh->b_data	= (char *)malloc(sizeof(blk_dev->bd_block_size));
	bh->b_dev	= blk_dev;	

	bio.bi_sector	= blk_dev->bd_block_size;
	bio.bi_bdev	= blk_dev;
	bio.bi_size	= blk_dev->bd_block_size;;
	bio.bi_ops	= &bfs_sops;	
	bio.bi_type	= BI_read;
	bio.bi_buff	= bh;

	kbuffer_io(&bio);

	struct super_block *sb;
	sb = build_sb_from_bfs_sb(bh);
	
	sb->s_dev	= blk_dev->bd_dev;
	sb->s_type	= type;
	sb->s_op	= &bfs_sops;
	sb->s_bdev	= blk_dev;

	blk_dev->bd_super = sb;

	return sb;
}

static void kill_bfs_sb(struct super_block *bfs_sb) {
		
}
