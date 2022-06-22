#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "ProofNumberSearch.h"
#define MaxCommandLength 50

bool CompareStrings(const char* string, const char* command) {
	int i = 0;
	while (string[i] != '\0' and command[i] != '\0') {
		if (string[i++] != command[i])return false;
	}
	return string[i] == '\0' and command[i] == '\0';
}

int AnotherPlayer(int player) {
	if (player == 1)return 2;
	else return 1;
}

int main()
{
	char command[MaxCommandLength];
	ProofNumberSearch* pns;
	Map* map;
	//std::ofstream plik("plik.txt");
	int n, m, k, player;
	while (std::cin >> command) {
		scanf("%d %d %d %d", &n, &m, &k, &player);
		map = new Map(n, m);
		pns = new ProofNumberSearch(n,m,k,map,player,player);
		bool result = pns->PN();
		delete pns;
		if (result) {
			if (player == 1) {
				printf("FIRST_PLAYER_WINS\n");
				//plik << "FIRST_PLAYER_WINS\n";
			}
			else {
				printf("SECOND_PLAYER_WINS\n");
				//plik << "SECOND_PLAYER_WINS\n";
			}
		}
		else {
			//printf("-------\n");
			pns = new ProofNumberSearch(n, m, k, map, player, AnotherPlayer(player));
			bool result = pns->PN();
			delete pns;
			if (result) {
				if (player == 2) {
					printf("FIRST_PLAYER_WINS\n");
					//plik << "FIRST_PLAYER_WINS\n";
				}
				else {
					printf("SECOND_PLAYER_WINS\n");
					//plik << "SECOND_PLAYER_WINS\n";
				}
			}
			else {
				printf("BOTH_PLAYERS_TIE\n");
				//plik << "BOTH_PLAYERS_TIE\n";
			}
		}
	}
	//plik.close();
	return 0;
}
