#ifndef _LINKED_LIST_OF_MUSIC_H
#define _LINKED_LIST_OF_MUSIC_H

#include "linkedList.h"
#include <stdio.h>

typedef struct Music
{
    char *Name;
    char *Artist;
    char *Album;
    char *Genre;
    char *DiscNumber;
    char *TrackNumber;
    char *Year;
} Music;

void lireFichierCSV(char * cheminFichier, Liste *playlist);
void SortByYear(Liste playlist, unsigned int nbLigns);

// Spitofy 2.0
//Liste playlistFromCSVFile(char *fileName);

#endif /*_LINKED_LIST_OF_MUSIC_H*/