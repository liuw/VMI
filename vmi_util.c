/* vim_util.c
 * 
 * Wei LIU <liuw@liuw.name>
 */

/* in pages */

#include <xenctrl.h>
#include <xs.h>
#include <stdio.h>
#include <sys/mman.h>

unsigned long vmi_get_domain_max_mem(int xc_handle, int domid)
{
     xc_dominfo_t dinfo;
     xc_domain_getinfo(xc_handle, domid, 1, &dinfo);
     /* return dinfo.max_memkb / 4; */
     return dinfo.nr_pages;
}

unsigned long vmi_get_domain_shinfo(int xc_handle, int domid)
{
     xc_dominfo_t dinfo;
     xc_domain_getinfo(xc_handle, domid, 1, &dinfo);
     /* return dinfo.max_memkb / 4; */
     return dinfo.shared_info_frame;
}

void *vmi_map_range_ro(int xc_handle, int domid, 
		       unsigned long size,
		       unsigned long mfn)
{
     return (void*)xc_map_foreign_range(xc_handle, domid,
					size, PROT_READ,
					mfn);
}


void dump_page(void *p)
{}
