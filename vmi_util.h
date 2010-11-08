#ifndef _VMI_UTIL_H_
#define _VMI_UTIL_H_

#include <xenctrl.h>
#include <xs.h>

/* in pages */
unsigned long vmi_get_domain_max_mem(int xc_handle, int domid);

unsigned long vmi_get_domain_shinfo(int xc_handle, int domid);

void *vmi_map_range_ro(int xc_handle, int domid, 
		       unsigned long size,
		       unsigned long mfn);

#endif /* _VMI_UTIL_H_ */
