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

/*class Donjon {
    vector < vector < Case * > > grille ;
public :
    void generer ( int largeur , int hauteur ) ;
    void afficher () ;
    vector < pair < int , int > > trouverChemin ( /* ...  ) ;
};  
*/  

/* Affichage ASCII du donjon :

Aventurier : @ 
Trésors : +
Monstres : M
Pieges : T
Murs : #  

*/

int main() {

    Mur m;
    Tresor t(50);
    Monstre mon(100);

    cout << "Affichage des cases test :" << endl;
    cout << "Mur : " << m.afficher() << endl;
    cout << "Tresor : " << t.afficher() << " (Valeur: " << t.getValeur() << ")" << endl;
    cout << "Monstre : " << mon.afficher() << " (PV: " << mon.getPv() << ")" << endl;

    return 0;
}