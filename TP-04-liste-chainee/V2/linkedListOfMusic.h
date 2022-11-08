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

#endif /*_LINKED_LIST_OF_MUSIC_H*/