#ifndef DCACHE_H
#define DCACHE_H

#include <fs.h>
#include <stdbool.h>

/*
 * "quick string" -- eases parameter passing, but more importantly
 * saves "metadata" about the string (ie length and the hash).
 *
 * hash comes first so it snuggles against d_parent in the
 * dentry.
 */
struct qstr {
	unsigned int 		hash;
	unsigned int 		len;
	const unsigned char	*name;
};

struct dentry {
	atomic_t			d_count;	/* Usage count */
	bool				d_mounted;	/* Is this mount point? */
	struct inode			*d_inode;	/* Associated inode */	
	struct dentry			*d_parent;	/* Dentry object of parent */
	struct qstr			d_name;		/* Dentry name */
	struct list_head		d_lru;		/* Unused list */
	struct list_head		d_child;	/* List of dentries within */
	struct list_head		d_subdirs;	/* Subdirectories */
	unsigned long			d_time;		/* Revalidate time */
	struct dentry_operations	*d_op;		/* dentry operations table */
	struct super_block		*d_sb;		/* superblock of file */
	unsigned int			d_flags;	/* dentry flags */
};

struct dentry_operations {
	int (*d_revalidate) (struct dentry *, struct nameidata *);
	int (*d_hash)(const struct dentry *, const struct inode *, struct qstr *);
	int (*d_compare) (struct dentry *, struct qstr *, struct qstr *);
	int (*d_delete)(struct dentry *);
	void (*d_release)(struct dentry *);
	void (*d_iput)(struct dentry *, struct inode *);	
};

#endif
