#include "file_lock.h"  


int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)  
{  
	struct flock    lock;  

	lock.l_type = type;     /* F_RDLCK, F_WRLCK, F_UNLCK */  
	lock.l_start = offset;  /* byte offset, relative to l_whence */  
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */  
	lock.l_len = len;       /* #bytes (0 means to EOF) */  

	return(fcntl(fd, cmd, &lock));  
}  


pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len)  
{  
	struct flock    lock;  

	lock.l_type = type;     /* F_RDLCK or F_WRLCK */  
	lock.l_start = offset;  /* byte offset, relative to l_whence */  
	lock.l_whence = whence; /* SEEK_SET, SEEK_CUR, SEEK_END */  
	lock.l_len = len;       /* #bytes (0 means to EOF) */  

	if (fcntl(fd, F_GETLK, &lock) < 0)  
	{  
		printf("fcntl error for %s.\n", strerror(errno));  
		return (-1);  
	}       

	if (lock.l_type == F_UNLCK)  
	{  
		return(0);    /* false, region isn't locked by another proc */  
	}   

	return(lock.l_pid); /* true, return pid of lock owner */  
}  
