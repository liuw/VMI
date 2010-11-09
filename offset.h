/* offset.h
 * 
 * Wei LIU <liuw@liuw.name>
 * defines offset of 'tsk' and 'comm' in 'struct task_struct'
 */

#ifndef _OFFSET_H_
#define _OFFSET_H_

/* applies to vmlinuz-2.6.24-26-xen */
#define TSK_OFFSET 0x88
#define COMM_OFFSET 0x1c9

#endif /* _OFFSET_H_ */
