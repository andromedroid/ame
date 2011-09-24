/**
 *	@file
 *	@brief		eight.c : 「８パズル」幅優先探索
 *	@note
 *		-		I learned by http://www.geocities.jp/m_hiroi/puzzle/eight.html
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>				/* malloc(), free() */
#include <stdint.h>				/* unsigned long int */

#define	FALSE			0
#define	TRUE			1
#define	FORWARD			1
#define	BACKWARD		2

#define	ADJACENT_WIDTH	5

#define	MAX_MOVE		1024

static	const	char	ac_final_state_9[9] = {
	1, 2, 3, 4, 5, 6, 7, 8, 0
};

static	const	char	ac_final_state_12[12] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 0
};

static	const	char	ac_final_state_15[15] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 0
};
 
static	const	char	ac_final_state_16[16] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0
};

static	const	char	ac_final_state_18[18] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 0
};

static	const	char	ac_final_state_20[20] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0
};

static	const	char	ac_final_state_25[25] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0
};

/* 3 x 3 隣接リスト */
static	const	char	adjacent_3x3[9][ADJACENT_WIDTH] = {
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

/* 3 x 4 隣接リスト */
static	const	char	adjacent_3x4[12][ADJACENT_WIDTH] = {
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

/* 3 x 5 隣接リスト */
static	const	char	adjacent_3x5[15][ADJACENT_WIDTH] = {
	{ 1,  3, -1, -1, -1},
	{ 0,  2,  4, -1, -1},
	{ 1,  5, -1, -1, -1},
	{ 0,  4,  6, -1, -1},
	{ 1,  3,  5,  7, -1},
	{ 2,  4,  8, -1, -1},
	{ 3,  7,  9, -1, -1},
	{ 4,  6,  8, 10, -1},
	{ 5,  7, 11, -1, -1},
	{ 6, 10, 12, -1, -1},
	{ 7,  9, 11, 13, -1},
	{ 8, 10, 14, -1, -1},
	{ 9, 13, -1, -1, -1},
	{10, 12, 14, -1, -1},
	{11, 13, -1, -1, -1}
};

/* 4 x 3 隣接リスト */
static	const	char	adjacent_4x3[12][ADJACENT_WIDTH] = {
	{ 1,  4, -1, -1, -1},
	{ 0,  2,  5, -1, -1},
	{ 1,  3,  6, -1, -1},
	{ 2,  7, -1, -1, -1},
	{ 0,  5,  8, -1, -1},
	{ 1,  4,  6,  9, -1},
	{ 2,  5,  7, 10, -1},
	{ 3,  6, 11, -1, -1},
	{ 4,  9, -1, -1, -1},
	{ 5,  8, 10, -1, -1},
	{ 6,  9, 11, -1, -1},
	{ 7, 10, -1, -1, -1}
};

/* 4 x 4 隣接リスト */
static	const	char	adjacent_4x4[16][ADJACENT_WIDTH] = {
	{ 1,  4, -1, -1, -1},
	{ 0,  2,  5, -1, -1},
	{ 1,  3,  6, -1, -1},
	{ 2,  7, -1, -1, -1},
	{ 0,  5,  8, -1, -1},
	{ 1,  4,  6,  9, -1},
	{ 2,  5,  7, 10, -1},
	{ 3,  6, 11, -1, -1},
	{ 4,  9, 12, -1, -1},
	{ 5,  8, 10, 13, -1},
	{ 6,  9, 11, 14, -1},
	{ 7, 10, 15, -1, -1},
	{ 8, 13, -1, -1, -1},
	{ 9, 12, 14, -1, -1},
	{10, 13, 15, -1, -1},
	{11, 14, -1, -1, -1}
};

/* 5 x 3 隣接リスト */
static	const	char	adjacent_5x3[15][ADJACENT_WIDTH] = {
	{ 1,  5, -1, -1, -1},
	{ 0,  2,  6, -1, -1},
	{ 1,  3,  7, -1, -1},
	{ 2,  4,  8, -1, -1},
	{ 3,  9, -1, -1, -1},
	{ 0,  6, 10, -1, -1},
	{ 1,  5,  7, 11, -1},
	{ 2,  6,  8, 12, -1},
	{ 3,  7,  9, 13, -1},
	{ 4,  8, 14, -1, -1},
	{ 5, 11, -1, -1, -1},
	{ 6, 10, 12, -1, -1},
	{ 7, 11, 13, -1, -1},
	{ 8, 12, 14, -1, -1},
	{ 9, 13, -1, -1, -1}
};

static	int		FIELD_SIZE;

/* 状態数 (9! / 2) */
static	int		MAX_STATE;

/* キュー */
static	char	*main_state;
static	int		*prev_state;
static	int		*number_table;

/* 同一局面チェックテーブル */
static	char	*check_table;

static	int		i_log_cnt;


/**
 *	@brief		get search data
 *	@param[out]	final state array address
 *	@param[out]	adjacent array address
 *	@param[in]	width
 *	@param[in]	height
 *	@return		none
 */
void	get_search_data(const char** pac_final_state, const char** pac_adjacent, char width, char height)
{
	if(width <= 3) {
		if(height <= 3) {
			*pac_final_state	= ac_final_state_9;
			*pac_adjacent		= (char*)adjacent_3x3;
		}
		else if(height == 4) {
			*pac_final_state	= ac_final_state_12;
			*pac_adjacent		= (char*)adjacent_3x4;
		}
		else if(height == 5) {
			*pac_final_state	= ac_final_state_15;
			*pac_adjacent		= (char*)adjacent_3x5;
		}
	}
	else if(width == 4) {
		if(height <= 3) {
			*pac_final_state	= ac_final_state_12;
			*pac_adjacent		= (char*)adjacent_4x3;
		}
		else if(height == 4) {
			*pac_final_state	= ac_final_state_16;
			*pac_adjacent		= (char*)adjacent_4x4;
		}
	}
	else if(width == 5) {
		if(height <= 3) {
			*pac_final_state	= ac_final_state_15;
			*pac_adjacent		= (char*)adjacent_5x3;
		}
	}
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
 *	@brief		解を表示
 */
void	print_state(int in)
{
	int		ii;

	for(ii = 0; ii < FIELD_SIZE; ii++) {
		printf("%d", *(main_state + (in * FIELD_SIZE + ii)));
	}
	printf("\n");
}

/**
 *	@brief		log answer
 */
void	log_state(int in, char* p_0pos)
{
	p_0pos[i_log_cnt++]	= search_space((main_state + (in * FIELD_SIZE)), FIELD_SIZE);
}

/**
 *	@brief		start から検索の解を表示
 */
void	print_answer_forward(int in, char* p_0pos)
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
void	print_answer_backward(int in, char* p_0pos)
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
void	print_answer(int pos1, int num1, int num2, char* p_0pos)
{
	/* num2 の位置を見つける */
	int		pos2 = pos1 - 1;

	while(num2 != number_table[pos2]) {
		pos2--;
	}

	if(check_table[num1] == FORWARD) {
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
char	get_move_direction(char prev, char next, char f_width)
{
	if((next - prev) == -1) {
		return	'L';
	}
	else if((next - prev) == 1) {
		return	'R';
	}
	else if((next - prev) == -f_width) {
		return	'U';
	}
	else if((next - prev) == f_width) {
		return	'D';
	}

	return	'?';
}

//#define	FT_SIZE		16
#define	FT_SIZE		12
/**
 *	@brief		change number
 */
unsigned long int	change_number(const char *board)
{
//	static	unsigned long int	fact_table[FT_SIZE] = {
//		130767436800, 87178291200, 6227020800, 479001600, 33916800,
//		3628800, 362880, 40320, 5040, 720, 120, 24, 6, 2, 1, 0
//	};
	static	unsigned long int	fact_table[FT_SIZE] = {
		33916800, 3628800, 362880, 40320, 5040, 720, 120, 24, 6, 2, 1, 0
	};
	unsigned long int	value = 0;

	char	work[FIELD_SIZE];
	int		ft_offset	= FT_SIZE - FIELD_SIZE,
			ij,
			ik;

	memcpy(work, board, FIELD_SIZE);

	for(ij = 0; ij < FIELD_SIZE - 1; ij++) {
		value += fact_table[ft_offset + ij] * work[ij];

		for(ik = ij + 1; ik < FIELD_SIZE; ik++) {
			if(work[ij] < work[ik]) {
				work[ik]--;
			}
		}
	}

	return value;
}

/**
 *	@brief		キューの初期化
 */
void	init_queue(char* p_init_state, const char* p_final_state, char* space_postion)
{
	unsigned long int	num;

	/* キュー */
	main_state		= (char*)malloc(sizeof(char) * (MAX_STATE + 1) * FIELD_SIZE);			/* +1 はワーク領域 */
	prev_state		= (int*)malloc(sizeof(int) * MAX_STATE);
	number_table	= (int*)malloc(sizeof(int) * MAX_STATE);

	/* 同一局面チェックテーブル */
	check_table		= (char*)malloc(sizeof(char) * MAX_STATE * 2);

	memset(check_table, 0, sizeof(check_table));		/* initialize 0 */

	/* スタート */
	memcpy((main_state + (0 * FIELD_SIZE)), p_init_state, FIELD_SIZE);
	space_postion[0]	= search_space(p_init_state, FIELD_SIZE);
	prev_state[0]		= -1;
	num					= change_number(p_init_state);
	number_table[0]		= num;
	check_table[num]	= FORWARD;

	/* ゴール */
	memcpy((main_state + (1 * FIELD_SIZE)), p_final_state, FIELD_SIZE);
	space_postion[1]	= FIELD_SIZE - 1;
	prev_state[1]		= -1;
	num					= change_number(p_final_state);
	number_table[1]		= num;
	check_table[num]	= BACKWARD;
}

/**
 *	@brief		キューの終了処理
 */
void	end_queue(void)
{
	/* キュー */
	free(main_state);
	free(prev_state);
	free(number_table);

	/* 同一局面チェックテーブル */
	free(check_table);
}

/**
 *	@brief		search function
 *	@param[in]	*p_init_state	初期状態
 *	@param[in]	p_move_log		0 の移動ログ
 *	@param[in]	f_width			フィールドの幅
 *	@param[in]	f_height		フィールドの高さ
 */
void	search(char* p_init_state, char* p_move_log, char f_width, char f_height)
{
	const char	*pac_final_state,
				*pac_adjacent;		/* 隣接リスト */

	char	space_postion[MAX_STATE],
			space_pos_log[MAX_MOVE];

	int		front	= 0,
			rear	= 2;		/* main_state[1] まで初期化したため、rear の初期値は 2。 */

	int		ii;

	/* 初期化 */
	FIELD_SIZE	= f_width * f_height;

	for(MAX_STATE = 1, ii = FIELD_SIZE; ii > 0; ii--) {		/* 階乗の計算 */
		MAX_STATE	*= ii; 
	}
	MAX_STATE >>= 1;			/* (FIELD_SIZE! / 2) */

	get_search_data(&pac_final_state, &pac_adjacent, f_width, f_height);
	printf("fs: %08X, %08X\n", (unsigned int)ac_final_state_9, (unsigned int)pac_final_state);
	init_queue(p_init_state, pac_final_state, space_postion);

	memset(space_pos_log, 0, sizeof(space_pos_log));
	i_log_cnt			= 0;

	/* キューにデータがある間繰り返す */
	while(front < rear) {
		int					is		= space_postion[front];
		unsigned long int	num1	= number_table[front],
							num2;
		int					in;

		for(ii = 0; (in = *(pac_adjacent + (is * ADJACENT_WIDTH + ii))) != -1; ii++) {
			/* 状態をコピー */
			memcpy((main_state + (rear * FIELD_SIZE)),
				   (main_state + (front * FIELD_SIZE)),
				   FIELD_SIZE);

			/* 移動 */
			*(main_state + (rear * FIELD_SIZE) + is)	= *(main_state + (rear * FIELD_SIZE) + in);
			*(main_state + (rear * FIELD_SIZE) + in)	= 0;
			space_postion[rear]		= in;
			prev_state[rear]		= front;
			num2					= change_number(main_state + (rear * FIELD_SIZE));

			printf("num1: %X, num2: %X\n", num1, num2);

			if(!check_table[num2]) {
				/* 登録 */
				number_table[rear]	= num2;
				check_table[num2]	= check_table[num1];
				rear++;
			}
			else if(check_table[num1] != check_table[num2]) {
				int		it;

				/* 解が見つかった */
//				print_answer(rear, num1, num2, space_pos_log);
				printf("状態数 %d 個\n", rear);
				printf("num1: %X, num2: %X\n", num1, num2);

				printf("space_pos_log : ");
				for(it = 1; it < i_log_cnt; it++) {
					printf("%d", space_pos_log[it]);
					p_move_log[it - 1]	= get_move_direction(space_pos_log[it - 1],
															 space_pos_log[it],
															 f_width);
				}
				printf("\n");
				printf("moved log : %s\n", p_move_log);

				end_queue();

				return;
			}
		}
		front++;
	}
	end_queue();
}
