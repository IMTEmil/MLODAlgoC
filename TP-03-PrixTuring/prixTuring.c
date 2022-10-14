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

#define MAX_NAME_SIZE 256
#define MAX_DESC_SIZE 1024
#define MAX_TURING_WINNERS 50
#define STARTING_YEAR 1968

typedef struct tagTURING_WINNERS
{
	uint16_t Year;

	char Name[MAX_NAME_SIZE];

	char TheseDesc[MAX_DESC_SIZE];

} TURING_WINNERS;

typedef struct tagTWList
{
	TURING_WINNERS *pTW;

	unsigned int nbWinners;
} TWLIST;

TWLIST g_TWL = {0};

/* This function scans a line of text (until \n) and returns a char* that contains all characters on the line (up to 255) excluding \n.
It also ensures the \0 termination.
**WARNING**: The result of this function has been allocated (calloc) by the function */
char* scanLine()
{
	int maxLineSize = 255;
	char c, *line = calloc(maxLineSize+1,sizeof(char));

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

void readAWinner(TURING_WINNERS *pTw)
{
	pTw->Year = scanLineAsInt();
	memcpy(pTw->Name, scanLine(), MAX_NAME_SIZE);
	memcpy(pTw->TheseDesc, scanLine(), MAX_DESC_SIZE);
}

void readWinners(TWLIST *pTWL)
{
	int i = 0;

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		readAWinner(pTWL->pTW + i);
	}
}

void TWprintf(TURING_WINNERS *pTW)
{
	fprintf(stdout, "%d\n", pTW->Year);
	fprintf(stdout, "%s\n", pTW->Name);
	fprintf(stdout, "%s\n", pTW->TheseDesc);
}

void printWinners(TWLIST *pTWL)
{
	int i = 0;

	printf("%i\n", g_TWL.nbWinners);

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		TWprintf(pTWL->pTW + i);
	}
}

void TWL_PrintTable(void)
{
	printWinners(&g_TWL);
}

void TWL_FillTable(void)
{
	int i = 0;

	g_TWL.nbWinners = scanLineAsInt();

	g_TWL.pTW = malloc(g_TWL.nbWinners * sizeof(TURING_WINNERS));

	readWinners(&g_TWL);
}

void infoAnnee(uint16_t Year)
{
	TURING_WINNERS TW = { 0 };

	if (Year == 1972) 
	{
		fprintf(stdout, "Pas de prix nobel pour 1972 dans nos données.");
	}
	else 
	{
		memcpy(&TW, g_TWL.pTW + (Year - STARTING_YEAR), sizeof(TURING_WINNERS));
		fprintf(stdout, "L'année %d, le(s) gagnant(s) ont été : %s\nNature des travaux : %s\n", TW.Year, TW.Name, TW.TheseDesc);
	}
}

int main(int argc, char **argv)
{
	TWL_FillTable();

	if (argc == 1)
	{
		TWL_PrintTable();
	}
	
	if (argc == 2)
	{
		infoAnnee(1989);
	}

	free(g_TWL.pTW);

	return EXIT_SUCCESS;
}
