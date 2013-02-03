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
		: "=g" (sum)
		:
		: "a1"
		);

	printf(	"sum : %u\n",
#if	1
			sum);							/* Why assemble NG !? (only AC100 ???) */
	/* ->	ldr	a1, r4; 		add	a1, a1, #4;	str	a1, r4	*/
#else
			(uint)&sum);
	/* ->	ldr	a1, [r7, #4];	add	a1, a1, #4;	str	a1, [r7, #4]	*/
#endif

	return	0;
}
