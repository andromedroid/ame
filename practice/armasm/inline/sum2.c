/**
 *	@brief		usage of C variable on inline arm gnu asm.
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
int		main(void)
{
	uint	sum	= 0;

	asm (
		"ldr	a1, %0;"
		"add	a1, a1, #4;"				/* sum = sum + 4 */
		"str	a1, %0"
//		: "=g" (sum)						/* it become NG when assemble. refer sum1.c */
		: "=m" (sum)
		: 
		: "a1"
		);

	printf(	"sum : %u\n",
			sum);

	/* store status flags. (we can use variable instead of "%0")*/
	asm (
		"mrs a1, cpsr;"
		"str a1, %[s];"
		: [s] "=m" (sum)
		: 
		: "a1"
		);

	printf(	"sum : 0x%08X\n",
			sum);

	return	0;
}
