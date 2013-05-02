/**
 *	@file
 *	@brief	print from common func.
 */

#import	<objc/Object.h>
#import	<stdio.h>


void	printFunc(	const char*	str,
					int			a,
					int			b,
					int			c)
{
	printf(	"%s\ta:%d, b:%d, c:%d\n",
			str, a, b, c);
}


@interface	SuperClass	: Object
{
@public
	int		pub;
@protected
	int		pro;
@private
	int		pri;
}
- (id)initVar:(int)a:(int)b:(int)c;
- (void)printA;
@end

@interface	SubClass	: SuperClass
- (void)printB;
@end

@interface	SsClass	: SubClass
- (void)printC;
@end

@implementation	SuperClass
- (id)initVar:(int)a:(int)b:(int)c
{
	pub	= a;
	pro	= b;
	pri	= c;
}
- (void)printA
{
	printFunc(	__func__,
				pub, pro, pri);
}
@end

@implementation	SubClass
- (void)printB
{
	printFunc(	__func__,
//				pub, pro, pri);
				pub, pro, -1);
}
@end

@implementation	SsClass
- (void)printC
{
	printFunc(	__func__,
//				pub, pro, pri);
				pub, pro, -1);
}
@end


int		main(void)
{
	SsClass	*ssc	= [[SsClass new] initVar:64:48:36];

	[ssc printA];
	[ssc printB];
	[ssc printC];

	printFunc(	__func__,
//				ssc->pub, ssc->pro, ssc->pri);
//				ssc->pub, ssc->pro, -1);
				ssc->pub, -1, -1);

	[ssc free];

	return	0;
}
