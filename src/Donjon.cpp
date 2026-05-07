#include <iostream>
#include "../include/Donjon.hpp"
#include "../include/CaseFactory.hpp"
#include "../include/Aventurier.hpp"
#include <vector>
#include <queue>
#include <algorithm> 

using namespace std;

// --- ACCESSEURS DE BASE ---

int Donjon::get_hauteur() const { return hauteur; }
int Donjon::get_largeur() const { return largeur; }

/**
 * Remplace une case à des coordonnées spécifiques.
 * Gère la désallocation de l'ancienne case pour éviter les fuites mémoire.
 */
void Donjon::set_case(int x, int y, Case* newCase) {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        delete grille[y][x]; // Libération de la mémoire de l'objet précédent
        grille[y][x] = newCase; 
    }
}

Case* Donjon::get_case(int x, int y) {
    return grille[y][x];
}

// --- PLACEMENT DES POINTS CLÉS ---

void Donjon::poserEntree() {
    set_case(0, 0, CaseFactory::creerCase(PORTE_E)); 
}

void Donjon::poserSortie() {
    // Note : sortie.first = y, sortie.second = x
    set_case(sortie.second, sortie.first, CaseFactory::creerCase(PORTE_S)); 
}

// --- GESTION DE L'EXPLORATION ---

void Donjon::set_visite(int x, int y, bool valeur) {
    if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
        visite[y][x] = valeur;
    }
}

bool Donjon::get_visite(int x, int y) const {
    return visite[y][x]; 
}

// --- GÉNÉRATION DU LABYRINTHE ---

/**
 * Initialise la structure de données du donjon.
 * Prépare la grille remplie de murs et calcule l'emplacement de la sortie.
 */
void Donjon::generer(int largeur, int hauteur) {
    this->largeur = largeur;
    this->hauteur = hauteur;

    // Calcul de la sortie (évite les bords pairs pour la compatibilité avec l'algo de génération)
    if (hauteur % 2 == 0) sortie.first = hauteur - 2;
    else sortie.first = hauteur - 1;

    if (largeur % 2 == 0) sortie.second = largeur - 2;
    else sortie.second = largeur - 1;

    // Redimensionnement et initialisation par défaut (Murs partout)
    grille.resize(hauteur, vector<Case*>(largeur, nullptr)); 
    visite.resize(hauteur, vector<bool>(largeur, false)); 
    
    for(int i = 0; i < hauteur; i++) {
        for(int j = 0; j < largeur; j++) {
            grille[i][j] = CaseFactory::creerCase(MUR);
        }
    }

    genererLabyrinthe(0, 0); // Lancement de l'algorithme récursif
    this->poserSortie();
    this->poserEntree();
    this->PlacerElements(); // Ajout des monstres/trésors
}

/**
 * Algorithme de génération par "Recursive Backtracking".
 * Creuse des passages en sautant 2 cases pour maintenir des murs de séparation.
 */
void Donjon::genererLabyrinthe(int x, int y) {
    set_visite(x, y, true);
    set_case(x, y, CaseFactory::creerCase(PASSAGE));
    
    // Définition des directions (Nord, Sud, Est, Ouest) avec un pas de 2
    int dir[4][2] = {{0, 2}, {0, -2}, {2, 0}, {-2, 0}}; 
    
    // Mélange aléatoire des directions (Algorithme de Fisher-Yates)
    for (int i = 3; i >= 0; i--) {
        int r = rand() % (i + 1);
        swap(dir[i][0], dir[r][0]);
        swap(dir[i][1], dir[r][1]);
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        
        if (nx >= 0 && nx < largeur && ny >= 0 && ny < hauteur && !get_visite(nx, ny)) {
            // "Casse" le mur entre la case actuelle et la suivante (case intermédiaire)
            set_case((x + nx) / 2, (y + ny) / 2, CaseFactory::creerCase(PASSAGE));
            genererLabyrinthe(nx, ny); // Récursion
        }
    }
}

// --- AFFICHAGE ET LOGIQUE DE JEU ---

void Donjon::afficher(Aventurier& adv) {
    cout << "+";
    for (int i = 0; i < largeur; i++) cout << "-";
    cout << "+" << endl;

    for (int i = 0; i < hauteur; i++) {
        cout << "|";
        for (int j = 0; j < largeur; j++) {
            if (adv.getX() == j && adv.getY() == i) cout << "@"; // Position joueur
            else cout << grille[i][j]->afficher(); // Symbole de la case
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int i = 0; i < largeur; i++) cout << "-";
    cout << "+" << endl;
}

/**
 * Détermine si l'aventurier peut marcher sur cette case.
 */
bool Donjon::estFranchissable(int x, int y) {
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) return false;
    char symbole = grille[y][x]->afficher();
    // Liste des symboles autorisés (tout sauf le mur '#')
    return (symbole == ' ' || symbole == '+' || symbole == 'M' || symbole == 'T' || symbole == 'S');
}

