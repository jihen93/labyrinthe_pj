#pragma once

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
    static void* creerCase(enum TypeCase t);
};