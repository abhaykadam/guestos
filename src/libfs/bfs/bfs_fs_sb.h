#ifndef BFS_FS_SB_H
#define BFS_FS_SB_H

#include <inttypes.h>

struct bfs_sb_info {
	uint32_t		s_inodes_per_block;	/* number of inodes per block */
	uint32_t		s_blocks_per_group;	/* number of blocks in a group */
	uint32_t		s_inodes_per_group;	/* number of inodes in a group */
	uint32_t		s_itb_per_group;	/* number of inode table blocks per group */
	uint32_t		s_gdb_count;		/* number of group descriptor blocks */
	uint32_t		s_desc_per_block;	/* number of group descriptors per block */
	uint32_t		s_groups_count;		/* number of groups in the fs */
	uint16_t		s_inode_size;		/* inode size */
	struct buffer_head	*s_sbh;			/* buffer containing the superblock */
	struct bfs_super_block	*s_bs;			/* pointer to the superblock in the buffer */
	struct buffer_head	*s_group_desc;		/* pointer to the group descriptor */
};

const struct super_operations bfs_sops;

#endif
