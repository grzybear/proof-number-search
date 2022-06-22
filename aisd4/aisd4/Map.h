#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

struct Vector {
	int x, y;
};
class Map
{
private:
	int x, y;
	char** tiles;
	bool LineCheck(int i, int j, int k, char player, Vector v);
	void SetVertical(int& a, int& b, Vector& v, int i, int j, int k);
	void SetHorizontal(int& a, int& b, Vector& v, int i, int j, int k);
	void SetRightDiag(int& a, int& b, Vector& v, int i, int j, int k);
	void SetLeftDiag(int& a, int& b, Vector& v, int i, int j, int k);
public:
	Map(int x, int y);
	Map(Map* map);
	~Map();
	char& Get(int i, int j);
	void Print();
	//char Ended(int i, int j, int k);
	bool OnMap(int i, int j);
	bool IsEmpty(int i, int j);
	int Value(char activePlayer, int k, Vector& v);
	bool IsFull();
	void Set(int i, int j, char a);
	bool Ended(int i, int j, int k, char player);
	int Moves();
	bool Ended(int k);
};

