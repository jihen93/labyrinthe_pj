#pragma once
#include "Case.hpp"

// Piege : affichage T

class Piege : public Case {
private :
    int degats;

public:
    Piege(int d = 10) : degats(d) {}
    char afficher() const override {
        return 'T';
    }

    int getDegats() const { return degats; }
};