#include <iostream>
#include "../include/Aventurier.hpp"
#include "../include/Monstre.hpp"
#include "../include/Tresor.hpp"
#include "../include/Piege.hpp"

using namespace std;

Aventurier::Aventurier(int startX, int startY) : x(startX), y(startY), pv(100), nbTresors(0) {}

void Aventurier::deplacer(int nx, int ny) {
    x = nx;
    y = ny;
}

bool Aventurier::estVivant() const {
    return pv > 0;
}

void Aventurier::afficherStatut() const {
    cout << "\nPosition : (" << x << ", " << y << ")" << endl;
    cout << "Sante    : " << pv << " PV" << endl;
    cout << "Tresors  : " << nbTresors << endl;
}

void Aventurier::modifierPV(int delta) {
    pv += delta;
}

void Aventurier::ajouterTresor() {
    nbTresors++;
}

int Aventurier::getX() const { return x; }
int Aventurier::getY() const { return y; }