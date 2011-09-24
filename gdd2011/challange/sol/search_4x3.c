/**
 *	@file
 *	@brief		4x3 -> 3x3
 */

#include <stdio.h>
#include <string.h>

#define	FIELD_WIDTH		4
#define	FIELD_HEIGHT	3
#define	FIELD_SIZE		(FIELD_WIDTH * FIELD_HEIGHT)

#define	SKIP_NUM		3

typedef	unsigned int	UINT;

static	const	char	ac_convert_state[FIELD_SIZE] = {
	0, -1, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8
};

static	const	char	ac_skip_state[SKIP_NUM] = {
	0, 4, 8
};


/**
 *	@brief		search space
 */
static	char	searchSpace(char* pac_items, int size)
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
 *	@brief		get space position to move direction
 */
static	char	getMovePlace(char c_SpcPos, char c_MoveDir)
{
	char	c_MovePos;

	if(c_MoveDir == 'L') {
		c_MovePos	= c_SpcPos - 1;
	}
	else if(c_MoveDir == 'R') {
		c_MovePos	= c_SpcPos + 1;
	}
	else if(c_MoveDir == 'U') {
		c_MovePos	= c_SpcPos - FIELD_WIDTH;
	}
	else if(c_MoveDir == 'D') {
		c_MovePos	= c_SpcPos + FIELD_WIDTH;
	}

	return	c_MovePos;
}

/**
 *	@brief		move array
 *	@param[out]	ac_MoveState		move state
 *	@param[in]	ac_clearState		clear state
 *	@param[in]	ac_clearState		move log
 */
static	void	moveState(char* ac_MoveState, char* ac_InitState, char* ac_MoveLog)
{
	UINT	ui_SpcPos	= (UINT)searchSpace(ac_InitState, FIELD_SIZE),
			ui_NextPos;
	UINT	uii;

	memcpy(ac_MoveState, ac_InitState, FIELD_SIZE);

	for(uii = 0; ac_MoveLog[uii] != '\0'; uii++) {
		ui_NextPos	= (UINT)getMovePlace(ui_SpcPos, ac_MoveLog[uii]);

		ac_MoveState[ui_SpcPos]		= ac_MoveState[ui_NextPos];
		ac_MoveState[ui_NextPos]	= 0;
		ui_SpcPos					= ui_NextPos;
	}
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

	for(uii = 0; uii < SKIP_NUM; uii++) {			/* for delete */
		ac_ClearState[(int)ac_skip_state[uii]]	= -1;
	}

	for(uii = 1; uii < FIELD_SIZE; uii++) {			/* for ac_convert_state loop */
		if(ac_convert_state[uii] == -1) {
			continue;
		}

		for(uij = 0; uij < FIELD_SIZE; uij++) {			/* for ac_ClearState loop */
			if((ac_ClearState[uij] == '=') ||
			   (ac_ClearState[uij] != uii)) {
				continue;
			}

//			printf("cs[%d]:%d, cv[%d]:%d\n", uij, ac_ClearState[uij], uii, ac_convert_state[uii]);
			ac_ClearState[uij]	= ac_convert_state[uii];

			break;
		}
	}

//	printf("clear :\n");
//	printState((char(*)[FIELD_WIDTH])ac_ClearState);

	for(uij = 0, uii = 0; uii < FIELD_SIZE; uii++) {		/* for ac_ClearState loop */
		if(ac_ClearState[uii] == -1) {
			continue;
		}

//		printf("ns[%d]:%d, cs[%d]:%d\n", uij, ac_NextState[uij], uii, ac_ClearState[uii]);
		ac_NextState[uij++]	= ac_ClearState[uii];
	}
}

/**
 *	@brief		search 3x4 -> 3x3
 *	@param[in]	ac_InitState		state on start
 *	@param[out]	ac_MidState			state on first search end
 *	@param[in]	ac_MoveLog			space moved log
 */
void	search4x3(char* ac_InitState, char* ac_MidState, char* ac_MoveLog)
{
	char	ac_MoveState[FIELD_SIZE];

	printState((char(*)[FIELD_WIDTH])ac_InitState);

	moveState(ac_MoveState, ac_InitState, ac_MoveLog);

	printf("moved :\n");
	printState((char(*)[FIELD_WIDTH])ac_MoveState);

	convertState(ac_MidState, ac_MoveState);

//	printf("converted :\n");
//	printState((char(*)[FIELD_WIDTH])ac_MidState);
}
