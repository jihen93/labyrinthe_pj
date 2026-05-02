#pragma once
#include <iostream>
#include "Case.hpp"
#include <vector>  
using namespace std;

class Donjon {
    vector<vector<Case*>>grille ;
    int largeur;
    int hauteur;
public :
    void generer ( int largeur , int hauteur ) ;
    void afficher () ;
    //vector < pair < int , int > > trouverChemin ( /* ...  */) ;
};  

/* Affichage ASCII du donjon :

Aventurier : @ 
Trésors : +
Monstres : M
Pieges : T
Murs : #  

*/