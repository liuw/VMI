/* offset.h
 * 
 * Wei LIU <liuw@liuw.name>
 * defines offset of 'tsk' and 'comm' in 'struct task_struct'
 */

#ifndef _OFFSET_H_
#define _OFFSET_H_

#include "vmi.h"

/* applies to vmlinuz-2.6.24-26-xen */
#define TSK_OFFSET 0x88
#define COMM_OFFSET 0x1c9
#define COMM_TO_TSK_OFFSET (0x1c9-0x88)

struct task_struct 
{
     char pad0[0x88];
     struct list_head tsk;
     char pad1[0x1c9-0x88];
     char comm[16];
     /* no more... */
};

#endif /* _OFFSET_H_ */
