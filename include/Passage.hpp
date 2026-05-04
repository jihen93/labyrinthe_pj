#pragma once
#include "Case.hpp"

class Passage : public Case { 
public: 
    Passage () = default;
    char afficher() override;
};