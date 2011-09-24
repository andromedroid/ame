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
#define	FORWARD			1
#define	BACKWARD		2

#define	FIELD_WIDTH		3
#define	FIELD_HEIGHT	3
#define	FIELD_SIZE		(FIELD_WIDTH * FIELD_HEIGHT)

#define	SAVE_MEM_DIV	1
/* 状態数 (9! / 2) */
#define	MAX_STATE		(181440 / SAVE_MEM_DIV)

#define	MAX_MOVE		(32 * SAVE_MEM_DIV)

static	const	char	ac_final_state[FIELD_SIZE] = {
	1, 2, 3, 4, 5, 6, 7, 8, 0
};

static	const	int		ac_fact_table[FIELD_SIZE] = {
	40320, 5040, 720, 120, 24, 6, 2, 1, 0,
};

/* 3 x 3 隣接リスト */
static	const	char	ac_adjacent[FIELD_SIZE][5] = {
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


/**
 *	@brief		search space
 */
static	int		search_space(char* pac_items, int size)
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
 *	@brief		盤面を表示
 */
static	void	print_state_arg(int in, char (*p_state)[FIELD_WIDTH])
{
	int		ii;

	for(ii = 0; ii < FIELD_SIZE; ii++) {
		if((ii != 0) &&
		   ((ii % FIELD_WIDTH) == 0)) {
			printf("\n");
		}
		printf("%d ", p_state[in][ii]);
	}

	printf("\n\n");
}

/**
 *	@brief		解を表示
 */
static	void	print_state(int in)
{
	int		ii;

	for(ii = 0; ii < FIELD_SIZE; ii++) {
		printf("%d", main_state[in][ii]);
	}
	printf("\n");
}

/**
 *	@brief		log answer
 */
static	void	log_state(int in, char* p_0pos)
{
	p_0pos[i_log_cnt++]	= search_space(main_state[in], FIELD_SIZE);
}

/**
 *	@brief		start から検索の解を表示
 */
static	void	print_answer_forward(int in, char* p_0pos)
{
	if(in > 1) {
		print_answer_forward(prev_state[in], p_0pos);
	}
//	print_state(in);
	log_state(in, p_0pos);
}

/**
 *	@brief		goal から検索の解を表示
 */
static	void	print_answer_backward(int in, char* p_0pos)
{
	do {
		in = prev_state[in];
//		print_state(in);
		log_state(in, p_0pos);
	} while(prev_state[in] != -1);
}

/**
 *	@brief		print answer
 */
static	void	print_answer(	int		pos1,
								int		num1,
								int		num2,
								int*	p_number_table,
								char*	p_check_table,
								char*	p_0pos)
{
	/* num2 の位置を見つける */
	int		pos2 = pos1 - 1;

	while(num2 != p_number_table[pos2]) {
		pos2--;
	}

	if(p_check_table[num1] == FORWARD) {
		print_answer_forward(pos1, p_0pos);
		print_answer_backward(pos2, p_0pos);
	}
	else {
		print_answer_forward(pos2, p_0pos);
		print_answer_backward(pos1, p_0pos);
	}
}

/**
 *	@brief		get space position to move direction
 */
static	char	get_move_direction(char prev, char next)
{
	char	move_num	= next - prev;

	if(move_num == -1) {
		return	'L';
	}
	else if(move_num == 1) {
		return	'R';
	}
	else if(move_num == -FIELD_WIDTH) {
		return	'U';
	}
	else if(move_num == FIELD_WIDTH) {
		return	'D';
	}

	printf("[%s] prev : %2d, next : %2d\n", __FUNCTION__, prev, next);

	return	'?';
}

/**
 *	@brief		change number
 */
static	int change_number(const char *board)
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

	return (value / SAVE_MEM_DIV);
}

/* キューの初期化 */
static	void	init_queue(	char*	p_init_state,
							int*	p_number_table,
							char*	p_check_table,
							char*	p_space_postion)
{
	int		num;

	/* スタート */
	memcpy(main_state[0], p_init_state, FIELD_SIZE);
	p_space_postion[0]	= search_space(p_init_state, FIELD_SIZE);
	prev_state[0]		= -1;
	num					= change_number(p_init_state);
	p_number_table[0]	= num;
	p_check_table[num]	= FORWARD;

	/* ゴール */
	memcpy(main_state[1], ac_final_state, FIELD_SIZE);
	p_space_postion[1]	= FIELD_SIZE - 1;
	prev_state[1]		= -1;
	num					= change_number(ac_final_state);
	p_number_table[1]	= num;
	p_check_table[num]	= BACKWARD;
}

/**
 *	@brief		search function
 *	@param[in]	init_state		初期状態
 */
void	search3x3(char* p_init_state, char* p_move_log)
{
	int		number_table[MAX_STATE];
	char	check_table[MAX_STATE * 2];		/* 同一局面チェックテーブル */

	char	space_postion[MAX_STATE],
			space_pos_log[MAX_MOVE];

	int		front	= 0,
			rear	= 2;		/* main_state[1] まで初期化したため、rear の初期値は 2。 */

	/* 初期化 */
	memset(check_table, 0, sizeof(check_table));		/* initialize 0 */
	init_queue(p_init_state, number_table, check_table, space_postion);

	memset(space_pos_log, 0, sizeof(space_pos_log));
	i_log_cnt			= 0;

	/* キューにデータがある間繰り返す */
	while(front < rear) {
		int		is		= space_postion[front];
		int		num1	= number_table[front],
				num2;
		int		ii,
				in;
		int		var = 0;

		for(ii = 0; (in = ac_adjacent[is][ii]) != -1; ii++) {
			if(main_state[front][in] == '=') {
//				var	= in;
				continue;
			}

			if(var == in) {
				print_state_arg(front, main_state);
				printf("var: %d\n", var);
				printf("is: %d\n", in);
				printf("ii: %d\n", in);
				printf("in: %d\n", in);
				printf("tonari: %d\n", main_state[front][in]);
				printf("ERR.");
				getchar();
				return;
			}

			/* 状態をコピー */
			memcpy(main_state[rear], main_state[front], FIELD_SIZE);

			/* 移動 */
			main_state[rear][is]	= main_state[rear][in];
			main_state[rear][in]	= 0;
			space_postion[rear]		= in;
			prev_state[rear]		= front;
			num2					= change_number(main_state[rear]);

			if(!check_table[num2]) {
				/* 登録 */
				number_table[rear]	= num2;
				check_table[num2]	= check_table[num1];
				rear++;
			}
			else if(check_table[num1] != check_table[num2]) {
				int		it;

				/* 解が見つかった */
				print_answer(rear, num1, num2, number_table, check_table, space_pos_log);
//				printf("状態数 %d 個\n", rear);

				printf("space_pos_log : ");
				for(it = 1; it < i_log_cnt; it++) {
					printf("%d", space_pos_log[it]);
					p_move_log[it - 1]	= get_move_direction(space_pos_log[it - 1],
															 space_pos_log[it]);
				}
				printf("\n");
				printf("moved log : %s\n\n", p_move_log);

				return;
			}
		}
		front++;
	}
}
