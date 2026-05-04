#pragma once
#include "Case.hpp"

// Tresor : affichage +

class Tresor : public Case { 
private:
    int valeur; 

public:
    Tresor(int v = 10);
    
    char afficher() override;
    int getValeur() const;
};