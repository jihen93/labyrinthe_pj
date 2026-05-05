#pragma once
#include "Case.hpp"

class Passage : public Case { 
private:
    char symbole = ' ';
public: 
    Passage();
    Passage(char s);
    char afficher() override;
};