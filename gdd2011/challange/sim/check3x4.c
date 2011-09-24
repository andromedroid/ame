/**
 *	@file
 *	@brief		3x4 -> 3x3
 */

#include <stdio.h>
#include "puzzle.h"

#define	FIELD_WIDTH		3
#define	FIELD_HEIGHT	4
#define	FIELD_SIZE		(FIELD_WIDTH * FIELD_HEIGHT)

#define	ANSWER_PLACE	3

static	const	char	ac_final_state[ANSWER_PLACE] = {
	0, 1, 2
};

/**
 *	@brief		解を表示
 */
static	void	printState(char (*p_State)[FIELD_WIDTH])
{
	UINT	uii,
			uij;

	for(uii = 0; uii < FIELD_HEIGHT; uii++) {
		for(uij = 0; uij < FIELD_WIDTH; uij++) {
			printf("%3d", p_State[uii][uij]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 *	@brief		check score
 *	@param[in]	ac_CurrState		current state
 *	@return		score	
 */
int		checkScore3x4(char* stgStr)
{
	UINT	ui_Score,
			ui_Val,
			uii;

//	printState((char(*)[FIELD_WIDTH])stgStr);

	for(ui_Score = 0, uii = 0; uii < ANSWER_PLACE; uii++) {
		ui_Val	= (UINT)ac_final_state[uii];

		if((stgStr[ui_Val] == (ac_final_state[uii] + 1)) ||
		   (stgStr[ui_Val] == '=')) {
			ui_Score++;
		}
	}

	if(ui_Score < ANSWER_PLACE) {
		return	0;
	}

	return	1;
}
