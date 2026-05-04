#pragma once
#include "Case.hpp" 

enum TypeCase {
    MUR,
    MONSTRE,
    PIEGE,
    TRESOR,
    PASSAGE,
    SOL,
    PORTE
};

class CaseFactory {
public:
    static Case* creerCase(TypeCase t); 
};