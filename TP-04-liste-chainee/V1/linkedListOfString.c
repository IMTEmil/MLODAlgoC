#include <stdio.h>
#include "linkedList.h"

void afficheElement(Element e)
{
    printf("%s\n", (char *)e);
}

void detruireElement(Element e)
{

}

int main(void)
{
    char *c = "chaine";
    char *d = "de";
    char *e = "charactere";
    
    /*printf("main = %p\n ",main);
    printf("c = %p\n ",c);
    printf("d = %p\n ",d);
    printf("e = %p\n ",e);*/
 
    Liste p = NULL;
    Liste l = creer(d);
    //printf("l = %p\n ",l);


    l = ajoutTete(c, l);

    l = ajoutFin_i(e,l);

    afficheListe_i(l);

    p = cherche_i("chaine",l);
	if(estVide(p))
		printf("cherche_i(chaine) : [ERREUR] pas trouve \n");
	else {
		printf("cherche_i(chaine) : trouve ");
		afficheElement(p->val);
		printf("\n");
	}

    p = cherche_i("non",l);
	printf("cherche_i(non) : %s\n",estVide(p)?"pas trouve":"[ERREUR] trouve !!!");

    printf("retirePremier_i(de)   : ");
	l = retirePremier_i("de",l);
	afficheListe_r(l);
	
	printf("retirePremier_i(non)   : ");
	l = retirePremier_i("non",l);
	afficheListe_r(l);

    detruire_i(l);
    
    return 0;
}