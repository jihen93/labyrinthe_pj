#include "include/Donjon.hpp"
#include "include/Mur.hpp"
#include "include/Tresor.hpp"
#include "include/Monstre.hpp"
#include <iostream>
#include <utility> // Pas oublier, sinon le main ne renvoie rien !

using namespace std;
    
int main() {

    Mur m;
    Tresor t(50);
    Monstre mon(100);
    //Donjon donjon;
    //donjon.generer(20,20);
    //donjon.afficher();

    cout << "Affichage des cases test :" << endl;
    cout << "Mur : " << m.afficher() << endl;
    cout << "Tresor : " << t.afficher() << " (Valeur: " << t.getValeur() << ")" << endl;
    cout << "Monstre : " << mon.afficher() << " (PV: " << mon.getPv() << ")" << endl;
    
    return 0;
}