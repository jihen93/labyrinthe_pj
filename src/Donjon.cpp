#include <iostream>
#include "../include/Donjon.hpp"
#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/CaseFactory.hpp"
#include "../include/Aventurier.hpp"

#include <vector>
#include <queue>
using namespace std;

void Donjon::set_case(int x, int y, Case* newCase) {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        delete grille[y][x]; // On supprime l'ancien MUR
         grille[y][x] = newCase; // On place le nouveau PASSAGE
    }
}

void Donjon::set_visite(int x, int y, bool valeur) {
if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        visite[y][x] = valeur;
    }
}

void Donjon::generer() {
    grille.resize(hauteur, vector<Case*>(largeur, nullptr)); // obligatoire sinon durant l'execution : Segmentation fault (core dumped)
    visite.resize(hauteur, vector<bool>(largeur, false)); // Initialise à false
    for(int i = 0; i < hauteur; i++) {
        for(int j = 0; j < largeur; j++) {
            grille[i][j] = CaseFactory::creerCase(MUR); // static_cast : void* vers case* // initialiser par des murs
        }
    }
    GenerateurDeLabyrinthe::initialiserGrille(*this); // démarrer à la case (1,1)
    
    this->poserSortie();           // Place le 'S' en bas à droite
    this->ajouterEntites(8, 6, 3);    // Place 8 trésors, 6 monstres et 3 pieges
}

void Donjon::afficher(Aventurier& adv) {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            // Si les coordonnées correspondent à la position du joueur
            if (adv.getX() == j && adv.getY() == i) {
                cout << "@"; 
            } else {
                cout << grille[i][j]->afficher();
            }
        }
        cout << endl;
    }
}

bool Donjon::estFranchissable(int x, int y) {
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) return false;
   
    char symbole = grille[y][x]->afficher();
 
    return (symbole == ' ' || symbole == '+' || symbole == 'M' || symbole == 'T' || symbole == 'S');
}

Case* Donjon::getCase(int x, int y) {
    return grille[y][x];
}
    
void Donjon::poserSortie() {
    set_case(17, 18, static_cast<Case*>(CaseFactory::creerCase(PORTE))); 
}

void Donjon::ajouterEntites(int nbTresors, int nbMonstres, int nbPieges) {
    int places = 0;
    while (places < (nbTresors + nbMonstres + nbPieges)) {
        int rx = rand() % (largeur - 2) + 1;
        int ry = rand() % (hauteur - 2) + 1;

        if (getCase(rx, ry)->afficher() == ' ' && (rx != 1 || ry != 1)) {
            TypeCase type;
            if (places < nbTresors) type = TRESOR;
            else if (places < nbTresors + nbMonstres) type = MONSTRE;
            else type = PIEGE;

            set_case(rx, ry, static_cast<Case*>(CaseFactory::creerCase(type)));
            places++;
        }
    }
}

Donjon::~Donjon() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            delete grille[i][j]; // Supprime chaque case créée avec new
        }
    }
}


vector<pair< int,int>> Donjon::trouverChemin(pair< int,int>& depart, pair< int,int>& arrivee) { // vector<pair< int,int>>
    // file = file_vide ()
    queue<pair< int,int>> file; 

    // visite = tableau 2 D de booleens , tout a FAUX
    vector<vector<bool>> visite_bfs;
    visite_bfs.resize(hauteur, vector<bool>(largeur, false));

    // parent = tableau 2 D de positions , tout a ( -1 , -1)
    vector<vector<pair< int,int>>> parent;
    parent.resize(hauteur, vector<pair< int,int>>(largeur, pair<int,int>(-1, -1)));

    //enfiler ( file , depart )
    file.push(depart);
    
    //visite [ depart ] = VRAI
    visite_bfs[depart.first][depart.second] = true;

    pair< int,int> courant ;

    //tant que file non vide :
    while(!file.empty()){

        //courant = defiler ( file )
        courant = file.front();
        file.pop();
        
        

        //si courant == arrivee :
        if (courant == arrivee){
            //retourner reconstruireChemin ( parent , depart , arrivee)
            return (*this).reconstruireChemin(parent, depart, arrivee);
        }
        pair< int,int> nord = {courant.first-1, courant.second};
        pair< int,int> sud = {courant.first+1, courant.second};
        pair< int,int> est = {courant.first, courant.second+1};
        pair< int,int> ouest = {courant.first, courant.second-1};
        vector<pair< int,int>> v = {nord, sud, est, ouest};

        // pour chaque voisin v de courant (4 directions ) :
        for(int i = 0; i< 4; i++){

            pair< int,int> voisin = v[i];

            //si v dans bornes ET non visite ET v n ’ est pas MUR :
            if ((*this).estFranchissable(voisin.first, voisin.second) && !visite_bfs[voisin.first][voisin.second]){
                //visite [ v ] = VRAI
                visite_bfs[voisin.first][voisin.second] = true;
                //parent [ v ] = courant
                parent[voisin.first][voisin.second] = courant;
                //enfiler ( file , v )
                file.push(voisin);
            }
        }
        
    }
    //retourner []
        vector<pair< int,int>> vide;
        return vide;

}

vector<pair< int,int>> Donjon::reconstruireChemin(vector<vector<pair< int,int>>> parent,pair< int,int>& depart, pair< int,int>& arrivee) {
    // chemin = liste vide
    vector<pair< int,int>> chemin;

    //courant = arrivee
    pair< int,int> courant = arrivee;

    //tant que courant != depart :
    while(courant != depart){
        
        // ajouter courant en tete de chemin
        chemin.insert(chemin.begin(), courant);
        //courant = parent [ courant ]
        courant = parent[courant.first][courant.second];
    }

    //ajouter depart en tete de chemin
    chemin.insert(chemin.begin(), depart);
    //DEBUG  
    return chemin;
}

void Donjon::afficher_bfs(vector<pair<int,int>> chemin){
    bool flag;
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                flag = true;

                if (grille[i][j]->afficher() == '#') {
                    cout << "#"; 
                    flag = false;
                }
                else{
                    for (pair<int,int> val : chemin) {
                        if (j == val.first && i == val.second) {
                            cout << ".";
                            flag = false;
                            break;
                        }
                    }
                    if (flag){
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }


    


}