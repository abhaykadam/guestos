#include <fs.h>

/* 
 * Lightweight file lookup 
 */
struct file *fget_light(unsigned int fd, int *fput_needed) {
	struct file *file;
	struct files_struct *files = current->files;

	*fput_needed = 0;
	
}
