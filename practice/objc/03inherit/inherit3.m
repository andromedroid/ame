/**
 *	@file
 *	@brief	override 2
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


void	callMethod(id obj)
{
	[obj method];
}

int		main(void)
{
	callMethod([SuperClass alloc]);
	callMethod([SubClass alloc]);

	return	0;
}
