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
    

void resoudreCase(Aventurier& adv, Case* c, Donjon& d) {
    if (!c) return;
    char symbole = c->afficher();

    if (symbole == '+') { 
        std::cout << "[!] TRESOR ! Vous le ramassez." << std::endl;
        adv.ajouterTresor();
        d.set_case(adv.getX(), adv.getY(), static_cast<Case*>(CaseFactory::creerCase(PASSAGE)));
    } 
    else if (symbole == 'T') { 
        std::cout << "[!] CLIC... Un PIEGE ! -15 PV." << std::endl;
        adv.modifierPV(-15);
    } 
    else if (symbole == 'M') { 
        if (adv.combattreMonstre()) { // si le montre a été vaincu, la case devient un passage
            d.set_case(adv.getX(), adv.getY(), static_cast<Case*>(CaseFactory::creerCase(PASSAGE)));
        }
    }
    if (symbole == 'S') { 
        std::cout << "   VICTOIRE ! VOUS ETES SORTI !  " << std::endl;
        std::cout << "   Tresors recoltes : " << adv.getNbTresors() << std::endl;
        exit(0);
    }
}

int main() {
    Donjon monDonjon;
    monDonjon.generer(20, 20);
    pair<int, int> depart = {0, 0};
    pair<int, int> arrivee = {19, 19};
    vector<pair< int,int>> chemin = monDonjon.trouverChemin(depart, arrivee);
    cout << "Chemin optimal" << endl;
    monDonjon.afficher_bfs(chemin);
    cout << "----------------------" << endl << endl;
    Aventurier joueur(1, 1);
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
            resoudreCase(joueur, monDonjon.get_case(nx, ny), monDonjon);
        } else {
            cout << "Mur !" << endl;
        }
    }

    if (!joueur.estVivant()){ cout << "Mort..." << endl;}
    return 0;
}