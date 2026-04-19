#pragma once

#include <string>
#include <vector>
using namespace std;

class Hero;
class Enemy;

class Room
{
private:
	int enemiesCount;
	vector<Enemy*> enemies;
	int roomDifficulty;
	int exp;
	Hero* player;
public:
	Room(int enemiesCount, int roomDifficulty, int exp, Hero* player);
	~Room();
    void fight();
    void printStats();
    void playerTurn();
    void enemyTurn();
	int winner();

    Hero* getPlayer();
    vector<Enemy*> getEnemies();
};

