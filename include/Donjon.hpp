#pragma once
#include <iostream>
#include "Case.hpp"
#include <vector>  
#include <queue>
using namespace std;

class Aventurier;

class Donjon {
    // Explications perso :
    // grille est un tableau dynamique de lignes (vector<vector<Case*>>)
    // Chaque ligne est elle-même un tableau dynamique de pointeurs vers des objets Case (vector<Case*>)
private:
    vector<vector<Case*>>grille ; 
    vector<vector<bool>> visite; // Tableau dynamique de visite, par déf, on ne connait pas sa taille avant exécution et besoin d'etre initialisé une seule fois
    int largeur = 20, hauteur = 20;

public :
    int get_largeur() const;
    int get_hauteur() const;

    void set_case(int x, int y, Case* newCase);
    Case* get_case(int x, int y);

    bool get_visite(int x, int y) const;
    void set_visite(int x, int y, bool valeur);

    void poserEntree();
    void poserSortie();

    void PlacerElements();
    void genererLabyrinthe(int x, int y);

    void generer();
    void afficher(Aventurier& adv);

    ~Donjon(); // vider la memoire
    bool estFranchissable(int x, int y);
    vector<pair< int,int>> trouverChemin(pair< int,int>& depart, pair< int,int>& arrivee) ;
    vector<pair< int,int>> reconstruireChemin(vector<vector<pair< int,int>>> parent, pair< int,int>& depart, pair< int,int>& arrivee) ;
    void afficher_bfs(vector<pair<int,int>> chemin);
};  

/* Affichage ASCII du donjon :

Aventurier : @ 
Trésors : +
Monstres : M
Pieges : T
Murs : #  

*/