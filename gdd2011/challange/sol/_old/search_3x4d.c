/**
 *	@file
 *	@brief		3x4 -> 3x3
 */

#include <stdio.h>
#include <string.h>

#define	FIELD_WIDTH		3
#define	FIELD_HEIGHT	4
#define	FIELD_SIZE		(FIELD_WIDTH * FIELD_HEIGHT)

#define	ANSWER_PLACE	3
#define	AVAIL_STATE_NUM	256

#define	MOVE_MAX		128
#define	SUM_MOVE_MAX	512

typedef	unsigned int	UINT;

typedef	struct {
	char	ac_Array[FIELD_SIZE];
	char	ac_mMoveLog[MOVE_MAX];
	char	c_SpcPos;
	char	c_PrevPos;
} AVAIL_STATE;

static	const	char	ac_final_state[ANSWER_PLACE] = {
	0, 1, 2
};

static	const	char	ac_convert_state[FIELD_SIZE] = {
	0, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8
};

/* 3 x 4 隣接リスト */
static	const	char	ac_Adjacent[FIELD_SIZE][5] = {
	{ 1,  3, -1, -1, -1},
	{ 0,  2,  4, -1, -1},
	{ 1,  5, -1, -1, -1},
	{ 0,  4,  6, -1, -1},
	{ 1,  3,  5,  7, -1},
	{ 2,  4,  8, -1, -1},
	{ 3,  7,  9, -1, -1},
	{ 4,  6,  8, 10, -1},
	{ 5,  7, 11, -1, -1},
	{ 6, 10, -1, -1, -1},
	{ 7,  9, 11, -1, -1},
	{ 8, 10, -1, -1, -1}
};


/**
 *	@brief		search space
 */
char	searchSpace(char* pac_items, int size)
{
	int		ii;

	for(ii = 0; ii < size; ii++) {
//		printf("item[%d] is %d\n", ii, pac_items[ii]);

		if(pac_items[ii] == 0) {
//			printf("0 pos is %d\n", ii);
			break;
		}
	}

	return	(char)ii;
}

/**
 *	@brief		get space position to move direction
 */
char	getMoveDirection(char prev, char next)
{
	if((next - prev) == -1) {
		return	'L';
	}
	else if((next - prev) == 1) {
		return	'R';
	}
	else if((next - prev) == -FIELD_WIDTH) {
		return	'U';
	}
	else if((next - prev) == FIELD_WIDTH) {
		return	'D';
	}

	return	'?';
}

/**
 *	@brief		check score
 *	@param[in]	ac_CurrState		current state
 *	@return		score	
 */
static	int		checkScore(char* ac_CurrState)
{
	UINT	ui_Score,
			ui_Val,
			uii;

	for(ui_Score = 0, uii = 0; uii < ANSWER_PLACE; uii++) {
		ui_Val	= (UINT)ac_final_state[uii];

		if((ac_CurrState[ui_Val] == (ac_final_state[uii] + 1)) ||
		   (ac_CurrState[ui_Val] == '=')) {
			ui_Score++;
		}
	}

	return	ui_Score;
}

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
 *	@brief		convert array
 *	@param[out]	ac_NextState		next state
 *	@param[in]	ac_clearState		clear state
 */
static	void	convertState(char* ac_NextState, char* ac_ClearState)
{
	UINT	uii,
			uij;

	for(uii = 1; uii < FIELD_SIZE; uii++) {			/* for ac_convert_state loop */
		for(uij = 0; uij < FIELD_SIZE; uij++) {			/* for ac_ClearState loop */
			if(ac_ClearState[uij] != uii) {
				continue;
			}

			ac_ClearState[uij]	= ac_convert_state[uii];
		}
	}

	for(uij = 0, uii = 0; uii < FIELD_SIZE; uii++) {		/* for ac_ClearState loop */
		if(ac_ClearState[uii] == -1) {
			continue;
		}

		ac_NextState[uij++]	= ac_ClearState[uii];
	}

	if(uij > (FIELD_SIZE - ANSWER_PLACE)) {
		printf("[ERR] next state overflow.\n");
	}
}

