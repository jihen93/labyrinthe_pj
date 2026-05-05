#include "../include/CaseFactory.hpp"
#include "../include/Mur.hpp"
#include "../include/Monstre.hpp"
#include "../include/Piege.hpp"
#include "../include/Tresor.hpp"
#include "../include/Passage.hpp"

Case* CaseFactory::creerCase(enum TypeCase t) { // creercase retourne donc un pointeur qui contient un objet d'une classe
    switch(t) {
        case MUR: {
            Mur* mur = new Mur();
            return mur;
        }
        case MONSTRE: {
            Monstre* monstre = new Monstre();
            return monstre;
        }
        case PIEGE: {
            Piege* piege = new Piege();
            return piege;
        }
        case TRESOR: {
            Tresor* tresor = new Tresor();
            return tresor;
        }
        case PASSAGE: {
            Passage* passage = new Passage();
            return passage;
        }
        /*case SOL: {
            Sol* sol = new Sol();
            return sol;
        }
        */
        case PORTE: {
            return new Passage('S');
        }

        default:
            return nullptr; // Gestion d'erreur si nécessaire
    }
}