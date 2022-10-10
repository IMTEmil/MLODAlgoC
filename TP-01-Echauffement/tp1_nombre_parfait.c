#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

unsigned int DiviseursDeN(unsigned int N, unsigned int *ListeDiviseurs, unsigned int *nDiviseurs)
{
    unsigned int i = 1;
    unsigned int IndexListe = 0;

    for (i = 1; i < N; i++)
    {
        if ((N % i) == 0)
        {
            *(ListeDiviseurs + IndexListe) = i;
            IndexListe++;
        }
    }

    *nDiviseurs = IndexListe;

    return 0;
}

bool NombreParfait(unsigned int N)
{
    unsigned int ListeDiviseurs[1024];
    unsigned int nDiviseurs = 0;
    unsigned int i = 0;
    unsigned int Somme = 0;

    DiviseursDeN(N, ListeDiviseurs, &nDiviseurs);

    for (i = 0; i < nDiviseurs; i++)
    {
        Somme += ListeDiviseurs[i];
    }

    return (Somme == N);
}

void ListeNombreParfaits(unsigned int N, unsigned int *ValeursParfaites, unsigned int *nValeursParfaites)
{
    unsigned int i = 1;
    unsigned int IndexValeursParfaites = 0;
    
    for (i = 1; i < N; i++)
    {
        if (NombreParfait(i) != 0)
        {
            ValeursParfaites[IndexValeursParfaites] = i;
            IndexValeursParfaites++;
        }
    }

    *nValeursParfaites = IndexValeursParfaites;
}

void AfficherListeEntier(unsigned int *Liste, unsigned int TailleListe)
{
    unsigned int i = 0;

    fprintf(stdout, "Il y a %d nombre(s) parfait(s) : \n", TailleListe);

    for (i = 0; i < TailleListe; i++)
    {
        fprintf(stdout, "%d \n", Liste[i]);
    }
}

int main(int argc, char **argv)
{
    int N = 0;
    unsigned int ValeursParfaites[1024];
    unsigned int nValeursParfaites = 0;

    if (argc > 1)
    {
        N = atoi(argv[1]);
    }

    ListeNombreParfaits(N, ValeursParfaites, &nValeursParfaites);
    AfficherListeEntier(ValeursParfaites, nValeursParfaites); 

    return 0;
}