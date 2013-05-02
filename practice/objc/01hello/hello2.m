/**
 *	@file
 *	@brief	Hello World on Objective-C with class method.
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	Hello	: Object
+ (void)print;
@end

@implementation	Hello
+ (void)print {
	printf(	"Hello, World.\n");
}
@end


int		main(void)
{
	[Hello print];

	return	0;
}
