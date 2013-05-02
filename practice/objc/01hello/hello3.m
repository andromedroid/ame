/**
 *	@file
 *	@brief	Hello World on Objective-C with instance method.
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	Hello	: Object
- (id)init;
- (void)print;
@end

@implementation	Hello
- (id)init
{
	self	= [super init];

	return	self;
}

- (void)print {
	printf(	"Hello, World.\n");
}
@end


int		main(void)
{
#if	0
//	id		hw	= [[Hello alloc] init];
//	Hello	*hw	= [[Hello alloc] init];
	Hello	*hw	= [Hello new];

	[hw print];

	[hw free];
#else
//	Hello	*hw	= [[[Hello alloc] init] print];
	[[[Hello alloc] init] print];
#endif

	return	0;
}
