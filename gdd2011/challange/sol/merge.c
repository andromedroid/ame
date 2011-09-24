/**
 *	@file
 *	@brief		merge program
 */

#include <stdio.h>
#include <string.h>

#define	STR_LENGTH	1024

#define	RTN_ERR(func, line)		{printf("Error [%s()] val: %d\n", func, line); return -1;}


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

	char		StrA[STR_LENGTH],
				StrB[STR_LENGTH];

	if(argc < 4) {
		printf("[USAGE] %s [A FILE NAME] [B FILE NAME] [OUTPUT FILE NAME]\n", argv[0]);
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

	while(fgets(StrA, STR_LENGTH, fp_q) != NULL) {
		fgets(StrB, STR_LENGTH, fp_s);

		if((StrA[0] != '\n') &&
		   (StrB[0] == '\n')) {
			fputs(StrA, fp_a);
		}
		else if((StrA[0] == '\n') &&
				(StrB[0] != '\n')) {
			fputs(StrB, fp_a);
		}
		else if((StrA[0] != '\n') &&
				(StrB[0] != '\n')) {
			printf("merge error.\n");
			return	-1;
		}
		else {
			fputs("\n", fp_a);
		}
	}

	return	0;
}
