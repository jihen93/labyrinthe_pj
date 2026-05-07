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
    
    char f_ou_c;
    int proba = rand() % (9 + 1) + 1; // nombre aléatoire entre 1 et 10
    cout << "Vous rencontrez un monstre, voulez vous (f)uir ou (c)ombattre ? : ";
    cin >> f_ou_c;

    if (f_ou_c == 'f') { // 20% de chance de fuite
        proba = rand() % (9 + 1) + 1; 
        if (proba <=2) {
            cout << "Vous réussisez à fuire" << endl;
            return false;
        }
        else{
            cout << "Il n'y a aucun échapatoire" << endl;
        }
    }


    cout << "----------------" << endl;
    cout << "Pour le vaincre il faut lui infliger 25 degâts" << endl;
    while (pvMonstre > 0 && pv > 0) {
        
        char choix;
        cout << endl << "----------------" << endl;
        cout << "Monstre : " << pvMonstre << "pv, Aventurier : " << pv << "pv" << endl;
        cout << "Appuyer sur une touche, pour frapper le monstre : ";
        cin >> choix;
        // Generate random number in the range [min, max]
        degats = rand() % (9 + 1) + 1; 
        cout << "Vous frappez le montre et lui infligez " << degats << " degats." << endl;
        pvMonstre -= degats;
        degats = rand() % (9 + 1) + 1; 
        cout << "Mais le monstre vous attaque aussi. Il vous inflige " << degats << " degats." << endl;
        pv -= degats;
    }
    return (pvMonstre <= 0);
}

int Aventurier::getX() const { return x; }
int Aventurier::getY() const { return y; }