#include "linkedListOfMusic.h"

int main(void)
{
    Liste playlist = NULL;

    lireFichierCSV("music.csv", &playlist);

    afficheListe_r(playlist);

    detruire_i(playlist);

    return 0;
}