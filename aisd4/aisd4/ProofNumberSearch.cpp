#include "ProofNumberSearch.h"

ProofNumberSearch::ProofNumberSearch(int n, int m, int k, Map* map, int startingPlayer, int player)
    :n(n), m(m), k(k) {
    root = new Cell(nullptr, map, player, player == startingPlayer);
    this->player = player;
}
ProofNumberSearch::~ProofNumberSearch() {
    delete root;
}
int ProofNumberSearch::PN() {
    {
        int firstCheck = root->CheckStartingPosition(n, m, k);
        if (firstCheck > 0)return firstCheck == player;
    }
    root->Evaluate(k);
    if (root->Ended())return root->proof == 0;
    root->GenerateChildren(n, m);
    root->EvaluateChildren(k);
    Cell* mostProvidingNode;
    while (!root->Ended()) {
        mostProvidingNode = MostProvidingNode();
        mostProvidingNode->GenerateChildren(n, m);
        mostProvidingNode->EvaluateChildren(k);
        mostProvidingNode->UpdateAncestors();
    }
    return root->proof == 0;
}
Cell* ProofNumberSearch::MostProvidingNode() {
    Cell* current = root;
    while (!current->IsLeaf()) {
        current = current->NextNode();
    }
    return current;
}
