#include <iostream>
#include <vector>  
#include <utility> 

using namespace std;
// Classe abstraite de base
class Case {
public :
    virtual char afficher () = 0;
    virtual ~ Case () = default ;
};

// classes des différentes types de cases à compléter

class Mur : public Case { 
public : 
    Mur () = default; // rien à initialiser ici
    char afficher() override {
        return '#';
    }
};

class Passage : public Case { 
public: 
    Passage () = default;
    char afficher() override {
        return ' ';
    }
};

// Tresor : affichage +

class Tresor : public Case { 
private:
    int valeur; 

public:
    Tresor(int v = 10) : valeur(v) {} // constructeur
    
    char afficher() override { // implémentation de la méthode virtuelle pure
        return '+';
    }

    int getValeur() const { return valeur; }
};

// Monstre : affichage M

class Monstre : public Case { 
private:
    int pv;

public:
    Monstre(int p = 20) : pv(p) {}
    char afficher() override {
        return 'M';
    };

    int getPv() const { return pv; }
};

// Piege : affichage T

class Piege : public Case {
private :
    int degats;

public:
    Piege(int d = 10) : degats(d) {}
    char afficher() override {
        return 'T';
    };

    int getDegats() const { return degats; }
};

// A ajouter a la classe donjon



/* Affichage ASCII du donjon :

Aventurier : @ 
Trésors : +
Monstres : M
Pieges : T
Murs : #  

*/

/* Info aventurier pour la boucle du jeu

Postion : (12, 9)
Sante (pv) : 100/100
Inventaire : 2 tresors
Distance a la sortie : 23 cases 
*/

class Aventurier {
private:
    int x, y;         
    int pv;          
    int nbTresors;     

public:
    Aventurier(int startX = 1, int startY = 1) : x(startX), y(startY), pv(100), nbTresors(0) {}

    void deplacer(int nx, int ny){
        x = nx;
        y = ny;
    }

    bool estVivant() const {
        return pv > 0;
    }

    void afficherStatut() const {
        std::cout << "Position : (" << x << ", " << y << ")" << std::endl;
        std::cout << "Sante    : " << pv << " PV" << std::endl;
        std::cout << "Tresors  : " << nbTresors << std::endl;
    }

    void modifierPV(int delta) { pv += delta; }
    void ajouterTresor() { nbTresors++; }

    int getX() const { return x; }
    int getY() const { return y; }
};


class Donjon {
private:
    vector<vector<Case*>> grille;
    int largeur, hauteur;

public:
    // Initialise une grille vide pour le test
    void generer(int l, int h) {
        largeur = l;
        hauteur = h;
        grille.assign(hauteur, vector<Case*>(largeur, nullptr));
        for (int i = 0; i < hauteur; ++i) {
            for (int j = 0; j < largeur; ++j) {
                grille[i][j] = new Passage(); // On met des passages partout pour tester
            }
        }
    }

    // Fonction d'affichage basique
    void afficher(const Aventurier& adv) {
        for (int i = 0; i < hauteur; ++i) {
            for (int j = 0; j < largeur; ++j) {
                if (i == adv.getY() && j == adv.getX()) cout << "@";
                else cout << grille[i][j]->afficher();
            }
            cout << endl;
        }
        adv.afficherStatut();
    }

    // Pour que ton main sache si on peut bouger (Exigence 3.5)
    bool estFranchissable(int x, int y) {
        if (x < 0 || x >= largeur || y < 0 || y >= hauteur) return false;
        return grille[y][x]->afficher() != '#'; // Vrai si ce n'est pas un mur
    }

    // Pour que resoudreCase puisse agir
    Case* getCase(int x, int y) {
        return grille[y][x];
    }
};

void resoudreCase(Aventurier& adv, Case* c) {
    if (!c) return;

    char symbole = c->afficher();

    if (symbole == '+') { 
        std::cout << "[!] TRESOR ! Vous le ramassez." << std::endl;
        adv.ajouterTresor();
    } 
    else if (symbole == 'T') { 
        std::cout << "[!] CLIC... Un PIEGE ! -15 PV." << std::endl;
        adv.modifierPV(-15);
    } 
    else if (symbole == 'M') { 
        char choix;
        cout << "[!] MONSTRE ! (c)ombattre ou (f)uir ? ";
        cin >> choix;
        if (choix == 'c') {
            adv.modifierPV(-25); //
            cout << "Victoire, mais vous etes blesse." << endl;
        } else {
            cout << "Vous fuyez prudemment." << endl;
        }
    }
}
/*
int main() {
   Mur m;
    Tresor t(50);
    Monstre mon(100);

    cout << "Affichage des cases test :" << endl;
    cout << "Mur : " << m.afficher() << endl;
    cout << "Tresor : " << t.afficher() << " (Valeur: " << t.getValeur() << ")" << endl;
    cout << "Monstre : " << mon.afficher() << " (PV: " << mon.getPv() << ")" << endl;

    return 0;
<<<<<<< HEAD

    
}*/

int main() {
    Donjon monDonjon;
    monDonjon.generer(20, 10);
    
    Aventurier joueur(1, 1);
    char commande;

    while (joueur.estVivant()) {
        monDonjon.afficher(joueur); 

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
            resoudreCase(joueur, monDonjon.getCase(nx, ny));
        } else {
            cout << "Mur !" << endl;
        }
    }

    if (!joueur.estVivant()) cout << "Mort..." << endl;
    return 0;
}