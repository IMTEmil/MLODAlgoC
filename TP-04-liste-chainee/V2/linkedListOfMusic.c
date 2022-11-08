#include "linkedListOfMusic.h"

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

int readUntilDelim(FILE *file, char delim, char* Line)
{
    int i = 0;
    char c = fgetc(file);

    while (c != delim && c != EOF)
    {
        if (Line != NULL) *(Line + i) = c;
        i++;
        c = fgetc(file);
    }

    Line[i]='\0';

    if (c == EOF) 
        return -1;
    return 0;
}

int readAndAddTo(FILE *file, char delim, char **string)
{
    char s[256] = {0};
    __uint8_t out = 0;

    if (readUntilDelim(file, delim, s) == 0) {
        if (strlen(s) != 0)
        {
            *string = malloc(strlen(s) * sizeof(char));
            if (*string == NULL) return -1;
            memcpy(*string, s, strlen(s) * sizeof(char));
        } 
        else    
            *string = NULL;
    } else return -1;

    return 0;
}

int LineToMusic(FILE *file, Music **music)
{
    char delim = ',';
    char s[256] = { 0 };

    *music = (Music *) malloc(sizeof(Music));
    
    if (readAndAddTo(file, delim, &(*music)->Name) == -1) return 1;
    readAndAddTo(file, delim, &(*music)->Artist);
    readAndAddTo(file, delim, &(*music)->Album);
    readAndAddTo(file, delim, &(*music)->Genre);
    readAndAddTo(file, delim, &(*music)->DiscNumber);
    readAndAddTo(file, delim, &(*music)->TrackNumber);
    readAndAddTo(file,'\n', &(*music)->Year);

    return 0;
}

void lireFichierCSV(char * cheminFichier, Liste *playlist)
{
    FILE *CSVfile = NULL;
    Music *music = NULL;

    if (OpenReadFile(&CSVfile, cheminFichier) == 0)
    {
        ReadLineFile(CSVfile, NULL); //lit la première ligne sans information

        while (LineToMusic(CSVfile, &music) == 0)
        {
            if (*playlist == NULL) 
                *playlist = creer(music);
            else ajoutFin_i(music ,*playlist);
            music = NULL;
        }
    }
    
    fclose(CSVfile);
}

void afficheElement(Element e)
{
    Music *music = e;

    fprintf(stdout, "%s,", music->Name);

    fprintf(stdout, "%s,", music->Artist);
    
    fprintf(stdout, "%s,", music->Album);

    fprintf(stdout, "%s,", music->Genre);

    fprintf(stdout, "%s,", (music->DiscNumber));

    fprintf(stdout, "%s,", (music->TrackNumber));

    fprintf(stdout, "%s\n", (music->Year));
}


void notNullfree(void *p) {
    if(p!=NULL)
        free(p);
}

void detruireElement(Element e)
{
    Music *music = e;

    notNullfree(music->Name);
    music->Name = NULL;
    notNullfree(music->Artist);
    music->Artist = NULL;
    notNullfree(music->Genre);
    music->Genre = NULL;
    notNullfree(music->Album);
    music->Album = NULL;
    notNullfree(music->DiscNumber);
    music->DiscNumber = NULL;
    notNullfree(music->TrackNumber);
    music->TrackNumber = NULL;
    notNullfree(music->Year);
    music->Year = NULL;

    notNullfree(music);
    music = NULL;
}

bool equalsElement(Element e1, Element e2)
{
    return !memcmp(e1, e2, sizeof(Music));
}