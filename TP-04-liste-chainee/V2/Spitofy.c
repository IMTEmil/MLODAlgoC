#include "linkedListOfMusic.h"

int main(void)
{
    Liste playlist = NULL;
    Liste playlist2 = NULL;
    Liste playlist3 = NULL;

    lireFichierCSV("music.csv", &playlist);

    SortByYear(playlist, 2702);

    afficheListe_r(playlist);

    detruire_i(playlist);

    return 0;
}

// Spitofy 2.0
/*
int main(void)
{
    Liste playlist = playlistFromCSVFile("music.csv");
}
*/