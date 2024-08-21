/*
 *** Context info
 */

#include <typedef.h>
#include <sysdef.h>
#include <syslib.h>
#include <knldef.h>

/* Executing context data on stack */
typedef struct {
	UW	r_[8];	// values of r4-r11 register which are stored by exception
	UW	r[4];	// values of r0-r3 register
	UW	ip;		// value of r12 register
	UW	lr;		// value of LR register
	UW	pc;		// value of PC register
	UW	xpsr;	// value of XPSR register
} StackFrame;

/* Make the initial context data */
void *make_context(UW *sp, UINT ssize, void (*fp)())
{
	StackFrame *sfp;

	/* Set the pointer of the executing context data on stack to sfp */
	sfp = (StackFrame*)((UW)sp + ssize);
	sfp--;

	/* Initialize the executing context data */
	sfp->xspr 	= 0x01000000;
	sfp->pc		= (UW)fp & ~0x00000001UL;

	return (void*)sfp;
}


