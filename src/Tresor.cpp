#include "../include/Tresor.hpp"

// Le constructeur doit être défini ici
Tresor::Tresor(int v) : valeur(v) {}

char Tresor::afficher() {
    return '+';
}

int Tresor::getValeur() const {
    return valeur;
}