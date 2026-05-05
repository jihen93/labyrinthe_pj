#include <iostream>
#include "../include/Donjon.hpp"
#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/CaseFactory.hpp"
#include "../include/Aventurier.hpp"

#include <vector>
using namespace std;

void Donjon::set_case(int x, int y, Case* newCase) {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        delete grille[y][x]; // On supprime l'ancien MUR
         grille[y][x] = newCase; // On place le nouveau PASSAGE
    }
}

void Donjon::set_visite(int x, int y, bool valeur) {
if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        visite[y][x] = valeur;
    }
}

void Donjon::generer() {
    grille.resize(hauteur, vector<Case*>(largeur, nullptr)); // obligatoire sinon durant l'execution : Segmentation fault (core dumped)
    visite.resize(hauteur, vector<bool>(largeur, false)); // Initialise à false
    for(int i = 0; i < hauteur; i++) {
        for(int j = 0; j < largeur; j++) {
            grille[i][j] = CaseFactory::creerCase(MUR); // static_cast : void* vers case* // initialiser par des murs
        }
    }
    GenerateurDeLabyrinthe::initialiserGrille(*this); // démarrer à la case (1,1)
}

void Donjon::afficher(Aventurier& adv) {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            // Si les coordonnées correspondent à la position du joueur
            if (adv.getX() == j && adv.getY() == i) {
                cout << "@"; 
            } else {
                cout << grille[i][j]->afficher();
            }
        }
        cout << endl;
    }
}

bool Donjon::estFranchissable(int x, int y) {
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) return false;
    return grille[y][x]->afficher() != '#'; 
}

Case* Donjon::getCase(int x, int y) {
    return grille[y][x];
}
    