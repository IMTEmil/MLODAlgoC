#include <stdio.h>
#include <stdlib.h>

/// auteur : Emil Pérouse

typedef struct tableau 
{
    unsigned int taille;
    unsigned int index;
    int *valeurs;
} tableau;

void ajouterValeur(tableau *t1, int valeur)
{
    if (t1->index < t1->taille)
    {
        *(t1->valeurs + t1->index) = valeur;
        t1->index++;
    }
}

void afficherTableau(tableau *t)
{
    unsigned int i = 0;

    for (i = 0; i < t->taille; i++)
    {
        printf("%d\t", *(t->valeurs+i));
    }
    printf("\n");
}

tableau repeat(tableau *t1, tableau *t2)
{   
    tableau tResultat = {0};

    unsigned int i = 0;
    int j = 0;
    unsigned int tailleFinale = 0;

    while (i < t1->taille)
    {
        tailleFinale += *(t1->valeurs + i);
        i++;
    }

    tResultat.taille = tailleFinale;
    tResultat.valeurs = (int *) malloc(tResultat.taille * sizeof(int));

    for (i = 0; i < t2->taille; i++)
    {
        for (j = 0; j < *(t1->valeurs + i); j++)
        {
            ajouterValeur(&tResultat, *(t2->valeurs + i));
        }
    }

    return tResultat;
}

int main(void)
{
    tableau t1 = {0};
    tableau t2 = {0};
    tableau t3 = {0};

    t1.taille = 3;
    t1.valeurs = (int *) malloc(t1.taille * sizeof(int));

    ajouterValeur(&t1, 1);
    ajouterValeur(&t1, 2);
    ajouterValeur(&t1, 4);

    t2.taille = 3;
    t2.valeurs = (int*) malloc(t2.taille * sizeof(int));

    ajouterValeur(&t2, 10);

    ajouterValeur(&t2, 3);

    ajouterValeur(&t2, 8);

    t3 = repeat(&t1, &t2);

    afficherTableau(&t3);

    free(t3.valeurs);

    return 0;
}