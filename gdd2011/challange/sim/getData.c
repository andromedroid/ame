/**
 *	@brief	to get data modules
 */

#include <stdio.h>
#include <stdlib.h>

#include "puzzle.h"


/**
 *	@brief		get Direction use Max num
 *	@param[out]	p_dirUseMax		Direction Use Max num
 *	@param[in]	p_numMaxStr		String
 */
void	getDirUseMax(DIR_USE_MAX* p_dirUseMax, char* p_numMaxStr)
{
	char	numStr[STR_LENGTH_NUM];
	UINT	uii	= 0,
			uij;

	/* get LEFT MAX */
	for(uij = 0;
		p_numMaxStr[uii] != ' ';
		uii++, uij++) {
		numStr[uij]	= p_numMaxStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_dirUseMax->mLeft	= atoi(numStr);

	/* get RIGHT MAX */
	for(uij = 0;
		p_numMaxStr[uii] != ' ';
		uii++, uij++) {
		numStr[uij]	= p_numMaxStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_dirUseMax->mRight	= atoi(numStr);

	/* get UP MAX */
	for(uij = 0;
		p_numMaxStr[uii] != ' ';
		uii++, uij++) {
		numStr[uij]	= p_numMaxStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_dirUseMax->mUp	= atoi(numStr);

	/* get DOWN MAX */
	for(uij = 0;
		p_numMaxStr[uii] != '\0';
		uii++, uij++) {
		numStr[uij]	= p_numMaxStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_dirUseMax->mDown	= atoi(numStr);

#if	0	/* check code */
	printf("uii = %d\n", uii);
	printf("uij = %d\n", uij);
	printf("%s\n", numStr);
	printf("%d\n", p_dirUseMax->mDown);
#endif
}

/**
 *	@brief		get Direction use Max num
 *	@param[out]	pui_Qnum		Question Num
 *	@param[in]	p_numQstr		String
 */
void	getQuestionNum(UINT* pui_Qnum, char* p_numQstr)
{
	char	numStr[STR_LENGTH_NUM];
	UINT	uii	= 0,
			uij;

	/* get LEFT MAX */
	for(uij = 0;
		p_numQstr[uii] != '\0';
		uii++, uij++) {
		numStr[uij]	= p_numQstr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	*pui_Qnum			= atoi(numStr);
}

/**
 *	@brief		get Stage Info
 *	@param[out]	p_stgInfo			Stage Info
 *	@param[in]	p_stgInfoStr		String
 */
void	getStageInfo(STAGE_INFO* p_stgInfo, char* p_stgInfoStr)
{
	char	numStr[STR_LENGTH_NUM];
	UINT	uii	= 0,
			uij;

	/* get stage width */
	for(uij = 0;
		p_stgInfoStr[uii] != ',';
		uii++, uij++) {
		numStr[uij]	= p_stgInfoStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_stgInfo->mWidth	= atoi(numStr);

	/* get stage height */
	for(uij = 0;
		p_stgInfoStr[uii] != ',';
		uii++, uij++) {
		numStr[uij]	= p_stgInfoStr[uii];
	}
	uii++;
	numStr[uij]			= '\0';
	p_stgInfo->mHeight	= atoi(numStr);

	/* get stage items */
	for(uij = 0;
		p_stgInfoStr[uii] != '\0';
		uii++, uij++) {
		p_stgInfo->mItems[uij]	= p_stgInfoStr[uii];
	}
	uii++;
	p_stgInfo->mItems[uij]	= '\0';
}
