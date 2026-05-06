#include <iostream>
#include <random>
#include <ctime>
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
bool Aventurier::combattreMonstre(){
    int pvMonstre = 20;
    int degats;

    // Define range
    int min = 1;
    int max = 10;
    

    // Initialize a random number generator
    
    uniform_int_distribution<> distrib(min, max);


    cout << "----------------" << endl;
    cout << "Vous rencontrez un monstre, pour le vaincre il faut lui infliger 25 degâts" << endl;
    while (pvMonstre > 0 && pv > 0) {
        char choix;
        cout << endl << "----------------" << endl;
        cout << "Monstre : " << pvMonstre << "pv, Aventurier : " << pv << "pv" << endl;
        cout << "Appuyer sur une touche, pour frapper le monstre : ";
        cin >> choix;
        // Generate random number in the range [min, max]
        mt19937 gen(time(0));
        degats = distrib(gen);
        cout << "Vous frappez le montre et lui infligez " << degats << " degats." << endl;
        pvMonstre -= degats;
        mt19937 gen2(time(0) + 1);
        degats = distrib(gen2);
        cout << "Mais le monstre vous attaque aussi. Il vous inflige " << degats << " degats." << endl;
        pv -= degats;
    }
    return (pvMonstre == 0);
}

int Aventurier::getX() const { return x; }
int Aventurier::getY() const { return y; }