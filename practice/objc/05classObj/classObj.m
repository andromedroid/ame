/**
 *	@file
 *	@brief	
 */

#import	<objc/Object.h>
#import	<stdio.h>


@interface	ClassObj	: Object
+ (void)print;
- (id)init;
@end

@implementation	ClassObj
+ (void)print
{
	printf(	"%s\n",
			__func__);
}
- (id)init;
{
	self	= [super init];

	printf(	"%s\n",
			__func__);

	return	self;
}
@end


int		main(void)
{
//	Class	*clsobj	= [ClassObj class];
	Class	clsobj	= [ClassObj class];

	[clsobj print];							// == [ClassObj print];
	[[clsobj new] free];					// == [[ClassObj new] free];
	[clsobj free];							// == [ClassObj free]

	return	0;
}
