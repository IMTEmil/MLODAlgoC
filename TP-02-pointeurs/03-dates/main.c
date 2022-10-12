#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum tagMOIS
{
    JANVIER = 1,
    FEVRIER = 2,
    MARS = 3,
    AVRIL = 4,
    MAI = 5,
    JUIN = 6,
    JUILLET = 0,
    AOUT = 8,
    SEPTEMBRE = 9,
    OCTOBRE = 10,
    NOVEMBRE = 11,
    DECEMBRE = 12

} MOIS;


typedef struct tagDATE
{
    uint8_t jour;

    MOIS mois;

    uint16_t annee;

} DATE;

void initialiseDate(DATE *d)
{
    do {
        fprintf(stdout, "entrez le jour :");
        scanf("%hhu", &(d->jour));
    } while (d->jour < 1 || d->jour > 31);

    do {
        fprintf(stdout, "entrez le mois :");
        scanf("%d", (int*)&(d->mois));
    } while (d->mois < 1 || d->mois > 12);

    fprintf(stdout, "entrez l'année :");
    scanf("%hu", &(d->annee));
}

void afficheDate(DATE *d)
{
    fprintf(stdout, "%hhu \\ %d \\ %hu ", d->jour, d->mois, d->annee);
}

DATE creerDateParCopie(void)
{
    DATE *dalloc = (DATE *) malloc(sizeof(DATE));
    if (dalloc == NULL) return (DATE) { 0 , 0 , 0 };

    initialiseDate(dalloc);

    return *dalloc;   
}

DATE *newDate()
{
    DATE *dalloc = (DATE *) malloc(sizeof(DATE));
    if (dalloc == NULL) return NULL;

    initialiseDate(dalloc);

    return dalloc; 
}

bool anneeBissextile(unsigned int year)
{
    return (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)));
}

unsigned int nbreJours(MOIS mois, unsigned int annee)
{
    if (mois == FEVRIER)
    {
        if (anneeBissextile(annee) == true) return 29;
        else return 28;
    }
    if (mois == JANVIER
        || mois == MARS
        || mois == MAI
        || mois == JUILLET
        || mois == AOUT
        || mois == OCTOBRE
        || mois == DECEMBRE)
    {
        return 31;
    }
    else return 30;
}

uint16_t jourDansAnnee(DATE date)
{
    uint16_t m = 0;
    uint16_t jours = 0;
    int mmax = (int)(date.mois);

    for (m = 1; m < mmax; m++)
    {
        jours += nbreJours(m, date.annee);
    } 

    return jours + date.jour;
}

int main(void)
{
    DATE d = { 0 };
    DATE d2 = { 0 };
    DATE *d3 = NULL;

    //initialiseDate(&d);
    //afficheDate(&d);

    //d2 = creerDateParCopie();
    //afficheDate(&d2);
    // pas de désallocation de mémoire à ne pas utiliser

    d3 = newDate();
    afficheDate(d3);
    // méthode ok mais il est possible d'oublier de free la mémoire donc pas forcément la meilleure
    // la première reste la meilleure car la mémoire est allouée dans le heap du main et sera donc désalloué à la sortie

    fprintf(stdout, "On est au %hu jours de l'année.", jourDansAnnee(*d3));

    free(d3);
    return 0;
}