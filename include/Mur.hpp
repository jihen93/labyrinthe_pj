#pragma once
#include "Case.hpp"

// classes des différentes types de cases à compléter

class Mur : public Case { 
public : 
    Mur () = default; // rien à initialiser ici
    char afficher() override;
};