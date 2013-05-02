/**
 *	@brief		putchar twice in asm.
 */

#include <stdio.h>


/**
 *	@brief
 */
void	main(void)
{
//	putchar('A');
//	putchar('B');
//	putchar(0x41);
//	putchar(0x42);

	/*
	 *	call twice.
	 */
	asm (
		"mov	a1, #0x41;"
//		"b  	putchar;"					/* if use "b" then program go to End. */
		"bl 	putchar;"
		"mov	a1, #0x42;"
//		"b  	putchar;"					/* if use "b" then Segmentation fault. */
		"bl 	putchar;"
		: 
		: 
		: "a1", "lr"
		);
}
