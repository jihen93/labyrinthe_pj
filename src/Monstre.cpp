#include "../include/Monstre.hpp"

Monstre::Monstre(int p) : pv(p) {}

char Monstre::afficher() { 
    return 'M'; 
    }
int Monstre::getPv() const { 
    return pv; 
    }