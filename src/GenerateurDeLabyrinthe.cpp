#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/GenerateurDeLabyrinthe.hpp"
#include "../include/CaseFactory.hpp"

#include <vector>  
#include <algorithm> // indispensable pour shuffle
#include <random>  // indispensable pour shuffle
using namespace std;

void GenerateurDeLabyrinthe::initialiserGrille(Donjon &donjon) {
    genererLabyrinthe(donjon, 1, 1);
}

void GenerateurDeLabyrinthe::genererLabyrinthe (Donjon &donjon, int x, int y) { // etat actuel
    //char visit[20][20];
    //visit[x][y] = "visite"; // Tableau de caractères
    static bool visite[20][20] = {false};  // Initialisé les cases visitées à false
    visite[x][y] = true;  // Marquer la case actuelle comme visitée
    vector<pair<int, int>> directions = {{0, +2}, {0, -2}, {+2, 0}, {-2, 0}}; // Tableau de caractères : Nord, Sud, Est, Ouest et on regarde 2 cases en avant
    
    // https://en.cppreference.com/cpp/algorithm/random_shuffle // std::random_shuffle is deprecated
    random_device rd;
    mt19937 g(rd());
    shuffle(directions.begin(), directions.end(), g);

    for (const auto &dir : directions) {
        int nx = x + dir.first;
        int ny = y + dir.second;
        
        if (nx >= 1 && nx < donjon.get_hauteur() - 1 && ny >= 1 && ny < donjon.get_largeur() - 1 && !visite[nx][ny]) {
            // Casser le mur entre (x,y) et (nx,ny)
            donjon.set_case((x + nx) / 2, (y + ny) / 2, static_cast<Case*>(CaseFactory::creerCase(PASSAGE)));
            genererLabyrinthe(donjon, nx, ny); // recursif
            }
    }

}