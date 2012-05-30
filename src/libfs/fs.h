#ifndef FS_H
#define FS_H

struct super_block {
	unsigned long	s_blocksize;		/* block size in bytes */
	unsigned char	s_blocksize_bits;	/* block size in bits */ 
};

#endif
