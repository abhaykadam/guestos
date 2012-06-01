#ifndef FS_H
#define FS_H

#include <list.h>
#include <mount.h>


struct super_block {
	unsigned long		s_blocksize;		/* Block size in bytes */
	unsigned char		s_blocksize_bits;	/* Block size in bits */ 
	unsigned char		s_dirt;			/* Dirty flag */
	struct file_system_type	*s_type;		/* Filesystem type */
	unsigned long		s_magic;		/* Filesystem's magic number */
	struct dentry		*s_root;		/* Directory mount point */
};

struct inode {
	unsigned long		i_ino;			/* Inode number */
	unsigned long		i_size;			/* File size in bytes */
};

struct file_system_type {
	const char	*name;				/* Filesystem name */				
	int		fs_flags;			/* Filesystem type flags */
	int (*get_sb) (struct file_system_type *, int,
	       const char *, void *, struct vfsmount *);/* Method for reading superblock */
	void (*kill_sb) (struct super_block *);		/* Method for removing superblock */
	struct file_system_type *next;			/* Pointer to the next element in the list of filesystem types */
	struct list_head fs_supers;			/* Head of list of superblocks */
};

extern int register_filesystem(struct file_system_type *);
extern int unregister_filesystem(struct file_system_type *);

#endif
