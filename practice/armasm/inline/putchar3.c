/**
 *	@brief		putchar loop in asm and use label.
 */

#include <stdio.h>


/**
 *	@brief
 */
void	main(void)
{
	asm (
		"mov	a1, #0x41;"
		"Loop:"
		"bl 	putchar;"
		"add	a1, a1, #1;"
		"cmp	a1, #0x50;"
		"ble	Loop;"
		"mov	a1, #0x0A;"			/* LF */
		"bl 	putchar;"
		: 
		: 
		: "a1", "lr"
		);
}
