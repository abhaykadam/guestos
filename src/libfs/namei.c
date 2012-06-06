#include <namei.h>
#include <path.h>
#include <fs.h>
#include <fcntl.h>

/*
 * Note that while the flag value (low two bits) for sys_open means:
 *      00 - read-only
 *      01 - write-only
 *      10 - read-write
 *      11 - special
 * it is changed into
 *      00 - no permissions needed
 *      01 - read-permission
 *      10 - write-permission
 *      11 - read-write
 */
static inline int open_to_namei_flags(int flag) {
	if ((flag+1) & O_ACCMODE)
		flag++;
	return flag;
}

/*
 * Name resolution.
 * This is the basic name resolution function, turning a pathname into
 * the final dentry. We expect 'base' to be positive and a directory.
 *
 * Returns 0 and nd will have valid dentry and mnt on success.
 * Returns error and drops reference to input namei data on failure.
 */
static int link_path_walk(const char *name, struct nameidata *nd) {
	struct path next;
	int err;
	unsigned int lookup_flags  = nd->flags;

	while (*name=='/')
		name++;
	if (!*name)
		goto return_reval;

	if (nd->depth)
		lookup_flags = LOOKUP_FOLLOW | (nd->flags & LOOKUP_CONTINUE);	

	/* At this point we know we have a real path component. */
	for(;;) {
		struct inode *inode;
		unsigned long hash;
		struct qstr this;
		unsigned int c;

		nd->flags |= LOOKUP_CONTINUE;

		this.name = name;
		c = *(const unsigned char *)name;
		hash = init_name_hash();
		do {
			name++;
			hash = partial_name_hash(c, hash);
			c = *(const unsigned char *)name;
		} while (c && (c != '/'));
		this.len = name - (const char *) this.name;
		this.hash = end_name_hash(hash);
		
		/* remove trailing slashes? */
		if (!c)
			goto last_component;
		while (*++name == '/');
			if (!*name)
				goto last_with_slashes;

		/* This does the actual lookups.. */
		err = do_lookup(nd, &this, &next, &inode);

		if (err)
			break;
		err = -1;
		if (!inode)
			goto out_dput;

		if (inode->i_op->follow_link){
			err = do_follow_link(inode, &next, nd);
		}

last_with_slashes:

last_component:

return_reval:

out_dput:

	}
	
}

static int path_init_rcu(int dfd, const char *name, unsigned int flags, struct nameidata *nd) {
	int retval = 0;
	int fput_needed;
	struct file *file;

	nd->last-->type = LAST_ROOT;
	nd->flags = flags | LOOKUP_RCU;
	nd->depth = 0;
	nd->root.mnt = NULL;
	nd->file = NULL;
	
	if (*name=='/') {
		struct fs_struct *fs = isa_ctx->fs;
		nd.root = fs->root;
		nd.path = nd->root;

	}  else if (dfd == AT_FDCWD) {
		struct fs_struct *fs = isa_ctx->fs;
		nd->path = fs->pwd;
	} else {
		struct dentry *dentry;
	}
}

struct file *do_filp_open(int dfd, const char *pathname,
		int open_flag, int mode, int acc_mode) {
	struct file *filp;
	struct nameidata nd;
	struct path path;
	int error;
	int flag = open_to_namei_flags(open_flag);
	int flags;

	if (!(open_flag & O_CREAT))
		mode = 0;

	flags = LOOKUP_OPEN;
	if (open_flag & O_DIRECTORY)
		flags |= LOOKUP_DIRECTORY;

	filp = get_empty_filp();
	if (!filp)
		return filp;

	filp->f_flags = open_flag;
	nd.intent.open.file = filp;
	nd.intent.open.flags = flag;
	nd.intent.open.create_mode = mode;

	if (open_flag & O_CREAT)
		goto creat;

creat:
	/*OK, have to create a file. Find the parent. */
	error = path_init_rcu(dfd, pathname,
			LOOKUP_PARENT | (flags & LOOKUP_REVAL), &nd);
	
}

/*
 * filp_open - open file and return file pointer
 *
 * @filename:	path to open
 * @flags:	open flags
 * @mode:	mode for the new file if O_CREAT is set, else ignored
 */
struct file *filp_open(const char *filename, int flags, int mode) {
	return do_filp_open(AT_FDCWD, filename, flags, mode, 0);
}
