#pragma once
#include <iostream>

// Classe abstraite de base
class Case {
public :
    virtual char afficher () = 0;
    virtual ~ Case () = default ;
};