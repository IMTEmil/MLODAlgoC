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
#define MAX_INT_SIZE 10 // max value 429 967 296

typedef struct tagTURING_WINNERS
{
	int Year;

	char Name[MAX_NAME_SIZE];

	char TheseDesc[MAX_DESC_SIZE];

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
	char c, *line = calloc(maxLineSize+1,sizeof(char));

	scanf("%250[^\n]", line);

	if ( (c = getchar()) != '\n') {
		// we did not get all the line 
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
/*
int scanLineAsInt() {
	int buf;
	scanf("%i\n",&buf);
	return buf;
}
*/

void TWL_OpenReadFile(FILE **file, char *FileName)
{
    *file = fopen(FileName, "r");
    if (*file == NULL)
    {
        fprintf(stderr, "Error opening %s file.", FileName);
    }
}

void TWL_OpenWriteFile(FILE **file, char *FileName)
{
    *file = fopen(FileName, "w");
    if (*file == NULL)
    {
        fprintf(stderr, "Error opening %s file.", FileName);
    }
}

int TWL_ReadLineFile(FILE *file, char *Line)
{
    int i = 0;
    char c = fgetc(file);

    while (c != '\n' && c != EOF)
    {
        *(Line + i) = c;
        i++;
        c = fgetc(file);
    }

    if (c == EOF) return -1;
    return 0;
}

int TWL_ReadLineFileAsInt(FILE *file, int *n)
{
    char szint[MAX_INT_SIZE] = {0};

    TWL_ReadLineFile(file, szint);

    *n = atoi(szint);
}

void TWL_ReadAWinner(TURING_WINNERS *pTw, FILE *file)
{
	TWL_ReadLineFileAsInt(file, &pTw->Year);
	TWL_ReadLineFile(file, pTw->Name);
	TWL_ReadLineFile(file, pTw->TheseDesc);
}

void TWL_ReadWinners(TWLIST *pTWL, FILE *file)
{
	int i = 0;

	for (i = 0; i < pTWL->nbWinners; i++)
	{
        TWL_ReadAWinner(pTWL->pTW + i, file);
	}
}

void TWprintf(TURING_WINNERS *pTW, FILE *OutputFile)
{
	fprintf(OutputFile, "%d\n", pTW->Year);
	fprintf(OutputFile, "%s\n", pTW->Name);
	fprintf(OutputFile, "%s\n", pTW->TheseDesc);
}

void printWinners(TWLIST *pTWL, FILE *OutputFile)
{
	int i = 0;

	fprintf(OutputFile, "%i\n", pTWL->nbWinners);

	for (i = 0; i < pTWL->nbWinners; i++)
	{
		TWprintf(pTWL->pTW + i, OutputFile);
	}
}

void TWL_PrintTable(TWLIST *pTWL, FILE *OutputFile)
{
	printWinners(pTWL, OutputFile);
}

void TWL_FillTable(TWLIST *pTWL, char *FileName)
{
	int i = 0;
    FILE *file = NULL;
    char nbWinners[4] = { 0 };

    TWL_OpenReadFile(&file, FileName);

	TWL_ReadLineFileAsInt(file, &pTWL->nbWinners);

	pTWL->pTW = malloc(pTWL->nbWinners * sizeof(TURING_WINNERS));

	TWL_ReadWinners(pTWL, file);
}

void infoAnnee(TWLIST *pTWL, uint16_t Year)
{
	TURING_WINNERS TW = { 0 };

	if (Year == 1972) 
	{
		fprintf(stdout, "Pas de prix nobel pour 1972 dans nos données.");
	}
	else 
	{
		memcpy(&TW, pTWL->pTW + (Year - STARTING_YEAR), sizeof(TURING_WINNERS));
		fprintf(stdout, "L'année %d, le(s) gagnant(s) ont été : %s\nNature des travaux : %s\n", TW.Year, TW.Name, TW.TheseDesc);
	}
}

void TWL_SwapTW(TURING_WINNERS *pTWL, int x, int y)
{
	TURING_WINNERS tempTW = {0};

	memcpy(&tempTW, pTWL + x, sizeof(TURING_WINNERS));

	memcpy(pTWL + x, pTWL + y, sizeof(TURING_WINNERS));

	memcpy(pTWL + y, &tempTW, sizeof(TURING_WINNERS));
}

void TWL_Merge(TWLIST *pTWL, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int i = 0, j = 0, k = 0;

	TWLIST TWL1 = {0};
	TWLIST TWL2 = {0};

	TWL1.nbWinners = n1;
	TWL2.nbWinners = n2;

	TWL1.pTW = malloc(n1 * sizeof(TURING_WINNERS));
	TWL2.pTW = malloc(n2 * sizeof(TURING_WINNERS));

	for (i = 0; i < n1; i++)
	{
		memcpy(TWL1.pTW + i, pTWL->pTW + p + i, sizeof(TURING_WINNERS));
	}

	for (i = 0; i < n2; i++)
	{
		memcpy(TWL2.pTW + i, pTWL->pTW + q + i + 1, sizeof(TURING_WINNERS));
	}

	i = 0;
	j = 0;
	k = p;

	while (i < n1 && j < n2) {
		if ((TWL1.pTW + i)->Year <= (TWL2.pTW + j)->Year) {
			memcpy(pTWL->pTW + k, TWL1.pTW + i, sizeof(TURING_WINNERS));
			i++;
		} else {
			memcpy(pTWL->pTW + k, TWL2.pTW + j, sizeof(TURING_WINNERS));
			j++;
		}
		k++;
		}

		while (i < n1) {
			memcpy(pTWL->pTW + k, TWL1.pTW + i, sizeof(TURING_WINNERS));	
			i++;
			k++;
		}
		while (j < n2) {
			memcpy(pTWL->pTW + k, TWL2.pTW + j, sizeof(TURING_WINNERS));
			j++;
			k++;
		}

		free(TWL1.pTW);
		free(TWL2.pTW);

}

void TWL_MergeSort(TWLIST *pTWL, int l, int r)
{
    int m = 0;

    if (l < r)
    {
        m = (l + r) / 2;

        TWL_MergeSort(pTWL, l, m);

        TWL_MergeSort(pTWL, m + 1, r);

        TWL_Merge(pTWL, l, m, r);        
    }
}

void TWL_SortByYear(TWLIST *pTWL)
{   
	TWL_MergeSort(pTWL, 0, pTWL->nbWinners - 1);
}

void TWL_AddNewWinner(TWLIST *pTWL)
{
	TURING_WINNERS pTW = {0};

	pTWL->nbWinners++;

	pTWL->pTW = realloc(pTWL->pTW, (pTWL->nbWinners + 1) sizeof(TURING_WINNERS));



	memcpy(pTWL->pTW + pTWL->nbWinners, pTW, sizeof(TURING_WINNERS));
}

int main(int argc, char **argv)
{
    FILE *file = NULL;

	TWLIST TWL = {0};

    if (argc == 1)
    {
        fprintf(stdout, "Ajoutez des arguments. Au moins une liste de gagnants du prix Turing.\n");
    }

    if (argc == 2)
    {
	    TWL_FillTable(&TWL, argv[1]);
        if (argc == 2) TWL_PrintTable(&TWL, stdout);
    }

	if (argc == 3)
	{
        TWL_OpenWriteFile(&file, argv[2]);
		TWL_PrintTable(&TWL, file);
	}

    if (argc == 4 || strcmp(argv[3], "sort"))
    {
	    TWL_FillTable(&TWL, argv[1]);
        TWL_SortByYear(&TWL); 
		TWL_OpenWriteFile(&file, argv[2]);
		TWL_PrintTable(&TWL, file);
    }

	free(TWL.pTW);

	return EXIT_SUCCESS;
}
