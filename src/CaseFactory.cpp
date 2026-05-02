#include "CaseFactory.hpp"
#include "Mur.hpp"
#include "Monstre.hpp"
#include "Piege.hpp"
#include "Tresor.hpp"
#include "Passage.hpp"

static void* CaseFactory::creerCase(enum TypeCase t) { // creercase retourne donc un pointeur qui contient un objet d'une classe
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
        case PORTE: {
            Porte* porte = new Porte();
            return porte;
        }
        */
        default:
            return nullptr; // Gestion d'erreur si nécessaire
    }
}