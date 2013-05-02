/**
 *	@file
 *	@brief
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	SuperClass	: Object
- (void)methodA;
@end

@interface	SubClass	: SuperClass
- (void)methodB;
@end

@implementation	SuperClass
- (void)methodA
{
	printf(	"%s\n",
			__func__);
}
@end

@implementation	SubClass
- (void)methodB
{
	printf(	"%s\n",
			__func__);
}
@end


int		main(void)
{
	SubClass	*Sub	= [SubClass new];

	[Sub methodA];
	[Sub methodB];

	[Sub free];

	return	0;
}
