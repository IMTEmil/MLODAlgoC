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
* Le classique Snake ! Les règles sont simples: il ne faut pas rentrer dans les murs ni dans soi-même et le but est de faire le plus long serpent possible. 
![menu](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Snake.png)
* Le stoïque Senèque ! Les règles sont identiques au Snake classique. La conduite peut-être accidentée si vous lisez en même temps...
![menu](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Seneque.png)
* Le dangereux Snare ! Attention! des obstacles apparaissent pendant votre course, les pièges sont dangereux que lorsqu'ils sont violet foncé. Pour vous aider, les murs sont vos amis !!
![menu](https://raw.github.com/IMTEmil/MLODAlgoC/master/MiniProjet/assets/Snare.png)