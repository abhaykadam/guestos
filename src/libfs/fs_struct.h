#ifndef FS_STRUCT_H
#define FS_STRUCT_H

#include <path.h>

struct fs_struct {
	struct path	root;	/* Root directory of process */
	struct path	pwd;	/* Current working directory */
};

#endif
