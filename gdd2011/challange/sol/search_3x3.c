/**
 *	@file
 *	@brief		for 3x3
 *	@note
 *		-		I learned by http://www.geocities.jp/m_hiroi/puzzle/eight.html
 */

#include <stdio.h>
#include <string.h>

#define	FALSE			0
#define	TRUE			1
#define	GOAL			2

#define	FIELD_WIDTH		3
#define	FIELD_HEIGHT	3
#define	FIELD_SIZE		(FIELD_WIDTH * FIELD_HEIGHT)

/* 状態数 (9! / 2) */
#define	MAX_STATE		181440

#define	MAX_MOVE		32

static	const	char	ac_final_state[FIELD_SIZE] = {
	1, 2, 3, 4, 5, 6, 7, 8, 0
};

static	const	int		ac_fact_table[FIELD_SIZE] = {
	40320, 5040, 720, 120, 24, 6, 2, 1, 0,
};

/* 3 x 3 隣接リスト */
const	char	adjacent[FIELD_SIZE][5] = {
	{1, 3,-1,-1,-1},
	{0, 2, 4,-1,-1},
	{1, 5,-1,-1,-1},
	{0, 4, 6,-1,-1},
	{1, 3, 5, 7,-1},
	{2, 4, 8,-1,-1},
	{3, 7,-1,-1,-1},
	{4, 6, 8,-1,-1},
	{5, 7,-1,-1,-1}
};

/* キュー */
static	char	main_state[MAX_STATE + 1][FIELD_SIZE];			/* +1 はワーク領域 */
static	int		prev_state[MAX_STATE];

static	int		i_log_cnt;

/* 同一局面チェックテーブル */
static	char	check_table[MAX_STATE * 2];


/**
 *	@brief		解を表示
 */
static	void	printState(char (*p_State)[FIELD_WIDTH])
{
	unsigned int	uii,
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
 *	@brief		search space
 */
int		search_space(char* pac_items, int size)
{
	int		ii;

	for(ii = 0; ii < size; ii++) {
//		printf("item[%d] is %d\n", ii, pac_items[ii]);

		if(pac_items[ii] == 0) {
//			printf("0 pos is %d\n", ii);
			break;
		}
	}

	return	ii;
}

/**
 *	@brief		print answer
 */
void	print_answer(int in)
{
	int		ii,
			ij;

	if(in != 0) {
		print_answer(prev_state[in]);
	}

	for(ii = 0; ii < FIELD_HEIGHT; ii++) {
		for(ij = 0; ij < FIELD_WIDTH; ij++) {
			printf("%d ", main_state[in][ii * FIELD_WIDTH + ij]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 *	@brief		log answer
 */
void	log_answer(int in, char* p_0pos)
{
	if(in != 0) {
//		printf("in : %d\n", in);
		log_answer(prev_state[in], p_0pos);
	}

	p_0pos[i_log_cnt++]	= search_space(main_state[in], FIELD_SIZE);
}

/**
 *	@brief		get space position to move direction
 */
char	get_move_direction(char prev, char next)
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
 *	@brief		change number
 */
int change_number(const char *board)
{
	char	work[FIELD_SIZE];
	int		ij,
			ik,
			value = 0;

	memcpy(work, board, FIELD_SIZE);

	for(ij = 0; ij < FIELD_SIZE - 1; ij++) {
		if(work[ij] == '=') {
			work[ij]	= ij + 1;
		}
	}

	for(ij = 0; ij < FIELD_SIZE - 1; ij++) {
		value += ac_fact_table[ij] * work[ij];

		for(ik = ij + 1; ik < FIELD_SIZE; ik++) {
			if(work[ij] < work[ik]) {
				work[ik]--;
			}
		}
	}

	return value;
}

/**
 *	@brief		search function
 *	@param[in]	init_state		初期状態
 */
void	search3x3(char* p_init_state, char* p_move_log)
{
	char	space_position[MAX_STATE],
			space_pos_log[MAX_MOVE];

	int		front	= 0,
			rear	= 1;
	int		var;

	printState((char(*)[FIELD_WIDTH])p_init_state);

	/* 初期化 */
	memset(check_table, 0, MAX_STATE * 2);		/* initialize 0 */
	memcpy(main_state[0], p_init_state, FIELD_SIZE);

	memset(space_pos_log, 0, sizeof(space_pos_log));
	i_log_cnt			= 0;

	/* 0 の探索 */
	space_position[0]	= search_space(p_init_state, FIELD_SIZE);

	prev_state[0]		= -1;

	var	= change_number(p_init_state);
//	printf("init: 0x%08X\n", var);
	check_table[var]	= TRUE;

	var	= change_number(ac_final_state);
//	printf("goal: 0x%08X\n", var);
	check_table[var]	= GOAL;

	/* キューにデータがある間繰り返す */
	while(front < rear) {
		int		is	= space_position[front];
		int		ii,
				ik,
				in;

		for(ii = 0; (in = adjacent[is][ii]) != -1; ii++) {
			if(main_state[front][in] == '=') {
				continue;
			}

			/* 状態をコピー */
			memcpy(main_state[rear], main_state[front], FIELD_SIZE);

			/* 移動 */
			main_state[rear][is]	= main_state[rear][in];
			main_state[rear][in]	= 0;
			space_position[rear]	= in;
			prev_state[rear]		= front;
			ik						= change_number(main_state[rear]);

			if(check_table[ik] == GOAL) {
				int		it;

				/* 発見 */
//				print_answer(rear);
//				printf("状態数 %d 個\n", rear);
				log_answer(rear, space_pos_log);

				printf("space_pos_log : ");
				for(it = 1; it < i_log_cnt; it++) {
					printf("%d", space_pos_log[it]);
					p_move_log[it - 1]	= get_move_direction(space_pos_log[it - 1],
															 space_pos_log[it]);
				}
				printf("\n");
				printf("moved log : %s\n", p_move_log);

				return;
			}
			else if(!check_table[ik]) {
				/* キューに登録 */
				check_table[ik]		= TRUE;
				rear++;
			}
		}
		front++;
	}
//	p_move_log[0]	= '?';
}
