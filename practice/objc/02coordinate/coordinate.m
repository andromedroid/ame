/**
 *	@file
 *	@brief
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	Cdn	: Object
{
	int	ix, iy;
}
- (id)init;
- (int)getX;
- (int)getY;
//- (void)setPoint:(int)ix:(int)iy;
- (void)setPoint:(int)x:(int)y;
@end

@implementation	Cdn
- (id)init
{
	printf(	"pre  Object init : 0x%08X, *0x%08X\n",
			(unsigned int)self,
			(unsigned int)&self);

	self	= [super init];

	printf(	"post Object init : 0x%08X, *0x%08X\n",
			(unsigned int)self,
			(unsigned int)&self);

	ix	= 0;
	iy	= 0;

	return	self;
}

- (int)getX {
	return	ix;
}

- (int)getY {
	return	iy;
}

#if	0
- (void)setPoint:(int)ix:(int)iy {
	self->ix	= ix;
	self->iy	= iy;
}
#else
- (void)setPoint:(int)x:(int)y {
	ix	= x;
	iy	= y;
}
#endif
@end


int		main(void)
{
	Cdn		*cdn	= [Cdn new];

	[cdn setPoint:480:320];

	printf(	"X:%d, Y:%d\n",
			[cdn getX],
			[cdn getY]);

	[cdn free];

	return	0;
}
