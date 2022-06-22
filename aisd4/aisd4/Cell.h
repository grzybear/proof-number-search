#pragma once
#include "Map.h"
#define max 500
class Cell
{
private:
    Cell** child;
    Cell* parent;
    Map* map;
    bool danger, isOr;
    Vector v;
    int children;
    bool ended;
public:
    int proof, disproof, player;
    Cell(Cell* parent, Map* map, int player, bool isOr);
    ~Cell();
    void Evaluate(int k);
    void GenerateChildren(int n, int m);
    void GenerateAllChildren(int n, int m);
    char Player(int player, bool myTurn);
    void Proof();
    void Disproof();
    void UpdateAncestors();
    bool IsLeaf();
    bool Ended();
    Cell* MinProof();
    Cell* MinDisproof();
    Cell* NextNode();
    void EvaluateChildren(int k);
    void SetProofAndDisproof();
    int CheckStartingPosition(int n, int m, int k);
    void DeleteChildren();
};