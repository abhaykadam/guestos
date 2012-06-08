#ifndef BFS_FS_SB_H
#define BFS_FS_SB_H

struct bfs_sb_info {
	uint32_t	s_inodes_count;			/* Total number of inodes */
	uint32_t	s_blocks_count;			/* Filesystem size in blocks */
	uint32_t	s_free_blocks_count;		/* Free blocks counter */
	uint32_t	s_free_inodes_count;		/* Free inodes counter */
	uint32_t	s_first_data_block;		/* Number of first useful block */
	uint32_t	s_log_block_size;		/* Block size */
	uint32_t	s_blocks_per_group;		/* Number of blocks per group */
	uint32_t	s_inodes_per_group;		/* Number of inodes per group */
	uint16_t	s_inode_size;			/* Size of on-disk inode structure */
	uint8_t		s_uuid[16];			/* 128-bit silesystem identifier */
	char		s_volume_name[16];		/* Volume name */
	uint8_t		s_prealloc_blocks;		/* Number of blocks to preallocate */
	uint8_t		s_prealloc_dir_blocks;		/* Number of blocks to preallocate for directories */
	uint16_t	s_padding_1;			/* Alignment to word */
	uint32_t	s_reserved[238];		/* Padding to the end of the block */
};

#endif
