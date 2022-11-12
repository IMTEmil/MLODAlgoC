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
    char s[100] = {0};
    int out = 0;
    unsigned int slen = 0;

    out = readUntilDelim(file, delim, s);
    
    slen = strlen(s);
    if (slen != 0)
    {
        *string = malloc(slen + 1);
        if (*string == NULL) return -1;
        strcpy(*string, s);
    } 
    else *string = NULL;

    return out;
}

int LineToMusic(FILE *file, Music **music)
{
    char delim = ',';

    *music = (Music *) malloc(sizeof(Music));
    
    if (readAndAddTo(file, delim, &(*music)->Name) == -1) 
    {
        free(*music);
        return 1;
    }
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
        //ReadLineFile(CSVfile, NULL); //lit la première ligne sans information

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

void printIfNotNull(char *ptr)
{
    if (ptr != NULL)
    {
        fprintf(stdout, "%s,", ptr);
    }
    else { fprintf(stdout, ",");}
}

void afficheElement(Element e)
{
    Music *music = e;

    printIfNotNull(music->Name);

    printIfNotNull(music->Artist);
    
    printIfNotNull(music->Album);

    printIfNotNull(music->Genre);

    printIfNotNull(music->DiscNumber);

    printIfNotNull(music->TrackNumber);

    if (music->Year != NULL) fprintf(stdout, "%s\n", (music->Year));
}

void freeIfNotNull(void *p) {
    if(p!=NULL)
    {
        free(p);
        p = NULL;
    }
}

void detruireElement(Element e)
{
    Music *music = e;

    freeIfNotNull(music->Name);
    freeIfNotNull(music->Artist);
    freeIfNotNull(music->Genre);
    freeIfNotNull(music->Album);
    freeIfNotNull(music->DiscNumber);
    freeIfNotNull(music->TrackNumber);
    freeIfNotNull(music->Year);

    freeIfNotNull(music);
}

int strcmpIfNotNull(char *s1, char *s2)
{
    if (s1 != NULL && s2 != NULL)
    {
        return strcmp(s1, s2);
    }
    return 0;
}

bool equalsElement(Element e1, Element e2)
{
    Music *m1 = e1;
    Music *m2 = e2;

    if (m1 == NULL || m2 == NULL) return false;

    if (strcmpIfNotNull(m1->Album, m2->Album) != 0) return false;    

    if (strcmpIfNotNull(m1->Name, m2->Name) != 0) return false; 

    if (strcmpIfNotNull(m1->Genre, m2->Genre) != 0) return false; 

    if (strcmpIfNotNull(m1->DiscNumber, m2->DiscNumber) != 0) return false; 

    if (strcmpIfNotNull(m1->TrackNumber, m2->TrackNumber) != 0) return false; 

    if (strcmpIfNotNull(m1->Year, m2->Year) != 0) return false; 

    return true;
}

Liste getSubPlaylist(Liste playlist, unsigned int index)
{
    Liste l = playlist;
    unsigned int i = 0;
    for (i = 0; i < index; i++)
    {
        l = l->suiv;
        if (l == NULL) break;
    }

    return l;
}

// https://iq.opengenus.org/fast-and-slow-pointer-technique/
void getTwoSubPlaylist(Liste playlist, Liste *g, Liste *d)
{
    Liste fast, slow;
    slow = playlist;
    fast = playlist->suiv;

    while(fast != NULL)
    {
        fast = fast->suiv;
        if (fast != NULL)
        {
            slow = slow->suiv;
            fast = fast->suiv;
        }
    }

    *g = playlist;
    *d = slow->suiv;
    slow->suiv = NULL;
}

bool yearcmp(Element e1, Element e2)
{
    Music *m1 = e1;
    Music *m2 = e2;
    int year1 = atoi(m1->Year);
    int year2 = atoi(m2->Year);

    return year1 <= year2;
}

Liste SortedMerge(Liste g, Liste d)
{
    Liste l = NULL;

    if (g == NULL) return d;
    if (d == NULL) return g;

    if (yearcmp(g->val, d->val))
    {
        l = g;
        l->suiv = SortedMerge(g->suiv, d);
    }
    else {

        l = d;
        l->suiv = SortedMerge(g, d->suiv);
    }

    return l;
}

void mergeSort(Liste *playlist)
{
    Liste tete = *playlist;
    Liste g = NULL, d = NULL;

    if ((tete == NULL || tete->suiv == NULL))
    {
        return;
    }
    getTwoSubPlaylist(tete, &g, &d);

    mergeSort(&g);
    mergeSort(&d);

    *playlist = SortedMerge(g,d);
}