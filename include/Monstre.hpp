#pragma once
#include "Case.hpp"

// Monstre : affichage M

class Monstre : public Case { 
private:
    int pv;

public:
    Monstre(int p = 20);
    char afficher() override;
    int getPv() const;
};