#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<stdlib.h>
#include<linux/fb.h>

int main(void)
{
	int fd;
	int rd;
	struct fb_var_screeninfo vi;
	
	fd = open("/dev/fb0",O_RDONLY);
	if(fd < 0){
		perror("open /dev/fb0");
		exit(-1);
	}
	
	rd = ioctl(fd, FBIOGET_VSCREENINFO,&vi);
	if(rd == -1){
		perror("get var screen info with ioctl");
		exit(-1);
	}

	printf("the ratio is %d * %d\n",vi.xres_virtual,vi.yres_virtual);
	
	return 0;
}
