/**
 *	@brief		usage of shift mnemonic.
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
//void	shiftprint(uint arg)
void	shiftprint(u8 *str)
{
	asm (
//		"ldr	r12, %[s];"
//		"ldr	a1, [r12];"
		"ldr	a1, [a1];"
		"loop:"
		"push	{a1};"				/* without push/pop then a1 is broken in putchar. */
		"bl  	putchar;"
		"pop	{a1};"				/* {} : register list */
		"lsr	a1, #8;"
		"cmp	a1, #0;"
		"bne	loop;"
		"mov	a1, #0x0A;"			/* LF */
		"bl  	putchar;"
//		: [a] "=m" (arg)
		: [s] "=m" (str)
		: 
		: "a1", "lr"
		);
}

/**
 *	@brief
 */
int		main(void)
{
//	shiftprint(0x41424344);
	shiftprint("ABCD");

	return	0;
}
