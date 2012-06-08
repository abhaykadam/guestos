#include <fs.h>
#include <fdtable.h>

/*struct file *get_empty_filp(void) {
	struct files_struct *files = isa_ctx->files;
	int error;

	for (int i = 0; i < NR_OPEN_DEFAULT; ++i) {
		if (files->fd_array[i] == 0) {
			return &(files->fd_array[i]);
		}
	}

	return NULL;
}*/
