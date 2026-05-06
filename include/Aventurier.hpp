#ifndef AVENTURIER_HPP
#define AVENTURIER_HPP

#include <iostream>

class Case; // Déclaration anticipée pour resoudreCase

class Aventurier {
private:
    int x, y;          // Position
    int pv;            // Points de vie
    int nbTresors;     // Inventaire

public:
    Aventurier(int startX = 1, int startY = 1);

    void deplacer(int nx, int ny);
    bool estVivant() const;
    void afficherStatut() const;

    void modifierPV(int delta);
    void ajouterTresor();

    int getPV() const { return pv; }
    int getNbTresors() const { return nbTresors; }

    int getX() const;
    int getY() const;
};

#endif