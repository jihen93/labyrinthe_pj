#include <iostream>
#include "Donjon.hpp"

void Donjon::generer(int largeur, int hauteur) {
        for(int i = 0; i < hauteur; i++) {
            for(int j = 0; j < largeur; j++) {
                grille[i][j] = static_cast<Case*>(CaseFactory::creerCase(MUR)); // void* vers case*
            }
        }
    }

    