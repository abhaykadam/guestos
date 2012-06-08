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

/* Name hashing routines. Initial hash value */
/* Hash courtesy of the R5 hash in reiserfs modulo sign bits */
#define init_name_hash()                0

/* partial hash update function. Assume roughly 4 bits per character */
static inline unsigned long
partial_name_hash(unsigned long c, unsigned long prevhash) {
	return (prevhash + (c << 4) + (c >> 4)) * 11;
}

/*
 * Finally: cut down the number of bits to a int value (and try to avoid
 * losing bits)
 */
static inline unsigned long end_name_hash(unsigned long hash) {
	return (unsigned int) hash;
}

/* Compute the hash for a name string. */
static inline unsigned int
full_name_hash(const unsigned char *name, unsigned int len) {
	unsigned long hash = init_name_hash();
	while (len--)
		hash = partial_name_hash(*name++, hash);
	return end_name_hash(hash);
}

#endif
