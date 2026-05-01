#pragma once
#include <iostream>

class Donjon {
    vector < vector < Case * > > grille ;
    int largeur;
    int hauteur;
public :
    void generer ( int largeur , int hauteur ) ;
    void afficher () ;
    vector < pair < int , int > > trouverChemin ( /* ...  */) ;
};  

/* Affichage ASCII du donjon :

Aventurier : @ 
Trésors : +
Monstres : M
Pieges : T
Murs : #  

*/