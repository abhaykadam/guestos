#ifndef NAMEI_H
#define NAMEI_H

struct open_intent {
	int		flags;
	int		create_mode;
	struct file	*file;
};

struct nameidata {
	struct path	path;
	struct path	root;
	struct file	*file;
	struct inode	*inode;
	unsigned int	flags;
	unsigned	seq;
	int		last_type;
	unsigned	depth;

	union {
		struct open_intent open;
	} intent;
};

/*
 * Type of the last component on LOOKUP_PARENT
 */
enum {LAST_NORM, LAST_ROOT, LAST_DOT, LAST_DOTDOT, LAST_BIND};

/*
 * The bitmask for a lookup event:
 *  - follow links at the end
 *  - require a directory
 *  - ending slashes ok even for nonexistent files
 *  - internal "there are more path components" flag
 *  - dentry cache is untrusted; force a real lookup
 *  - suppress terminal automount
 */
#define LOOKUP_FOLLOW		0x0001
#define LOOKUP_DIRECTORY        0x0002
#define LOOKUP_CONTINUE         0x0004

#define LOOKUP_PARENT           0x0010
#define LOOKUP_REVAL            0x0020
#define LOOKUP_RCU              0x0040
#define LOOKUP_NO_AUTOMOUNT     0x0080
/*
 * Intent data
 */
#define LOOKUP_OPEN             0x0100
#define LOOKUP_CREATE           0x0200
#define LOOKUP_EXCL             0x0400
#define LOOKUP_RENAME_TARGET    0x0800

#endif
