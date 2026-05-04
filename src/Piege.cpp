#include "../include/Piege.hpp"

Piege::Piege(int d) : degats(d) {}

char Piege::afficher() {
    return 'T'; 
}

int Piege::getDegats() const {
    return degats;
}