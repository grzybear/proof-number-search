#include "Cell.h"

Cell::Cell(Cell* parent, Map* map, int player, bool isOr)
    : proof(1), disproof(1), child(nullptr), parent(parent) {
    this->map = new Map(map);
    this->player = player;
    this->danger = false;
    this->ended = map->IsFull();
    this->isOr = isOr;
    this->children = 0;
    v.x = -1;
    v.y = -1;
}
Cell::~Cell() {
    if (child != nullptr) {
        for (int i = 0; i < children; i++) {
            delete child[i];
        }
        free(child);
    }
    delete map;
}
void Cell::Evaluate(int k) {
    char active = Player(player, isOr);
    int a = map->Value(active, k, v);
    switch (a)
    {
    case -1: //win for active player
        if (isOr)Proof();
        else Disproof();
        break;
    case 1: //danger 1
        danger = true;
        break;
    case 2: //lose for active player
        danger = true;
        if (!isOr)Proof();
        else Disproof();
        break;
    default: //unknown both = 1
        break;
    }
    if (Ended())ended = true;
    /*map->Print();
    printf("\n");*/
}
void Cell::GenerateChildren(int n, int m) {
    char activePlayer = Player(player, isOr);
    if (danger == 1 and v.x != -1 and v.y != -1) {
        map->Set(v.x, v.y, activePlayer);
        children = 1;
        child = (Cell**)malloc(sizeof(Cell*) * children);
        if (child == nullptr)return;
        child[0] = new Cell(this, map, player, !isOr);
        map->Set(v.x, v.y, '0');
    }
    else {
        children = map->Moves();
        child = (Cell**)malloc(sizeof(Cell*) * children);
        if (child == nullptr)return;
        GenerateAllChildren(n, m);
    }
}
void Cell::GenerateAllChildren(int n, int m) {
    char activePlayer = Player(player, isOr);
    int l = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map->IsEmpty(i, j)) {
                map->Set(i, j, activePlayer);
                child[l++] = new Cell(this, map, player, !isOr);
                map->Set(i, j, '0');
            }
        }
    }
}
char Cell::Player(int player, bool myTurn) {
    if (!myTurn)player++;
    if (player > 2)player = 1;
    return '0' + player;
}
void Cell::Proof() {
    proof = 0;
    disproof = max;
}
void Cell::Disproof() {
    proof = max;
    disproof = 0;
}
void Cell::UpdateAncestors() {
    Cell* current = this->parent;
    while (current != nullptr) {
        current->SetProofAndDisproof();
        current = current->parent;
    }
}
bool Cell::IsLeaf() {
    return children == 0;
}
bool Cell::Ended() {
    if (ended or proof == 0 or
        disproof == 0)  return true;
    return false;
}
Cell* Cell::MinProof() {
    int min = max;
    int j = 0;
    for (int i = 0; i < children; i++) {
        if (!child[i]->ended and child[i]->proof < min) {
            min = child[i]->proof;
            j = i;
        }
    }
    return child[j];
}
Cell* Cell::MinDisproof() {
    int min = max;
    int j = 0;
    for (int i = 0; i < children; i++) {
        if (!child[i]->ended and child[i]->disproof < min) {
            min = child[i]->disproof;
            j = i;
        }
    }
    return child[j];
}
Cell* Cell::NextNode() {
    if (isOr)return MinProof();
    else return MinDisproof();
}
void Cell::EvaluateChildren(int k) {
    for (int i = 0; i < children; i++) {
        child[i]->Evaluate(k);
    }
}
void Cell::SetProofAndDisproof() {
    int endedChildren = 0;
    if (isOr) {
        proof = max;
        disproof = 0;
    }
    else {
        proof = 0;
        disproof = max;
    }

    for (int i = 0; i < children; i++) {
        if (isOr) {
            if (child[i]->proof < proof)proof = child[i]->proof;
            disproof += child[i]->disproof;
            if (disproof > max)disproof = max;
        }
        else {
            if (child[i]->disproof < disproof)disproof = child[i]->disproof;
            proof += child[i]->proof;
            if (proof > max)proof = max;
        }
        if (child[i]->Ended())endedChildren++;
    }
    if (endedChildren >= children) {
        this->ended = true;
        this->DeleteChildren();
    }
}
int Cell::CheckStartingPosition(int n, int m, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map->Ended(i, j, k, '1'))return 1;
            if (map->Ended(i, j, k, '2'))return 2;
        }
    }
    return 0;
}
void Cell::DeleteChildren() {
    for (int i = 0; i < children; i++) {
        delete child[i];
    }
    free(child);
    child = nullptr;
}