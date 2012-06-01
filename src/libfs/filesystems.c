#include <fs.h>
#include <strings.h>

static struct file_system_type **find_filesystem(const char *name, unsigned len)
{
	struct file_system_type **p;
	for (p=&file_systems; *p; p=&(*p)->next)
		if (strlen((*p)->name) == len &&
		    strncmp((*p)->name, name, len) == 0)
			break;
	return p;
}

/*
 * 	register_filesystem - registers a new filesystem
 *	@fs: the filesystem structure
 *
 *	Adds the file system passed to the list of file systems the kernel
 *	is aware of for mount and other syscalls. Returns 0 on success,
 *	or a negative errno code on an error.
 *
 *	The &struct file_system_type that is passed is linked into the kernel 
 *	structures and must not be freed until the file system has been
 *	unregistered.
 */

int register_filesystem(struct file_system_type * fs) {
	int res = 0;
	struct file_system_type ** p;

	INIT_LIST_HEAD(&fs->fs_supers);
	p = find_filesystem(fs->name, strlen(fs->name));
	if (*p)
		res = -1;
	else
		*p = fs;

	return 0;
}

struct file_system_type *get_fs_type(const char *name){
	struct file_system_type *fs;
	const char *dot = strchr(name, '.');
	unsigned len = dot ? dot - name : strlen(name);

	fs = *(find_filesystem(name, len));
	
	return fs;
}
