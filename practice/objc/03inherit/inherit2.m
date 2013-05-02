/**
 *	@file
 *	@brief	override
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
	printf(	"%s\n",
			__func__);
}
@end


int		main(void)
{
	[[SuperClass alloc] method];
	[[SubClass alloc] method];

	return	0;
}
