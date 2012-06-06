#ifndef PATH_H
#define PATH_h

struct path {
	struct vfsmount	*mnt;
	struct dentry	*dentry;
};

#endif
