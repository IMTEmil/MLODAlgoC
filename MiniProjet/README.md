# MiniProjet

## Description

Ce projet a été réalisé dans le cadre du cours donné par Luc Fabresse en MLOD à IMT Nord Europe en 2022/2023.

Il reprend le classique jeu snake qui a été forké depuis [raylib] (https://raylib.com). J'y ai ajouté des options supplémentaires: 
Le principe est de créer des variantes du jeu classique Snake autour de jeu de mots avec le mot 'snake'.
    * Sénèque : le stoïcien de renom remplace la tête de serpent et instruit son joueur.
    * Snare : le jeu est jonché de pièges qu'il faut éviter, ils apparaissent petit à petit et progressivement.

Le répertoire contient:
* Le code source du jeu original donné par Raylib dans snake.c
* Le module du projet avec son code source (projet.c) et le header (projet.h). 
* Un Makefile pour compiler et lancer le jeu.
* Un README.md que vous êtes en train de lire. 

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
