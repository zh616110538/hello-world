/***************************************file_lock.h*******************************************/  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <string.h>  
#include <errno.h>  
#include <fcntl.h>  
#include <signal.h>  
#include <sys/types.h>        
#include <sys/stat.h>  
  
  
int   lock_reg(int, int, int, off_t, int, off_t); //register lock  
pid_t lock_test(int, int, off_t, int, off_t);  //test  lockable  
  
  
//set lock  
#define read_lock(fd, offset, whence, len) \
            lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))  
#define readw_lock(fd, offset, whence, len) \
	            lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))  
#define write_lock(fd, offset, whence, len) \
	            lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))  
#define writew_lock(fd, offset, whence, len) \
	            lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))  
#define un_lock(fd, offset, whence, len) \
	            lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))  
	              
	//Test lock      
#define read_lock_pid(fd, offset, whence, len) \
	      lock_test((fd), F_RDLCK, (offset), (whence), (len))  
#define write_lock_pid(fd, offset, whence, len) \
	      lock_test((fd), F_WRLCK, (offset), (whence), (len))  
#define is_read_lockable(fd, offset, whence, len) \
	            (read_lock_pid == 0)  
#define is_write_lockable(fd, offset, whence, len) \
	            (write_lock_pid == 0)       
