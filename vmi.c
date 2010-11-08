/*
 * vmi.c
 *
 * Wei LIU <liuw@liuw.name>
 *
 * Virtual machine introspection for Xen. Try to read guest's process
 * list.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <xenctrl.h>
#include <xs.h>

#define KERNEL_OFFSET 0xc0000000
#define SIZE_TO_MAP (1024*1024*4 * 1024)

static int xc_handle = -1;

void message(void)
{
     printf("This program reads init_task_vaddr.\n"
	    "Make sure you invoke find_init_task.sh "
	    "with the right system map.\n");
     printf("\n\n");
}


int main(int argc, char **argv)
{
     int fd = -1;
     int domid = -1;
     char buf[9];
     unsigned long init_task_vaddr = 0, mfn = 0;
     void *mapped = 0;

     xc_handle = xc_interface_open();
     if (xc_handle == -1)
	  exit(-1);

     message();
     
     buf[0] = buf[8] = 0;
     fd = open("init_task_vaddr", O_RDONLY);
     read(fd, buf, 8);
     if (buf[0] == 0) {
	  printf("Unable to get virtual address of init_task.\n"
		 "Check init_task_vaddr\n");
	  exit(0);
     }
     init_task_vaddr = strtoul(buf, NULL, 16);

     printf("Input target domain id: ");
     scanf("%d", &domid);

     /* mapped = (void*) xc_map_foreign_range( */
     /* 	  xc_handle, domid, getpagesize(), PROT_READ, */
     /* 	  (unsigned long)ref); */

     if (mapped == NULL) {
	  printf("Unable to map target pages\n");
	  exit(-1);
     }


     /* munmap(mapped, SIZE_TO_MAP); */
     close(xc_handle);
     return 0;
}
