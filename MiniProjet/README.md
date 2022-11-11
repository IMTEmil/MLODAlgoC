# MiniProjet

## Description

Ce projet a été réalisé dans le cadre du cours donné par Luc Fabresse en MLOD à IMT Nord Europe en 2022/2023.

Il reprend le classique jeu snake qui a été forké depuis [raylib](https://raylib.com). J'y ai ajouté des options supplémentaires: 
Le principe est de créer des variantes du jeu classique Snake autour de jeu de mots avec le mot 'snake':
* Sénèque : le stoïcien de renom remplace la tête de serpent et instruit son joueur.
* Snare : le jeu est jonché de pièges qu'il faut éviter, ils apparaissent petit à petit et progressivement.

Le répertoire contient:
* Le code source du jeu original donné par Raylib dans snake.c
* Le module du projet avec son code source (projet.c) et le header (projet.h). 
* Un Makefile pour compiler et lancer le jeu.
* Un README.md que vous êtes en train de lire. 

Par négligence, j'ai développé le projet sur un repertoire différent de celui-ci. L'historique des commits peut y être retrouvé sur le répertoire [MiniProjet](https://github.com/IMTEmil/MiniProjet), les commits fait après le 4 novembre 2022 sont sur le répertoire courant.

## Compiler 

Avant de compiler, si vous n'avez pas raylib sur votre machine vous pouvez suivre cette page faite par notre enseignant : [installer raylib](https://github.com/LucFabresse/mlod-algoc-sujets/blob/main/MiniProjet/HOW_TO_Raylib.md)

Pour compiler veuillez lancer la commande: 
```
$ make snake
```
Ce qui donnera un executable ./snake

## Exécuter 
Pour lancer le jeu: 
```
$ make game
```

## Nettoyer
```
$ make clean
```

## Jouer au jeu ?

Voici le menu présenté à l'entrée du jeu ! :
![menu](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Menu_du_jeu.png)

3 choix se présentent à vous: 
* Le classique Snake ! Les règles sont simples: il ne faut pas rentrer dans les murs ni dans soi-même et le but est de faire le plus long serpent possible en mangeant des fruits.
![snake](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Snake.png)
* Le stoïque Senèque ! Les règles sont identiques au Snake classique. La conduite peut-être accidentée si vous lisez en même temps...
![seneque](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Seneque.png)
* Le dangereux Snare ! Attention! des obstacles apparaissent pendant votre course, les pièges sont dangereux que lorsqu'ils sont violet foncé. Pour vous aider, les murs sont vos amis !!
![snare](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Snare.png)

# Touches 

Menu: 
- 1, 2 ou 3 : choix du jeu

En jeu:
- P : bouton PAUSE en jeu
- arrow_keys : changement de direction du serpent

Ecran de défaite: 
- ENTER : rejouer au même jeu
- I : revenir au menu initial
![ecran de défaite](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Ecran_defaite.png)

# Implémentation

Pour différencier mon code de celui donné par raylib, j'ai crée un module projet.c et son header projet.h dans lesquels sont définis les fonctions, structures et autres que j'ai implémenté. Le module est initié et fermé avec les fonctions InitProjetAddOn et CloseProjetAddOn.

Tout d'abord, la version que j'ai implémenté propose plusieurs jeux et un menu. J'ai implémenté quatre états de jeu (GameState) qui renseignent quand le jeu est dans le menu ou dans un des jeux. En fonction de ce flag, l'application réagit différement. 
En pratique, j'ai traduit cela par une énumération pouvant représenter 4 états et une variable globale du jeu qui prend comme valeur l'état courant.

Ensuite, l'implémentation du deuxième jeu Senèque n'a pas été très sorcier. Si le jeu est dans l'état GAME_SENEQUE, on charge une image de la tête de Senèque à le place de celle du serpent. Ensuite, dès que le joueur mange un fruit on affiche au milieu de l'écran une des citations de Senèque.

Finalement, pour le dernier jeu, j'ai utilisé une liste chaînée pour stocker les pièges qui se créent au fur et à mesure de la partie et supprimer les plus anciens. Un piège a 3 états : gris, violet et violet foncé et une durée de vie variable. La structure de données représentant un piège est très similaire à celle du fruit implémenté par raylib: 
- une position
- une taille 
- un booléen si il est actif ou non
- une couleur
mais avec des ajouts: 
- un état : initialisé, en chargement et chargé
- le nombre de secondes depuis sa création

Toutes les frames, les pièges sont mis à jours. 

# Améliorations possibles

* En réalité, le nombre de pièges ne dépasse pas une valeur qu'on pourrait déterminer en début de programme, en fonction du temps de vie d'un piège. De ce fait, une liste chaînée est peut-être trop performante pour ce qu'on cherche à faire. Un buffer circulaire aurait été plus approprié. En effet, l'implémentation d'un buffer circulaire aurait éviter d'allouer et de désallouer de la mémoire dès qu'un piège apparait ou disparait. D'autant plus que nous ne savons pas combien de temps la fonction malloc peut prendre ce qui est embêtant dans un jeu à temps réel.

* D'un point de vue gameplay: on peut aussi imaginer que les pièges se déplacent vers la gauche et apparaissent sur la première colonne aléatoirement.