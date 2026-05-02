#pragma once
#include <iostream>
#include "Case.hpp"
#include <vector>  
using namespace std;

class Donjon {
    // Explications perso :
    // grille est un tableau dynamique de lignes (vector<vector<Case*>>)
    // Chaque ligne est elle-même un tableau dynamique de pointeurs vers des objets Case (vector<Case*>)
private:
    vector<vector<Case*>>grille ; 
    int largeur, hauteur;
public :
    int get_largeur() const {return largeur;};
    int get_hauteur() const {return hauteur;};
    void set_case(int x, int y, Case* newCase);

    void poserEntree();
    void poserSortie();

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