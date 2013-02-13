/**
 *	@brief		string print with putchar & shift mnemonic.
 */

#include <stdio.h>

typedef	signed char		s8;
typedef	unsigned char	u8;
typedef	signed short	s16;
typedef	unsigned short	u16;
typedef	signed long		s32;
typedef	unsigned long	u32;
typedef	unsigned int	uint;


/**
 *	@brief
 */
void	shiftprint(u8 *str)
{
	asm (
		"ldr	r12, %[s];"
		"ldrb	a1, [r12];"
		"loop:"
		"push	{a1, r12};"			/* without push/pop then a1 is broken in putchar. */
		"bl  	putchar;"
		"pop	{a1, r12};"			/* {} : register list */
		"add	r12, r12, #1;"
		"ldrb	a1, [r12];"
		"cmp	a1, #0;"
		"bne	loop;"
		: [s] "=m" (str)
		: 
		: "a1", "r12", "lr"
		);
}

/**
 *	@brief
 */
int		main(void)
{
	shiftprint("Hello, World !\n");

	return	0;
}
