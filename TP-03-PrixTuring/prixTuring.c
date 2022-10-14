/**
 Compilation
 gcc --std=c99 -W -Wall -o prixTuring prixTuring.c

 Exécution
 ./prixTuring < turingWinners.txt > out.txt

 Tests
 diff out.txt turingWinners.txt

 Détection de fuites mémoires
 valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --show-reachable=no ./prixTuring < turingWinners.txt > out.txt
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct tagTURING_WINNERS
{
	uint16_t Year;

	char *Name;

	char *TheseDesc;

} TURING_WINNERS;

typedef struct tagTWList
{
	TURING_WINNERS *pTW;

	unsigned int nbWinners;
} TWLIST;


/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
	int maxLineSize = 255;
	char c, *line = calloc(maxLineSize + 1,sizeof(char));

	scanf("%250[^\n]", line);

	if ( (c = getchar()) != '\n') {
		/* we did not get all the line */
		line[250] = '[';
		line[251] = line[252] = line[253] = '.';
		line[254] = ']';
		// line[255] = '\0'; // useless because already initialized by calloc

		// let's skip all chars untli the end of line
		while (( (c = getchar()) != '\n') && c != EOF) ;
	}

	return line;
}

/* This function scans a line of text (until \n), converts it as an integer and returns this integer */
int scanLineAsInt() {
	int buf;
	scanf("%i\n",&buf);
	return buf;
}

void TWL_ReadAWinnerFromFile(TURING_WINNERS *pTw)
{
	pTw->Year = scanLineAsInt();
	pTw->Name = scanLine();
	pTw->TheseDesc = scanLine();
}

void TWL_ReadWinnersFromFile(TWLIST *pTWL)
{
	int i = 0;

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		TWL_ReadAWinnerFromFile(pTWL->pTW + i);
	}
}

void TWL_PrintfAWinner(TURING_WINNERS *pTW)
{
	fprintf(stdout, "%d\n", pTW->Year);
	fprintf(stdout, "%s\n", pTW->Name);
	fprintf(stdout, "%s\n", pTW->TheseDesc);
}

void TWL_PrintWinners(TWLIST *pTWL)
{
	int i = 0;

	printf("%i\n", pTWL->nbWinners);

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		TWL_PrintfAWinner(pTWL->pTW + i);
	}
}

void TWL_FillTableWithWinners(TWLIST *pTWL)
{
	int i = 0;

	pTWL->nbWinners = scanLineAsInt();

	pTWL->pTW = malloc(pTWL->nbWinners * sizeof(TURING_WINNERS));

	TWL_ReadWinnersFromFile(pTWL);
}

void TWL_YearInfos(uint16_t Year, TWLIST *pTWL)
{
	TURING_WINNERS TW = { 0 };
	int i = 0;

	while (i < pTWL->nbWinners)
	{
		if (Year == (pTWL->pTW + i)->Year)
		{
			memcpy(&TW, pTWL->pTW + i, sizeof(TURING_WINNERS));
			break;
		}
		i++;
	}

	fprintf(stdout, "L'année %d, le(s) gagnant(s) ont été : %s\nNature des travaux : %s", TW.Year, TW.Name, TW.TheseDesc);

}

void TWL_CloseTWL(TWLIST *pTWL)
{
	int i = 0;

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		free((pTWL->pTW + i)->Name);
		free((pTWL->pTW + i)->TheseDesc);
	}

	free(pTWL->pTW);
}

int main(int argc, char **argv)
{
	int year = 0;

	TWLIST TWL = {0};

	TWL_FillTableWithWinners(&TWL);

	if (argc == 1)
	{
		TWL_PrintWinners(&TWL);
	}
	
	if (argc == 2)
	{
		year = atoi(argv[1]);
		TWL_YearInfos((uint16_t)year, &TWL);
	}

	TWL_CloseTWL(&TWL);

	return EXIT_SUCCESS;
}
