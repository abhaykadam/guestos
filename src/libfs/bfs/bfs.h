#ifndef BFS_H
#define BFS_H

#include <types.h>

/* bfs inode data in memory */
struct bfs_inode_info {
	uint32_t	i_data[12];
	uint32_t	i_flags;
	uint16_t	i_state;
	uint32_t	i_dtime;
	uint32_t	i_block_group;
	struct inode	vfs_inode;
};

static inline struct bfs_inode_info *bfs_i(struct inode *inode) {
	return container_of(inode, struct bfs_inode_info, vfs_inode);
}

extern struct bfs_inode *bfs_get_inode(struct super_block *sb,
	unsigned long ino, struct buffer_head *bh);

extern inline void inode_copy (struct bfs_inode *dest, 
	struct bfs_inode *src);

#endif
