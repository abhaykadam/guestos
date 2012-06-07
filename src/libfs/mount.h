#ifndef MOUNT_H
#define MOUNT_H

#include <fs.h>
#include <dcache.h>
#include <list.h>

struct vfsmount{
	struct	vfsmount	*mnt_parent;		/* FS we are mounted on */
	struct	dentry		*mnt_mountpoint;	/* Dentry of mountpoint */
	struct	dentry		*mnt_root;		/* Root of the mounted tree */
	struct	super_block	*mnt_sb;		/* Pointer to superblock */
	struct	list_head	*mnt_mounts;		/* List of children anchored  here */
	int			mnt_flags;		/* Mount flags */
	int			mnt_id;			/* Mount identifier */
	char			*mnt_devname;		/* Name of device */
	atomic_t		mnt_count;		/* Usage count */
};

#endif