/**
 * Parcourt les passages vides pour y placer aléatoirement des objets de jeu.
 */
void Donjon::PlacerElements() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            if (get_case(j, i)->afficher() == ' ') {
                int r = rand() % 101;
                if (r < 5) set_case(j, i, CaseFactory::creerCase(TRESOR));
                else if (r < 10) set_case(j, i, CaseFactory::creerCase(MONSTRE));
                else if (r < 13) set_case(j, i, CaseFactory::creerCase(PIEGE));
            }
        }
    }
}

Donjon::~Donjon() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            delete grille[i][j]; // Nettoyage final de la mémoire
        }
    }
}

/**
 * Gère les effets déclenchés lorsqu'un joueur marche sur une case spécifique.
 */
void Donjon::resoudreCase(Aventurier& adv, Case* c) {
    if (!c) return;
    char symbole = c->afficher();

    if (symbole == '+') { 
        cout << "[!] TRESOR ! Vous le ramassez." << endl;
        adv.ajouterTresor();
        set_case(adv.getX(), adv.getY(), CaseFactory::creerCase(PASSAGE)); // La case devient vide
    } 
    else if (symbole == 'T') { 
        cout << "[!] CLIC... Un PIEGE ! -15 PV." << endl;
        adv.modifierPV(-15);
    } 
    else if (symbole == 'M') { 
        if (adv.combattreMonstre()) {
            set_case(adv.getX(), adv.getY(), CaseFactory::creerCase(PASSAGE));
        }
    }
    if (symbole == 'S') { 
        cout << "   VICTOIRE ! VOUS ETES SORTI !   " << endl;
        exit(0);
    }
}

// --- ALGORITHMES DE RÉSOLUTION  ---

/**
 * Recherche le chemin le plus court vers la sortie via un parcours en largeur (BFS).
 */
vector<pair<int,int>> Donjon::trouverChemin() {
    pair<int,int> depart = {0,0}; 
    pair<int,int> arrivee = {sortie.second, sortie.first}; 

    queue<pair<int,int>> file; 
    vector<vector<bool>> visite_bfs(hauteur, vector<bool>(largeur, false));
    vector<vector<pair<int,int>>> parent(hauteur, vector<pair<int,int>>(largeur, {-1, -1}));

    file.push(depart);
    visite_bfs[depart.second][depart.first] = true;

    while(!file.empty()){
        pair<int,int> courant = file.front();
        file.pop();

        if (courant == arrivee) return reconstruireChemin(parent, depart, arrivee);

        int dx[] = {0, 0, 1, -1};
        int dy[] = {-1, 1, 0, 0};

        for(int i = 0; i < 4; i++){
            pair<int,int> voisin = {courant.first + dx[i], courant.second + dy[i]};

            if (estFranchissable(voisin.first, voisin.second) && !visite_bfs[voisin.second][voisin.first]){
                visite_bfs[voisin.second][voisin.first] = true;
                parent[voisin.second][voisin.first] = courant; // Mémorise d'où l'on vient
                file.push(voisin);
            }
        }
    }
    return {}; // Aucun chemin trouvé
}

/**
 * Remonte le tableau de parenté pour reconstruire la liste des coordonnées du chemin.
 */
vector<pair<int,int>> Donjon::reconstruireChemin(vector<vector<pair<int,int>>> parent, pair<int,int>& depart, pair<int,int>& arrivee) {
    vector<pair<int,int>> chemin;
    pair<int,int> courant = arrivee;

    while(courant != depart){
        chemin.insert(chemin.begin(), courant);
        courant = parent[courant.second][courant.first];
    }
    chemin.insert(chemin.begin(), depart);
    return chemin;
}

/**
 * Affiche le labyrinthe en marquant le chemin de l'IA par des points ('.').
 */
void Donjon::afficher_bfs(vector<pair<int,int>> chemin){
    cout << "+";
    for (int i = 0; i < largeur; i++) cout << "-";
    cout << "+" << endl;

    for (int i = 0; i < hauteur; i++) {
        cout << "|";
        for (int j = 0; j < largeur; j++) {
            bool estSurChemin = false;
            for (auto& p : chemin) {
                if (p.first == j && p.second == i) {
                    estSurChemin = true;
                    break;
                }
            }

            if (estSurChemin) cout << "."; // Marqueur du chemin
            else cout << grille[i][j]->afficher();
        }
        cout << "|" << endl;
    }

    cout << "+";
    for (int i = 0; i < largeur; i++) cout << "-";
    cout << "+" << endl;
}