#include "liste-chainee.h"
#include <stdlib.h>
#include <stdio.h>

// retourne vrai si l est vide et faux sinon
bool estVide(Liste l) {
	return l == NULL;
}

// créer une liste d'un seul élément contenant la valeur v
Liste creer(Element v){
	Liste l = malloc(sizeof(Cellule));
	if (l!= NULL)
	{
		l->val = v;
		l->suiv = NULL;
	}
	return l;
}

// ajoute l'élément v en tete de la liste l
Liste ajoutTete(Element v, Liste l) 
{
	Liste newList = creer(v);
	if (newList != NULL)
	{
		newList->suiv = l;
	}
	return newList;
}

void afficheElement(Element e) {
	printf("%i ",e);
}

// affiche tous les éléments de la liste l
// Attention, cette fonction doit être indépendante du type des éléments de la liste
// utiliser une fonction annexe affiche_element
// Attention la liste peut être vide !
// version itérative
void afficheListe_i(Liste l) 
{
	Liste currentList = l;
	if (!(estVide(l)))
	{
		do {
			afficheElement(currentList->val);
			currentList = currentList->suiv;
		} while (currentList != NULL);
	}
}

// version recursive
void afficheListe_r(Liste l) {
	if (!(estVide(l)))
	{
		afficheElement(l->val);
		afficheListe_r(l->suiv);
	}
}

void detruireElement(Element e) 
{

}

// Détruit tous les éléments de la liste l
// version itérative
void detruire_i(Liste l) 
{
	Liste nextList = NULL;
	Liste currentList = l;

	if (!(estVide(l)))
	{
		nextList = currentList->suiv;
		do {
			free(currentList);
			detruireElement(currentList->val);
			currentList = nextList;
			nextList = currentList->suiv;
		} while (nextList != NULL);
	}
}

// version récursive
void detruire_r(Liste l) 
{
	if (!(estVide(l)))
	{
		detruire_r(l->suiv);
		detruireElement(l->val);
		free(l);
	}
}

// retourne la liste dans laquelle l'élément v a été ajouté en fin
// version itérative
Liste ajoutFin_i(Element v, Liste l) {
	Liste lastElement = l;
	Liste newList = malloc(sizeof(Cellule));
	if (newList != NULL)
	{
		do {
			lastElement = lastElement->suiv;
		} while (lastElement->suiv != NULL);
	}
	lastElement->suiv = newList;
	newList->val = v;
	newList->suiv = NULL;
	return l;
}

// version recursive
Liste ajoutFin_r(Element v, Liste l) {
	Liste newList = NULL;
	if (!estVide(l)) return NULL;
	if (!(estVide(l->suiv)))
	{
		ajoutFin_r(v, l->suiv);
		return l;
	}
	else {
		newList = creer(v);
		if (newList != NULL)
		{
			newList->suiv = NULL;
			l->suiv = newList;
		}
	}
	return l;
}

// compare deux elements
bool equalsElement(Element e1, Element e2){
	return e1 == e2;
}

// Retourne un pointeur sur l'élément de la liste l contenant la valeur v ou NULL
// version itérative
Liste cherche_i(Element v,Liste l) 
{
	Liste iterList = l;
	if (!(estVide(l)))
	{
		while (!equalsElement(iterList->val, v) && iterList->suiv != NULL)
		{
			iterList = iterList->suiv;
		}
		if (iterList->val == v) return iterList;
	}
	return NULL;
}

// version récursive
Liste cherche_r(Element v,Liste l) 
{
	if (!estVide(l))
	{
		if (equalsElement(l->val, v))return l;
		else cherche_r(v, l->suiv);
	}
	return l;
}

// Retourne la liste modifiée dans la laquelle le premier élément ayant la valeur v a été supprimé
// ne fait rien si aucun élément possède cette valeur
// version itérative
Liste retirePremier_i(Element v, Liste l) 
{
	Liste currentElement = l;
	Liste lastElement = {0};
	if (!estVide(l))
	{
		while (currentElement != NULL)
		{
			if (equalsElement(v, currentElement->val))
			{
				if (lastElement != NULL)
				{
					lastElement->suiv = currentElement->suiv;
				}
				else {
					l = currentElement->suiv;
				}
				free(currentElement);
				currentElement = NULL;
				break;
			}
			lastElement = currentElement;
			currentElement = currentElement->suiv;
		}
	}
	return l;
}

// version recursive
Liste retirePremier_r(Element v, Liste l) 
{
	Liste premierElement = {0};
	if (!estVide(l))
	{
		if (equalsElement(v, l->val))
		{
			premierElement = l;
			l = l->suiv;
			free(premierElement);
			premierElement = NULL;
		}
		else {
			l->suiv = retirePremier_r(v, l->suiv);
		}
	}	

	return l;
}


void afficheEnvers_r(Liste l) {
	if (!estVide(l->suiv))
	{
		afficheEnvers_r(l->suiv);
	}
	afficheElement(l->val);
}



