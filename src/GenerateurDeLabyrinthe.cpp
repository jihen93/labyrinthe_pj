#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/CaseFactory.hpp"

#include <vector>  
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
using namespace std;

void GenerateurDeLabyrinthe::initialiserGrille(Donjon &donjon) {
    srand(time(0)); // Initialise une seule fois
    genererLabyrinthe(donjon, 1, 1);    
}

void GenerateurDeLabyrinthe::genererLabyrinthe (Donjon &donjon, int x, int y) { // etat actuel
    int hauteur = donjon.get_hauteur();
    int largeur = donjon.get_largeur();

    donjon.set_visite(x, y, true);  // Marquer la case actuelle comme visitée // MAIS case (0,0) jamais visité ??
    int dir[4][2] = {{0, +2}, {0, -2}, {+2, 0}, {-2, 0}}; // Tableau 2D de directions : Nord, Sud, Est, Ouest et on regarde 2 cases en avant
    
    // mélange(directions)
    for (int i = 3; i >= 0; i--) { //selon algo de Fisher-Yates
        int r = rand() % (i + 1);  // nb aléatoire entre 0 et i
        for (int j = 0; j < 2; j++) { //col
            swap(dir[i][j], dir[r][j]); 
        }
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        //debug
        cout << "nx: " << nx << ", ny: " << ny << endl;
        
        if (nx > 0 && nx < hauteur-1 && ny > 0 && ny < largeur-1 && !donjon.get_visite(nx,ny)) { // de 1 à 19 ?? (visit(20, 20))
            cout << "nx_valid: " << nx << ", ny_valid: " << ny << endl;
            // Casser le mur entre (x,y) et (nx,ny)
            donjon.set_case((x + nx) / 2, (y + ny) / 2, static_cast<Case*>(CaseFactory::creerCase(PASSAGE)));
            genererLabyrinthe(donjon, nx, ny); // recursif
        }
    }
}