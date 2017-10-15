#include <errno.h>
#include <features.h>

int __syscall_error(int err_no)
{
	__set_errno(-err_no);
	return -1;
}

