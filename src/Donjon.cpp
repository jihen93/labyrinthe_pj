#include <iostream>
#include "../include/Donjon.hpp"
#include "../include/CaseFactory.hpp"
#include "../include/GenerateurDeLabyrinthe.hpp"
#include "CaseFactory.cpp"


#include <vector>
using namespace std;

void Donjon::set_case(int x, int y, Case* newCase) {
    delete grille[x][y];
    grille[x][y] = newCase;
}

void Donjon::generer(int largeur, int hauteur) {
    grille.resize(hauteur, vector<Case*>(largeur, nullptr)); // obligatoire sinon durant l'execution : Segmentation fault (core dumped)
    for(int i = 0; i < hauteur; i++) {
        for(int j = 0; j < largeur; j++) {
            grille[i][j] = static_cast<Case*>(CaseFactory::creerCase(MUR)); // static_cast : void* vers case* // initialiser par des murs
        }
    }
    GenerateurDeLabyrinthe::initialiserGrille(*this); // démarrer à la case (1,1)
}

void Donjon::afficher() {
    for (auto &ligne : grille) {          // Pour chaque ligne de grille (ligne est une référence vers une ligne courante de la grille) // auto permet de déduire le type automatiquement
        for (Case* c : ligne) {           // Pour chaque case
            cout << c->afficher(); // équivalent à (*c).afficher()
        }
        cout << endl;
    }
}
    