/**
 *	@file
 *	@brief	protect is available for grandchild .
 */

#import	<objc/Object.h>
#import	<stdio.h>


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
	printf(	"%s\tpub:%d, pro:%d, pri:%d\n",
			__func__,
			pub, pro, pri);
}
@end

@implementation	SubClass
- (void)printB
{
	printf(	"%s\tpub:%d, pro:%d, pri:%d\n",
			__func__,
//			pub, pro, pri);
			pub, pro, -1);
}
@end

@implementation	SsClass
- (void)printC
{
	printf(	"%s\tpub:%d, pro:%d, pri:%d\n",
			__func__,
//			pub, pro, pri);
			pub, pro, -1);
}
@end


int		main(void)
{
	SsClass	*ssc	= [[SsClass new] initVar:64:48:36];

	[ssc printA];
	[ssc printB];
	[ssc printC];

	printf(	"%s\tpub:%d, pro:%d, pri:%d\n",
			__func__,
//			ssc->pub, ssc->pro, ssc->pri);
//			ssc->pub, ssc->pro, -1);
			ssc->pub, -1, -1);

	[ssc free];

	return	0;
}
