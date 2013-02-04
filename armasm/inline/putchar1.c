/**
 *	@brief		putchar in asm.
 */

#include <stdio.h>


/**
 *	@brief
 */
void	main(void)
{
//	putchar('A');
//	putchar(0x41);
#if	0
	/*
	 *	a1: 1st argument
	 *	a2: 2nd arg
	 *	a3: same as
	 *	a4: ...
	 */
	asm (
		"mov	a1, #0x41;"
		"b  	putchar;"
		: 
		: 
		: "a1"
		);
#else
	/*
	 *	if we use "bl" then we must define to modify "lr".
	 */
	asm (
		"mov	a1, #0x42;"
		"bl  	putchar;"
		: 
		: 
		: "a1", "lr"
		);
#endif
}
