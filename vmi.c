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
#include <xen/xen.h>

#include "vmi.h"
#include "vmi_util.h"

unsigned long nr_pages_to_map = 0;
unsigned long shinfo_mfn = 0, arch_shinfo_mfn = 0;
shared_info_t *shinfo = 0;
struct arch_shared_info *arch_shinfo = 0;
void *p2m_list_list = 0, *p2m_list = 0, *p2m_table;
unsigned long max_pfn = 0;
static int xc_handle = -1;

int main(int argc, char **argv)
{
     int fd = -1;
     int domid = -1;
     char buf[20]; // This should be enough by now
     char *cptr;
     unsigned long init_task_vaddr = 0, mfn = 0;

     xc_handle = xc_interface_open();
     if (xc_handle == -1)
	  exit(-1);

     buf[0] = buf[19] = 0;
     fd = open("config", O_RDONLY);
     if (fd == -1) {
	  printf("Unable to read config file.\n");
	  exit(-1);
     }

     read(fd, buf, 19);
     if (buf[0] == 0) {
     	  printf("Unable to get virtual address of init_task.\n"
     		 "Check init_task_vaddr\n");
     	  exit(0);
     }
     cptr = buf;
     domid = strtoul(cptr, &cptr, 10);
     init_task_vaddr = strtoul(cptr, NULL, 16);
     /* printf("%d\n%08x\n", domid, init_task_vaddr); */

     nr_pages_to_map = vmi_get_domain_max_mem(xc_handle, domid);
     
     printf("%x\n", nr_pages_to_map);
     

//
     shinfo_mfn = vmi_get_domain_shinfo(xc_handle, domid);
     
     shinfo = (shared_info_t*)vmi_map_range_ro(xc_handle, domid, 
					       getpagesize(), shinfo_mfn);
     if (shinfo == NULL) {
	  printf("Unable to map shared info pages\n");
	  exit(-1);
     }

     arch_shinfo = &(shinfo->arch);

     /* This ONLY works for x86 platform */
     max_pfn = arch_shinfo->max_pfn;
     p2m_list_list = vmi_map_range_ro(xc_handle, domid, getpagesize(), 
				      arch_shinfo->pfn_to_mfn_frame_list_list);
     if (p2m_list_list == NULL) {
	  printf("Unable to map p2m list list page\n");
	  exit(-1);
     }
     
     p2m_list = xc_map_foreign_batch(xc_handle, domid, PROT_READ,
				     p2m_list_list,
				     (max_pfn+(FPP*FPP)-1)/(FPP*FPP));
     if (p2m_list == NULL) {
	  printf("Unable to map p2m list pages\n");
	  exit(-1);
     }
     
     p2m_table = xc_map_foreign_batch(xc_handle, domid, PROT_READ,
				      p2m_list,
				      (max_pfn+FPP-1)/FPP);
     if (p2m_table == NULL) {
	  printf("Unable to map p2m table pages\n");
	  exit(-1);
     }
//


     /* clean up */
     munmap(shinfo, getpagesize());
     close(xc_handle);
     return 0;
}
