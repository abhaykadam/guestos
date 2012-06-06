#ifndef FS_H
#define FS_H

#include <list.h>
#include <rcupdate.h>
#include <dcache.h>
#include <mount.h>
#include <path.h>
#include <namei.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

extern struct ctx_t *isa_ctx;

struct super_block {
	struct list_head	s_list;			/* List of all superblocks */
	unsigned long		s_blocksize;		/* Block size in bytes */
	unsigned char		s_blocksize_bits;	/* Block size in bits */ 
	unsigned char		s_dirt;			/* Dirty flag */
	struct file_system_type	*s_type;		/* Filesystem type */
	struct super_operations	*s_op;			/* Superblock methods */
	unsigned long		s_magic;		/* Filesystem's magic number */
	struct dentry		*s_root;		/* Directory mount point */
	struct list_head	s_inodes;		/* List of inodes */
	struct list_head	s_dirty;		/* List of dirty inodes */
};

struct super_operations {
	struct inode *(*alloc_inode) (struct super_block *sb);
	void (*destroy_inode) (struct inode *);
	void (*dirty_inode) (struct inode *);
	int (*write_inode) (struct inode *, int);
	void (*drop_inode) (struct inode *);
	void (*delete_inode) (struct inode *);
	void (*put_super) (struct super_block *);
	void (*write_super) (struct super_block *);
	
};

struct inode {
	struct list_head	i_list;			/* List of inodes */
	struct list_head	i_sb_list;		/* List of superblocks */
	struct list_head	i_dentry;		/* List of dentries */
	unsigned long		i_ino;			/* Inode number */
	uid_t			i_uid;			/* User id of owner */
	gid_t			i_gid;			/* Group id of owner */
	off_t			i_size;			/* File size in bytes */
	struct timespec		i_atime;		/* Last access time */
	struct timespec		i_mtime;		/* Last modify time */
	struct timespec		i_ctime;		/* Last change time */
	unsigned int		i_blkbits;		/* Block size in bits */
	blkcnt_t		i_blocks;		/* File size in blocks */
	unsigned int		i_bytes;		/* Bytes consumed */
	mode_t			i_mode;			/* Access permissions */
	struct inode_operations	*i_op;			/* Inode ops table */
	struct file_operations	*i_fop;			/* Default inode ops */
	struct super_block	*i_sb;			/* Associated superblock */	
};

struct inode_operations {
	struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *);
	int (*create) (struct inode *,struct dentry *,int, struct nameidata *);
	void * (*follow_link) (struct dentry *, struct nameidata *);

};

struct file {
	union {
		struct list_head	fu_list;	/* List of file objects */
		struct rcu_head		fu_rcuhead;	/* RCU list after freeing */
	}f_u;
	struct path			f_path;		/* Contains the dentry */
	struct file_operations		*f_op;		/* File operations table */
	unsigned int			f_flags;	/* Flags specified on open */
	mode_t				f_mode;		/* File access mode */	
	off_t				f_pos;		/* File offset(file pointer) */
};

struct file_operations {
	off_t (*llseek) (struct file *, off_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, off_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, off_t *);
	int (*open)(struct inode *, struct file *);
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

struct nameidata;

extern int register_filesystem(struct file_system_type *);
extern int unregister_filesystem(struct file_system_type *);

extern int alloc_fd(unsigned start, unsigned flags);
extern int get_unused_fd(void);
#define get_unused_fd_flags(flags) alloc_fd(0, (flags))

extern struct file *filp_open(const char *, int, int);

#endif
