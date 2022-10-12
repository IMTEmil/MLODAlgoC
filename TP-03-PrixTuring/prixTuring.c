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

typedef struct tagTURING_WINNERS
{
	uint16_t Year;

	char Name[MAX_NAME_SIZE];

	char TheseDesc[MAX_DESC_SIZE];

} TURING_WINNERS;

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

void readWinners(TURING_WINNERS *pTW, unsigned int nbWinners)
{
	int i = 0;

	for (i = 0; i < nbWinners; i++)
	{
		readAWinner(pTW + sizeof(TURING_WINNERS)*i);
	}
}

void printWinners(void)
{

}

int main(void)
{
	int i = 0;
	int nbGagnants = 0;

	TURING_WINNERS *ptblTW = NULL;

	nbGagnants = scanLineAsInt();
	printf("nbGagnants = %i\n",nbGagnants);

	ptblTW = (TURING_WINNERS *) calloc(nbGagnants, sizeof(TURING_WINNERS));

	readWinners(ptblTW, nbGagnants);


	return EXIT_SUCCESS;
}
