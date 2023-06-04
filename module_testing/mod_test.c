#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

int main(int argc, char* argv[]) {
	int fd;
	fd = open("/dev/CacheClear", O_RDONLY);
	if (fd == -1) {
		printf("Error: Open Failed. errno == %d\n", errno);
		return 1;
	}

	int ioctl_retval;

	ioctl_retval = ioctl(fd, 5, 10);
	printf("ioctl_retval: %d\n", ioctl_retval);
	ioctl_retval = ioctl(fd, 1, 10);
	printf("ioctl_retval: %d\n", ioctl_retval);

	close(fd);
	return 0;
}
