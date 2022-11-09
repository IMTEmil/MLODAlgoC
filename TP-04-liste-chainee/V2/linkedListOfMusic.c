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
    __uint8_t out = 0;
    unsigned int slen = 0;

    if (readUntilDelim(file, delim, s) == 0) {
        slen = strlen(s);
        if (slen != 0)
        {
            *string = malloc(slen + 1);
            if (*string == NULL) return -1;
            strcpy(*string, s);
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
    Liste iterListe = NULL;
    unsigned int i = 0;
    for (i = 0; i < index; i++)
    {
        l = playlist->suiv;
        if (l == NULL) break;
    }

    return l;
}

Liste swapElement(Liste playlist, unsigned int i1, unsigned int i2)
{
    Liste subListe1 = getSubPlaylist(playlist, i1);
    Liste subListe2 = getSubPlaylist(playlist, i2);
    Music *music1 = subListe1->val;
    Music *music2 = subListe2->val;

    subListe1->val = music2;
    subListe2->val = music1;
    return playlist;
}

bool yearDelta(char *y1, char *y2)
{
    int year1 = atoi(y1);
    int year2 = atoi(y2);
    return year1 < year2;
}

void Merge(Liste playlist, int l, int m, int r)
{
	int i = 0, j = 0, k = 0;
    int n1 = m - l + 1;
    int n2 = r - m;

	Liste L = getSubPlaylist(playlist, l);

	Liste R = getSubPlaylist(playlist, m + 1);

    Liste currPlaylistL = L;

    Liste currPlaylistR = R;

    Music *valL = (Music *)L->val;

    Music *valR = (Music *)R->val;
    
    k = l;  

    while (i < n1 && j < n2)
    {
        if (yearDelta(valL->Year, valR->Year))
        {
            playlist = swapElement(playlist, k, l + i);
            i++;
        }
        else 
        {
            playlist = swapElement(playlist, k, m + 1 + j);
            j++;
        }
        L = getSubPlaylist(playlist, l + i);
        R = getSubPlaylist(playlist, j + i);
        valL = L->val;
        valR = R->val;
        k++;
    }
    /*

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
    */
}

void MergeSort(Liste playlist, int l, int r)
{
    int m = 0;

    if (l < r)
    {
        m = (l + r) / 2;

        MergeSort(playlist, l, m);

        MergeSort(playlist, m + 1, r);

        Merge(playlist, l, m, r);        
    }
}

void SortByYear(Liste playlist, unsigned int nbLigns)
{   
   	MergeSort(playlist, 0, nbLigns);
}

/*
Liste playlistFromCSVFile(char *fileName)
{

}
*/