/**
 *	@brief		search 3x4 -> 3x3
 *	@param[in]	ac_InitState		state on start
 *	@param[in]	ac_MidState			state on first search end
 *	@param[in]	ac_MoveLog			space moved log
 */
void	search3x4(char* ac_InitState, char* ac_MidState, char* ac_MoveLog)
{
	char		ac_CurrState[FIELD_SIZE],
				ac_CurrMoveLog[SUM_MOVE_MAX],
				c_CurrSpcPos	= searchSpace(ac_InitState, FIELD_SIZE);
	AVAIL_STATE	ac_AvailState[AVAIL_STATE_NUM];
	const UINT	ui_GoalScore	= ANSWER_PLACE;
	UINT		ui_MaxScore		= checkScore(ac_InitState);

	memcpy(ac_CurrState, ac_InitState, FIELD_SIZE);

	while(ui_MaxScore != ui_GoalScore) {
		AVAIL_STATE	*p_NowState,
					*p_NextState;
		UINT	ui_SpcPos,
				ui_AdjaPos;
		UINT	ui_Score	= 0,
				ui_Anum		= 0,
				uii;
		char	ac_Move[2]	= {'\0', '\0'};

		ui_Score	= 0;
		ui_Anum		= 0;

		memset(ac_AvailState, 0, sizeof(ac_AvailState));
		memcpy(ac_AvailState[ui_Anum].ac_Array, ac_CurrState, FIELD_SIZE);
		ac_AvailState[ui_Anum].c_SpcPos		= c_CurrSpcPos;
		ac_AvailState[ui_Anum].c_PrevPos	= 0x7F;

		for(ui_Anum = 0; ui_Anum < (AVAIL_STATE_NUM - 3); ui_Anum += uii) {
			ui_SpcPos	= ac_AvailState[ui_Anum].c_SpcPos;

			for(uii = 0;
				(ui_AdjaPos = (UINT)ac_Adjacent[ui_SpcPos][uii]) != -1;
				uii++) {
				if((ac_AvailState[ui_Anum].ac_Array[ui_AdjaPos] == ac_AvailState[ui_Anum].c_PrevPos) ||
				   (ac_AvailState[ui_Anum].ac_Array[ui_AdjaPos] == '=')) {
					continue;
				}

				p_NowState	= &ac_AvailState[ui_Anum];
				p_NextState	= &ac_AvailState[ui_Anum + 1];

				/* 状態をコピー */
				memcpy(p_NextState->ac_Array,
					   p_NowState->ac_Array,
					   FIELD_SIZE);

				/* 移動 */
				p_NextState->ac_Array[ui_SpcPos]	= p_NextState->ac_Array[ui_AdjaPos];
				p_NextState->ac_Array[ui_AdjaPos]	= 0;
				p_NextState->c_SpcPos				= (char)ui_AdjaPos;
				p_NextState->c_PrevPos				= p_NowState->c_SpcPos;

				ac_Move[0]	= getMoveDirection(p_NowState->c_SpcPos, p_NextState->c_SpcPos);
				strcat(p_NextState->ac_mMoveLog, ac_Move);

				ui_Score	= checkScore(p_NextState->ac_Array);
				if(ui_Score > ui_MaxScore) {
					ui_MaxScore	= ui_Score;

					memcpy(ac_CurrState, p_NextState->ac_Array, FIELD_SIZE);
					c_CurrSpcPos	= p_NextState->c_SpcPos;
					strcat(ac_CurrMoveLog, p_NextState->ac_mMoveLog);

					ui_Anum	= AVAIL_STATE_NUM;		/* break */
					break;
				}
			}
		}
	}

	printf("3x4 clear !\n");
	printState((char(*)[FIELD_WIDTH])ac_CurrState);

	convertState(ac_MidState, ac_CurrState);
	strcat(ac_MoveLog, ac_CurrMoveLog);
}
