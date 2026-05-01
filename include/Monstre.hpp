#pragma once
#include "Case.hpp"

// Monstre : affichage M

class Monstre : public Case { 
private:
    int pv;

public:
    Monstre(int p = 20) : pv(p) {}
    char afficher() const override {
        return 'M';
    }

    int getPv() const { return pv; }
};