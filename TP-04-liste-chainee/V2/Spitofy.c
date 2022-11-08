#include "linkedListOfMusic.h"

int main(void)
{
    Music music = { 0 };
    Liste playlist = {0};

    lireFichierCSV("music.csv", playlist);

    detruire_i(playlist);

    return 0;
}