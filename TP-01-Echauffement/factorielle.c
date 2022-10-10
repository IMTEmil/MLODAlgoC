#include <stdio.h>

#ifdef ULL_TYPE_ENTIER
    #define FORMAT_SPECIFIER "%llu"
    typedef unsigned long long TypeEntier;
    TypeEntier factorielle(TypeEntier);
#endif

#ifndef ULL_TYPE_ENTIER
    #define FORMAT_SPECIFIER "%hd"
    typedef short TypeEntier;
    TypeEntier factorielle(TypeEntier);
#endif

TypeEntier factorielle(TypeEntier entier)
{
    TypeEntier i = 1;
    TypeEntier fact = 1;

    for (i = 1; i < entier + 1; i++)
    {
        fact *= i;
    }

    return fact;
}

void AfficherFactorielles()
{
    TypeEntier i = 0;

    for (i = 1; i < 15; i++)
    {
        fprintf(stdout, "Factorielle de " FORMAT_SPECIFIER " : " FORMAT_SPECIFIER "\n", i, factorielle(i));
    }
}

int main(void)
{
    
    AfficherFactorielles((TypeEntier) 10);
    return 0;
}