#pragma once
#include "Donjon.hpp"

class GenerateurDeLabyrinthe {
public :
    void static initialiserGrille(Donjon &donjon); // mettre static évite de créer une instance plus tard
private :
    void static genererLabyrinthe(Donjon &donjon, int x, int y); 

    void placerElements(Donjon &donjon); // Reste à faire
};

