#pragma once
#include "Case.hpp"

// Tresor : affichage +

class Tresor : public Case { 
private:
    int valeur; 

public:
    Tresor(int v = 10) : valeur(v) {} // constructeur
    
    char afficher() override { // implémentation de la méthode virtuelle pure
        return '+';
    }

    int getValeur() const { return valeur; }
};