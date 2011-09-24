/**
 *	@brief	number puzzle header
 */

#define	STR_LENGTH_Q			64
#define	STR_LENGTH_NUM			16
#define	STR_LENGTH_I_LOG		1024
#define	STAGE_MAX_WIDTH			6
#define	STAGE_MAX_HEIGHT		6

#define	RTN_ERR(func, line)		{printf("Error [%s()] val: %d\n", func, line); return -1;}

#define	FALSE					0
#define	TRUE					(!FALSE)

typedef	signed char		B;
typedef	signed short	H;
typedef	signed long		W;

typedef	unsigned char	UB;
typedef	unsigned short	UH;
typedef	unsigned long	UW;
typedef	unsigned int	UINT;
typedef	unsigned char	BOOL;

typedef	struct {
	UINT	mLeft;
	UINT	mRight;
	UINT	mUp;
	UINT	mDown;
} DIR_USE_MAX;

typedef	struct {
	UB		mWidth;
	UB		mHeight;
	char	mItems[STR_LENGTH_Q - 4];
} STAGE_INFO;

typedef	struct {
	UB		mX;
	UB		mY;
} STAGE_0_POS;

/* getData.c */
extern	void	getDirUseMax(DIR_USE_MAX*, char*);
extern	void	getQuestionNum(UINT*, char*);
extern	BOOL	getStageInfo(STAGE_INFO*, char*);
