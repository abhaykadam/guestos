#ifndef FDTABLE_H
#define FDTABLE_H

#include <fs.h>
#include <limits.h>

/*
 * The fd array needs to be BITS_PER_LONG
 */
#define NR_OPEN_DEFAULT SHRT_MAX

/*struct fdtable {
	unsigned int	max_fds;
	struct file	**fd;
	unsigned long	*open_fds;
	struct rcu_head	rcu;
	struct fdtable 	*next;	
};*/

struct files_struct {
	struct file	*fd_array[NR_OPEN_DEFAULT];	/* Files array */
};

#endif
