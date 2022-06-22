#pragma once
#include "Cell.h"
class ProofNumberSearch
{
private:
    Cell* root;
    int n, m, k, player;
public:
    ProofNumberSearch(int n, int m, int k, Map* map, int startingPlayer, int player);
    ~ProofNumberSearch();
    int PN();
    Cell* MostProvidingNode();
};

