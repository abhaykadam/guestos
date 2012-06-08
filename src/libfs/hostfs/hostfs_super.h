#ifndef HOSTFS_SUPER_H
#define HOSTFS_SUPER_H

#include <fs.h>

extern struct super_block hostfs_sb;

const struct super_operations hostfs_sops;

#endif
