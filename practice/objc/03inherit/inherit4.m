/**
 *	@file
 *	@brief	override 3
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	SuperClass	: Object
- (void)method;
@end

@interface	SubClass	: SuperClass
- (void)method;
@end

@implementation	SuperClass
- (void)method
{
	printf(	"%s\n",
			__func__);
}
@end

@implementation	SubClass
- (void)method
{
	[super method];

	printf(	"%s\n",
			__func__);
}
@end


int		main(void)
{
	[[SubClass alloc] method];

	return	0;
}
