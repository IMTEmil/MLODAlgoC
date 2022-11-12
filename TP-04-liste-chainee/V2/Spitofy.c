#include "linkedListOfMusic.h"

int main(int argc, char **argv) 
{
    Liste playlist = NULL;

    if (argc > 1)
    {
        lireFichierCSV(argv[1], &playlist);
    }

    if (argc == 3 && (strcmp(argv[2], "-sort") == 0))
    {
        mergeSort(&playlist);
    }

    if (playlist != NULL)
    {
        afficheListe_r(playlist);

        detruire_i(playlist);
    }

    return 0;
}

// Spitofy 2.0
/*
int main(void)
{
    Liste playlist = playlistFromCSVFile("music.csv");
}
*/