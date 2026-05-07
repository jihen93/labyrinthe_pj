#include <iostream>
#include <utility> // Pas oublier, sinon le main ne renvoie rien !
#include "include/Donjon.hpp"
#include "include/Aventurier.hpp"
#include "include/Mur.hpp"
#include "include/Tresor.hpp"
#include "include/Monstre.hpp"
#include "include/Case.hpp"
#include "include/CaseFactory.hpp"

using namespace std;
    

int main() {
    int largeur;
    int hauteur;
    do {
    cout << "Largeur : " ;
    cin >> largeur;
    } while(largeur <= 0);

    do{
    cout << "Hauteur : " ;
    cin >> hauteur;
    } while(hauteur <= 0);

    Donjon monDonjon;
    monDonjon.generer(largeur, hauteur);

    vector<pair< int,int>> chemin = monDonjon.trouverChemin();
    cout << "Chemin optimal" << endl;
    monDonjon.afficher_bfs(chemin);
    cout << "----------------------" << endl << endl;
    Aventurier joueur(0, 0);
    char commande;

    while (joueur.estVivant()) {
        monDonjon.afficher(joueur); 

        cout << "PV: " << joueur.getPV() << " | Tresors: " << joueur.getNbTresors() << endl;
        cout << "\nAction (z:haut, s:bas, q:gauche, d:droite, x:quitter) : ";
        cin >> commande;

        if (commande == 'x') break;

        int nx = joueur.getX();
        int ny = joueur.getY();

        if (commande == 'z') ny--;
        else if (commande == 's') ny++;
        else if (commande == 'q') nx--;
        else if (commande == 'd') nx++;

        if (monDonjon.estFranchissable(nx, ny)) {
            joueur.deplacer(nx, ny);
            monDonjon.resoudreCase(joueur, monDonjon.get_case(nx, ny));
        } else {
            cout << "Mur !" << endl;
        }
    }

    if (!joueur.estVivant()){ cout << "Mort..." << endl;}
    return 0;
}