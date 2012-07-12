#ifndef HOSTFS_H
#define HOSTFS_H

#include <fs.h>
#include <types.h>
#include <limits.h>

struct hostfs_inode_info {
	char 		file[LINE_MAX];
	struct inode	hostfs_inode;
};

static inline struct hostfs_inode_info *hostfs_i(struct inode *inode) {
	return container_of(inode, struct hostfs_inode_info, hostfs_inode);
}

#endif
