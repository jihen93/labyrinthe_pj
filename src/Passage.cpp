#include "../include/Passage.hpp"

Passage::Passage() : symbole(' ') {} 
Passage::Passage(char s) : symbole(s) {}

char Passage::afficher() {
    return symbole; 
}