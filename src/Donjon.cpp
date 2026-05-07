#include <iostream>
#include "../include/Donjon.hpp"
#include "../include/CaseFactory.hpp"
#include "../include/Aventurier.hpp"

#include <vector>
#include <queue>
using namespace std;

int Donjon::get_hauteur() const {
    return hauteur;
}

int Donjon::get_largeur() const {
    return largeur;
}

void Donjon::set_case(int x, int y, Case* newCase) {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        delete grille[y][x]; // On supprime l'ancien MUR
        grille[y][x] = newCase; // On place le nouveau PASSAGE
    }
}

Case* Donjon::get_case(int x, int y) {
    return grille[y][x];
}

void Donjon::poserEntree() {
    set_case(0, 0, CaseFactory::creerCase(PORTE_E)); 
}

void Donjon::poserSortie() {
    set_case(sortie.first, sortie.second, CaseFactory::creerCase(PORTE_S)); 
}

void Donjon::set_visite(int x, int y, bool valeur) {
if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        visite[y][x] = valeur;
    }
}

bool Donjon::get_visite(int x, int y) const {
    return visite[y][x]; 
}

void Donjon::generer(int largeur, int hauteur) {
    this->largeur = largeur;  // Stocke la largeur
    this->hauteur = hauteur;  // Stocke la hauteur

    //sortie pas au coin car probleme de labyrinthe
    if (hauteur % 2 == 0) sortie.first = hauteur - 2;
    else sortie.first = hauteur - 3;

    if (largeur % 2 == 0) sortie.second = largeur - 2;
    else sortie.second = largeur - 3;

    grille.resize(hauteur, vector<Case*>(largeur, nullptr)); // obligatoire sinon durant l'execution : Segmentation fault (core dumped)
    visite.resize(hauteur, vector<bool>(largeur, false)); // Initialise à false
    for(int i = 0; i < hauteur; i++) {
        for(int j = 0; j < largeur; j++) {
            grille[i][j] = CaseFactory::creerCase(MUR); // static_cast : void* vers case* // initialiser par des murs
        }
    }
    genererLabyrinthe(0, 0);
    

    this->poserSortie();           // Place le 'S' en bas à droite
    this->poserEntree();
    this->PlacerElements();
}

void Donjon::genererLabyrinthe(int x, int y) {
    set_visite(x, y, true);  // Marquer la case actuelle comme visitée // MAIS case (0,0) jamais visité ??
    set_case(x, y, CaseFactory::creerCase(PASSAGE));
    int dir[4][2] = {{0, +2}, {0, -2}, {+2, 0}, {-2, 0}}; // Tableau 2D de directions : Nord, Sud, Est, Ouest et on regarde 2 cases en avant
    
    // mélange(directions)
    for (int i = 3; i >= 0; i--) { //selon algo de Fisher-Yates
        int r = rand() % (i + 1);  // nb aléatoire entre 0 et i
        swap(dir[i][0], dir[r][0]);
        swap(dir[i][1], dir[r][1]);
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        
        if (nx >= 0 && nx < largeur-1 && ny >= 0 && ny < hauteur-1 && !get_visite(nx,ny)) { // de 1 à 19 ?? (visit(20, 20))
            // Casser le mur entre (x,y) et (nx,ny)
            set_case((x + nx) / 2, (y + ny) / 2, CaseFactory::creerCase(PASSAGE)); // à vérifier
            genererLabyrinthe(nx, ny); // recursif
        }
    }
}

void Donjon::afficher(Aventurier& adv) {
    //premiere ligne
    cout << "+" ;
    for (int i = 0; i < hauteur; i++){
        cout << "-";
    }
    cout << "+" << endl;

    for (int i = 0; i < hauteur; i++) {
        cout << "|" ;
        for (int j = 0; j < largeur; j++) {
            // Si les coordonnées correspondent à la position du joueur
            if (adv.getX() == j && adv.getY() == i) {
                cout << "@"; 
            } else {
                cout << grille[i][j]->afficher();
            }
        }
        cout << "|" << endl;
    }

    //derniere ligne
    cout << "+" ;
    for (int i = 0; i < hauteur; i++){
        cout << "-";
    }
    cout << "+" << endl;
}

bool Donjon::estFranchissable(int x, int y) {
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) return false;
   
    char symbole = grille[y][x]->afficher();
 
    return (symbole == ' ' || symbole == '+' || symbole == 'M' || symbole == 'T' || symbole == 'S');
}

void Donjon::PlacerElements() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (get_case(i, j)->afficher() == ' ') {
                int r = rand() % 101; // de 0 à 100
                if (r < 5) {
                    set_case(i, j, CaseFactory::creerCase(TRESOR));
                }
                else if (r < 10) {
                    set_case(i, j, CaseFactory::creerCase(MONSTRE));
                }
                else if (r < 13) {
                    set_case(i, j, CaseFactory::creerCase(PIEGE));
                }
            }
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

vector<pair< int,int>> Donjon::trouverChemin() { // 
    pair< int,int> depart = {0,0};
    pair< int,int> arrivee = sortie;
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
    //premiere ligne
    cout << "+" ;
    for (int i = 0; i < hauteur; i++){
        cout << "-";
    }
    cout << "+" << endl;
        for (int i = 0; i < hauteur; i++) {
            cout << "|" ;
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
            cout << "|" << endl;
        }
    //premiere ligne
    cout << "+" ;
    for (int i = 0; i < hauteur; i++){
        cout << "-";
    }
    cout << "+" << endl;

}