#include "linkedListOfMusic.h"

int creerMusic(Music *music)
{

}

int OpenReadFile(FILE **file, char *FileName)
{
    *file = fopen(FileName, "r");
    if (*file == NULL)
    {
        fprintf(stderr, "Error opening %s file.", FileName);
        return -1;
    }
    return 0;
}

int ReadLineFile(FILE *file, char *Line)
{
    int i = 0;
    char c = fgetc(file);

    while (c != '\n' && c != EOF)
    {
        if (Line != NULL) *(Line + i) = c;
        i++;
        c = fgetc(file);
    }

    if (c == EOF) return -1;
    return 0;
}

int getNextString(char * Line, char **string, char *delim)
{  
    char *s = NULL;

    s = strtok(Line, delim);
    if (s == NULL) return -1;
    *string = strdup(s);

    return 0;
}

int getNextInt(char *Line, int *i, char *delim)
{   
    char *string = NULL;

    string = strtok(Line, delim);
    if (string == NULL) return -1;
    *i = atoi(string);

    return 0;
}

int LineToMusic(FILE *file, Music **music)
{
    char Line[512] = {0}; // max line size 512 bytes 
    unsigned int memorySize = 0;
    char delim[2] = ",";
    *music = (Music *) malloc(sizeof(Music));
    __uint8_t out = 0;

    if (ReadLineFile(file, Line) == -1) out = 1; 

    if (getNextString(Line, &(*music)->Name, delim) != 0) return -1;
    if (getNextString(NULL, &(*music)->Artist, delim) != 0) return -1;
    if (getNextString(NULL, &(*music)->Album, delim) != 0) return -1;
    if (getNextString(NULL, &(*music)->Genre, delim) != 0) return -1;
    if (getNextInt(NULL, &(*music)->DiscNumber, delim) != 0) return -1;
    if (getNextInt(NULL, &(*music)->TrackNumber, delim) != 0) return -1;
    if (getNextInt(NULL, &(*music)->Year, delim) != 0) return -1;

    return out;
}

void lireFichierCSV(char * cheminFichier, Liste playlist)
{
    FILE *CSVfile = NULL;
    Music *music = NULL;

    if (OpenReadFile(&CSVfile, cheminFichier) == 0)
    {
        ReadLineFile(CSVfile, NULL); //lit la première ligne sans information

        while (LineToMusic(CSVfile, &music) == 0)
        {
            if (playlist == NULL) playlist = creer(music);
            else ajoutFin_i(music ,playlist);
            music = NULL;
        }
    }
}

void afficheElement(Element e)
{
    Music *music = e;

    fprintf(stdout, "Name: %s\n", music->Name);

    fprintf(stdout, "Artist: %s\n", music->Artist);
    
    fprintf(stdout, "Album: %s\n", music->Album);

    fprintf(stdout, "Genre: %s\n", music->Genre);

    fprintf(stdout, "Disc number: %d\n", (music->DiscNumber));

    fprintf(stdout, "Track number: %d\n", (music->TrackNumber));

    fprintf(stdout, "Year: %d\n", (music->Year));
}

void detruireElement(Element e)
{

}

bool equalsElement(Element e1, Element e2)
{
    return !memcmp(e1, e2, sizeof(Music));
}