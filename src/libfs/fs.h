#ifndef FS_H
#define FS_H

#include <dlist.h>
#include <types.h>
#include <dcache.h>
#include <mount.h>
#include <path.h>
#include <namei.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <inttypes.h>

extern struct ctx_t *isa_ctx;

struct block_device{
	dev_t			bd_dev;
	struct super_block	*bd_super;
	unsigned		bd_block_size;
	const char		*bd_name;
};

struct super_block {
	struct list_head	s_list;			/* List of all superblocks */
	dev_t			s_dev;			/* Identifier */
	unsigned long		s_blocksize;		/* Block size in bytes */
	unsigned char		s_blocksize_bits;	/* Block size in bits */ 
	unsigned char		s_dirt;			/* Dirty flag */
	unsigned long long	s_maxbytes;		/* Max file size */
	struct file_system_type	*s_type;		/* Filesystem type */
	struct super_operations	*s_op;			/* Superblock methods */
	unsigned long		s_flags;		/* Mount Flags */
	unsigned long		s_magic;		/* Filesystem's magic number */
	struct dentry		*s_root;		/* Directory mount point */
	int			s_count;		/* Superblock reference count */
	struct list_head	s_inodes;		/* List of inodes */
	struct list_head	s_dirty;		/* List of dirty inodes */
	struct block_device	*s_bdev;		/* Associated block device */
	char			s_id[32];		/* Text name */
	void			*s_fs_info;		/* Filesystem specific info */
};

struct super_operations {
	struct inode *(*alloc_inode) (struct super_block *sb);
	void (*destroy_inode) (struct inode *);
	void (*write_inode) (struct inode *);
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
	atomic_t		i_count;		/* Reference counter */
	uid_t			i_uid;			/* User id of owner */
	gid_t			i_gid;			/* Group id of owner */
	dev_t			i_rdev;			/* Real device node */
	off_t			i_size;			/* File size in bytes */
	time_t		i_atime;		/* Last access time */
	time_t		i_mtime;		/* Last modify time */
	time_t		i_ctime;		/* Last change time */
	unsigned int		i_blkbits;		/* Block size in bits */
	blkcnt_t		i_blocks;		/* File size in blocks */
	unsigned int		i_bytes;		/* Bytes consumed */
	mode_t			i_mode;			/* Access permissions */
	struct inode_operations	*i_op;			/* Inode ops table */
	struct file_operations	*i_fop;			/* Default inode ops */
	struct super_block	*i_sb;			/* Associated superblock */
	unsigned long		i_state;		/* State flags */
	unsigned long		dirtied_when;		/* First dirtying time */	
};

struct inode_operations {
	struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *);
	int (*create) (struct inode *,struct dentry *,int, struct nameidata *);
	int (*mkdir) (struct inode *,struct dentry *,int);
	int (*rmdir) (struct inode *,struct dentry *);
	int (*rename) (struct inode *, struct dentry *, struct inode *, struct dentry *);
	void (*truncate) (struct inode *);
};

struct file {
	struct list_head		fu_list;	/* List of file objects */
	struct path			f_path;		/* Contains the dentry */
	struct file_operations		*f_op;		/* File operations table */
	unsigned int			f_flags;	/* Flags specified on open */
	mode_t				f_mode;		/* File access mode */	
	off_t				f_pos;		/* File offset(file pointer) */
};

/*
 * This is the "filldir" function type, used by readdir() to let
 * the kernel specify what kind of dirent layout it wants to have.
 * This allows the kernel to read directories into kernel space or
 * to have different dirent layouts depending on the binary type.
 */
typedef int (*filldir_t)(void *, const char *, int, loff_t, uint64_t, unsigned);

struct file_operations {
	off_t (*llseek) (struct file *, off_t, int);
	ssize_t (*read) (struct file *, char *, size_t, off_t *);
	ssize_t (*write) (struct file *, const char *, size_t, off_t *);
	int (*open)(struct inode *, struct file *);
	int (*readdir) (struct file *, void *, filldir_t);
	int (*release) (struct inode *, struct file *);
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
