class CaseFactory {
public :
    static void creerCase(TypeCase t) {
        switch(t) {
            case MUR :
                Mur mur;
                Mur *pstr_mur = &mur;
                //int *m = new_int;
                //*m = mur; // la valeur de m prend la case mur
            case MONSTRE :
                Monstre monstre;
                Monstre *pstr_monstre = &monstre;
            case PIEGE :
                Piege piege;
                Piege *pstr_piege = &piege;
            case TRESOR :
                Tresor tresor;
                Tresor *pstr_tresor = &tresor;
            case PASSAGE :
                Passage passage;
                Passage *pstr_passage = &passage;
        }
    };
};

enum TypeCase {
    MUR,
    MONSTRE,
    PIEGE,
    TRESOR,
    PASSAGE,
    SOL,
    PORTE
};

class CaseFactory {
public:
    static void* creerCase(TypeCase t) {
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
            case SOL: {
                Sol* sol = new Sol();
                return sol;
            }
            case PORTE: {
                Porte* porte = new Porte();
                return porte;
            }
            default:
                return nullptr; // Gestion d'erreur si nécessaire
        }
    }
};