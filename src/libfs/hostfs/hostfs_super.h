#include <fs.h>

const struct super_operations hostfs_sops;

struct inode *hostfs_alloc_inode(struct super_block *sb);
