#pragma once
#include "Case.hpp" 

enum TypeCase {
    MUR,
    MONSTRE,
    PIEGE,
    TRESOR,
    PASSAGE,
    SOL,
    PORTE_E,
    PORTE_S
};

class CaseFactory {
public:
    static Case* creerCase(TypeCase t); 
};