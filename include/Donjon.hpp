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
    int get_largeur() const {return largeur;};
    int get_hauteur() const {return hauteur;};
    void set_case(int x, int y, Case* newCase);

    bool get_visite(int x, int y) const { return visite[y][x]; }
    void set_visite(int x, int y, bool valeur);

    void poserEntree();
    void poserSortie();
    void ajouterEntites(int nbTresors, int nbMonstres, int nbPieges);

    void generer();
    void afficher(Aventurier& adv);

    ~Donjon(); // vider la memoire
    bool estFranchissable(int x, int y);
    Case* getCase(int x, int y);
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