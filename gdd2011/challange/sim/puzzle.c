/**
 *	@brief	number puzzle
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "puzzle.h"

extern	int		myKbhit(void);

extern	int		checkScore3x4(char*);
extern	int		checkScore4x3(char*);


/**
 *	@brief		make Stage
 *	@param[out]	pac_Stage			Stage Field
 *	@param[out]	p_Stg0Pos			'0' Position
 *	@param[in]	p_StgInfo			Stage Info
 */
void	makeStage(	char			(*pac_Stage)[STAGE_MAX_WIDTH + 1],
					STAGE_0_POS*	p_Stg0Pos,
					STAGE_INFO*		p_StgInfo)
{
	UINT	uii,
			uij;

	for(uii = 0; uii < p_StgInfo->mHeight; uii++) {
		for(uij = 0; uij < p_StgInfo->mWidth; uij++) {
			pac_Stage[uii][uij]	= p_StgInfo->mItems[(uii * p_StgInfo->mWidth) + uij];

			if(pac_Stage[uii][uij] == '0') {
				p_Stg0Pos->mX	= (UB)uij;
				p_Stg0Pos->mY	= (UB)uii;
			}
		}
		pac_Stage[uii][p_StgInfo->mWidth]	= '\0';
	}
}

/**
 *	@brief		display Stage
 *	@param[in]	pac_Stage			Stage Field
 *	@param[in]	p_StgInfo			Stage Info
 */
