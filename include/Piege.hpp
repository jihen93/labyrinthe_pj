#pragma once
#include "Case.hpp"

// Piege : affichage T

class Piege : public Case {
private :
    int degats;

public:
    Piege(int d = 10);
    char afficher() override;
    int getDegats() const;
};