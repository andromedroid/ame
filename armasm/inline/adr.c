/**
 *	@brief		usage of C pointer variable on inline arm gnu asm.
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
	uint	var		= 0;
	uint	memleak	= 0xFFFFFFFF;
	uint	*adr	= &var;

	/*
	 *	using C variable on inline assembly.
	 */
	asm (
		"ldr	a1, %[v];"
		"add	a1, a1, #4;"				/* var = var + 4 */
		"str	a1, %[v]"
		: [v] "=g" (var)
		:
		: "a1"
		);

	printf(	"var : 0x%08X : %u\n",
			(uint)&var,
			var);

	/*
	 *	using C address (pointer) on inline assembly.
	 *	(this is wrong usage)
	 *
	 *	pointer must be defined as "read only" variables. (maybe)
	 */
	asm (
		"ldr	a1, %[a];"
		"add	a1, a1, #4;"				/* adr = adr + 4Byte */
		"str	a1, %[a]"
//		: [a] "=g" (adr)	/* Error: cannot represent T32_OFFSET_IMM relocation in this object file format */
		:
		: [a] "g" (adr)
		: "a1"
		);

	printf(	"adr : 0x%08X : %u (result of wrong usage)\n",
			(uint)adr,
			*adr);

	adr	-= 1;								/* reset address. */

	/*
	 *	using C address (pointer) on inline assembly.
	 *	 ->	use another register.
	 */
	asm (
		"ldr	a1, %[a];"
		"ldr	a2, [a1];"
		"add	a2, a2, #4;"
		"str	a2, [a1]"
		:
		: [a] "g" (adr)
		: "a1", "a2"
		);

	printf(	"adr : 0x%08X : %u\n",
			(uint)adr,
			*adr);

	return	0;
}