void	dispStage(	char		(*pac_Stage)[STAGE_MAX_WIDTH + 1],
					STAGE_INFO* p_StgInfo)
{
	UINT	uii,
			uij;

	for(uii = 0 ; uii < p_StgInfo->mHeight; uii++) {
		for(uij = 0 ; uij < p_StgInfo->mWidth; uij++) {
			printf("%c ", pac_Stage[uii][uij]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 *	@brief		modify ascii -> integer
 *	@param[in]	p_StgInfo			Stage Info
 */
void	atoiArray(	char*	pac_int,
					char	(*pac_ascii)[STAGE_MAX_WIDTH + 1],
					UINT	width,
					UINT	height)
{
	char	size	= width * height;
	char	ac_CurrState[size];
	char	c_Moji;
	UINT	uii,
			uij;

	for(uii = 0 ; uii < height; uii++) {
		for(uij = 0 ; uij < width; uij++) {
			ac_CurrState[uii * width + uij]	= pac_ascii[uii][uij];
		}
	}

	for(uii = 0 ; uii < size; uii++) {
		c_Moji	= ac_CurrState[uii];

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
 *	@brief		main function
 *	@retval		0	success
 *	@retval		<0	error
 */
int		main(int argc, char* argv[])
{
	FILE		*fp_q,
				*fp_a;

	char		*fn_q,
				*fn_a;

	char		stgStr[STR_LENGTH_Q],
				ansStr[STR_LENGTH_I_LOG];
	DIR_USE_MAX	dirUseMax;
	UINT		ui_QuestionNum;
	STAGE_INFO	stgInfo;

	char		ac_Stage[STAGE_MAX_HEIGHT][STAGE_MAX_WIDTH + 1];

	STAGE_0_POS	stg0Pos	= {0xFF, 0xFF};

	char		c_InputKey,
				ac_InputLog[STR_LENGTH_I_LOG];

	UINT		ui_InputNum;

	if(argc < 3) {
		printf("[USAGE] %s [QUESTION FILE NAME] [ANSWER FILE NAME]\n", argv[0]);
		return	0;
	}

	fn_q	= argv[1];
	fn_a	= argv[2];

	fp_q	= fopen(fn_q, "r");
	if(fp_q == NULL) {
		RTN_ERR(__FUNCTION__, __LINE__);
	}

	fp_a	= fopen(fn_a, "r+");
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

//		if((stgInfo.mWidth  == 3) &&
//		   (stgInfo.mHeight == 4)) {
		if((stgInfo.mWidth  == 4) &&
		   (stgInfo.mHeight == 3)) {
			;
		}
		else {
			fputs("\n", fp_a);
			continue;
		}

		if(fgets(ansStr, STR_LENGTH_I_LOG, fp_a) != NULL) {
			if(ansStr[0] != '\n') {
				printf("%s\n", ansStr);
				continue;
			}
			lseek((int)fp_a, -1, SEEK_CUR);
		}

		/* make stage and get 0 position */
		makeStage(ac_Stage, &stg0Pos, &stgInfo);

		if((stg0Pos.mX > STAGE_MAX_WIDTH) ||
		   (stg0Pos.mY > STAGE_MAX_HEIGHT)) {
			RTN_ERR(__FUNCTION__, __LINE__);
		}

		dispStage(ac_Stage, &stgInfo);
		printf("\n");
		printf("Stage -> W:%d, H:%d\n", stgInfo.mWidth, stgInfo.mHeight);
		printf("0 Pos -> X:%d, Y:%d\n", stg0Pos.mX, stg0Pos.mY);
		printf("\n");

		/* game Start */
		(void)memset(ac_InputLog, '\0', sizeof(ac_InputLog));
		ui_InputNum	= 0;

		while('A') {
			if(myKbhit() == 0) {
				continue;
			}
			c_InputKey = getchar();

			if(c_InputKey == 'q') {
				fclose(fp_q);
				fclose(fp_a);
				return	0;
			}
			else if(c_InputKey == 's') {		/* skip */
				break;
			}
			else if(c_InputKey == 'h') {		/* move Left */
				if(stg0Pos.mX == 0) {
					printf("You can't move.\n");
				}
				else if(ac_Stage[stg0Pos.mY][stg0Pos.mX - 1] == '=') {
					printf("You can't move.\n");
				}
				else {
					ac_Stage[stg0Pos.mY][stg0Pos.mX]	= ac_Stage[stg0Pos.mY][stg0Pos.mX - 1];
					ac_Stage[stg0Pos.mY][--stg0Pos.mX]	= '0';
					ac_InputLog[ui_InputNum++]			= 'L'; 
				}
			}
			else if(c_InputKey == 'j') {		/* move Down */
				if((stg0Pos.mY + 1) >= stgInfo.mHeight) {
					printf("You can't move.\n");
				}
				else if(ac_Stage[stg0Pos.mY + 1][stg0Pos.mX] == '=') {
					printf("You can't move.\n");
				}
				else {
					ac_Stage[stg0Pos.mY][stg0Pos.mX]	= ac_Stage[stg0Pos.mY + 1][stg0Pos.mX];
					ac_Stage[++stg0Pos.mY][stg0Pos.mX]	= '0';
					ac_InputLog[ui_InputNum++]			= 'D'; 
				}
			}
			else if(c_InputKey == 'k') {		/* move Up */
				if(stg0Pos.mY == 0) {
					printf("You can't move.\n");
				}
				else if(ac_Stage[stg0Pos.mY - 1][stg0Pos.mX] == '=') {
					printf("You can't move.\n");
				}
				else {
					ac_Stage[stg0Pos.mY][stg0Pos.mX]	= ac_Stage[stg0Pos.mY - 1][stg0Pos.mX];
					ac_Stage[--stg0Pos.mY][stg0Pos.mX]	= '0';
					ac_InputLog[ui_InputNum++]			= 'U'; 
				}
			}
			else if(c_InputKey == 'l') {		/* move Right */
				if((stg0Pos.mX + 1) >= stgInfo.mWidth) {
					printf("You can't move.\n");
				}
				else if(ac_Stage[stg0Pos.mY][stg0Pos.mX + 1] == '=') {
					printf("You can't move.\n");
				}
				else {
					ac_Stage[stg0Pos.mY][stg0Pos.mX]	= ac_Stage[stg0Pos.mY][stg0Pos.mX + 1];
					ac_Stage[stg0Pos.mY][++stg0Pos.mX]	= '0';
					ac_InputLog[ui_InputNum++]			= 'R'; 
				}
			}
			else {
				continue;
			}

			printf("Input log : %s\n", ac_InputLog);
			dispStage(ac_Stage, &stgInfo);
			printf("\n");

			atoiArray(stgStr,
					  ac_Stage,
					  (UINT)stgInfo.mWidth,
					  (UINT)stgInfo.mHeight);

//			if(checkScore3x4(stgStr) != 0) {
			if(checkScore4x3(stgStr) != 0) {
				printf("Clear !\n\n\n");
				break;
			}
		}

		fputs(ac_InputLog, fp_a);
		fputs("\n", fp_a);
	}

	fclose(fp_q);
	fclose(fp_a);

	return	0;
}
