/**
 *	@file
 *	@brief		number puzzle
 */

#include <stdio.h>
#include <string.h>

#include "puzzle.h"

extern	void	search3x3(char*, char*);

extern	void	search3x4(char*, char*, char*);
extern	void	search4x3(char*, char*, char*);


/**
 *	@brief		display Stage
 *	@param[in]	p_StgInfo			Stage Info
 */
void	dispStage(STAGE_INFO* p_StgInfo)
{
	UINT	uii,
			uij;

	for(uii = 0 ; uii < p_StgInfo->mHeight; uii++) {
		for(uij = 0 ; uij < p_StgInfo->mWidth; uij++) {
			printf("%c", p_StgInfo->mItems[uii * p_StgInfo->mWidth + uij]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 *	@brief		modify ascii -> integer
 *	@param[in]	p_StgInfo			Stage Info
 */
void	atoiArray(char* pac_int, char* pac_ascii, UINT size)
{
	char	c_Moji;
	UINT	uii;

	for(uii = 0 ; uii < size; uii++) {
		c_Moji	= pac_ascii[uii];

		if((c_Moji >= '0') &&
		   (c_Moji <= '9')) {
			pac_int[uii]	= c_Moji - 48;
		}
		else if((c_Moji >= 'A') &&
				(c_Moji <= 'Z')) {
			pac_int[uii]	= c_Moji - 55;
		}
		else if(c_Moji == '=') {
			pac_int[uii]	= '=';
		}
		else {
			pac_int[uii]	= '\0';
		}
	}
}

/**
 *	@brief		modify ascii -> integer
 *	@param[in]	p_init_state		state on start
 *	@param[in]	p_mid_state			state on first search end
 *	@param[in]	p_move_log			space moved log
 */
static	void	dummyFunc(char* p_init_state, char* p_mid_state, char* p_move_log)
{
	(void)memcpy(p_mid_state, p_init_state, 9);
}

/**
 *	@brief		main function
 *	@retval		0	success
 *	@retval		<0	error
 */
int		main(int argc, char* argv[])
{
	FILE		*fp_q,
				*fp_s,
				*fp_a;

	char		*fn_q,
				*fn_s,
				*fn_a;

	char		stgStr[STR_LENGTH_Q],
				ansStr[STR_LENGTH_I_LOG];
	DIR_USE_MAX	dirUseMax;
	UINT		ui_QuestionNum;
	STAGE_INFO	stgInfo;

	void		(*search)(char*, char*, char*);
	char		ac_InitState[STR_LENGTH_Q],
				ac_MidState[STR_LENGTH_Q],
				ac_InputLog[STR_LENGTH_I_LOG];

	if(argc < 4) {
		printf("[USAGE] %s [QUESTION FILE NAME] [SUPPORT FILE NAME] [ANSWER FILE NAME]\n", argv[0]);
		return	0;
	}

	fn_q	= argv[1];
	fn_s	= argv[2];
	fn_a	= argv[3];

	fp_q	= fopen(fn_q, "r");
	if(fp_q == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	fp_s	= fopen(fn_s, "r");
	if(fp_s == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	fp_a	= fopen(fn_a, "w");
	if(fp_a == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	/* get Direction use Max num */
	if(fgets(stgStr, STR_LENGTH_Q, fp_q) == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	getDirUseMax(&dirUseMax, stgStr);

	/* get Question num */
	if(fgets(stgStr, STR_LENGTH_Q, fp_q) == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	getQuestionNum(&ui_QuestionNum, stgStr);

	/* Stage Read */
	while(fgets(stgStr, STR_LENGTH_Q, fp_q) != NULL) {
		(void)getStageInfo(&stgInfo, stgStr);

		fgets(ansStr, STR_LENGTH_I_LOG, fp_s);

		if((stgInfo.mWidth  == 3) &&
		   (stgInfo.mHeight == 3)) {
			search	= dummyFunc;
		}
		else if((stgInfo.mWidth  == 3) &&
				(stgInfo.mHeight == 4)) {
			search	= search3x4;
		}
		else if((stgInfo.mWidth  == 4) &&
				(stgInfo.mHeight == 3)) {
			search	= search4x3;
		}
		else {
			fputs("\n", fp_a);
			continue;
		}

		printf("----\n\n");
		dispStage(&stgInfo);
		printf("Stage -> W:%d, H:%d\n", stgInfo.mWidth, stgInfo.mHeight);
		printf("\n");

		/* game Start */
		(void)memset(ac_InitState, '\0', sizeof(ac_InitState));
		(void)memset(ac_MidState, '\0', sizeof(ac_MidState));
		(void)memset(ac_InputLog, '\0', sizeof(ac_InputLog));

		atoiArray(ac_InitState,
				  stgInfo.mItems,
				  (UINT)(stgInfo.mWidth * stgInfo.mHeight));

		/* depth */
		search(ac_InitState,
			   ac_MidState,
			   ansStr);

		/* finish */
		search3x3(ac_MidState,
				  ac_InputLog);

		ansStr[strlen(ansStr) - 1]	= '\0';
//		strlcat(ansStr, ac_InputLog, sizeof(ansStr));
		strcat(ansStr, ac_InputLog);
		fputs(ansStr, fp_a);
		fputs("\n", fp_a);
	}

	fclose(fp_q);
	fclose(fp_a);

	return	0;
}
