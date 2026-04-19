#pragma once

#include <string>
using namespace std;

class Hero;

class Enemy
{
private:
	string name;
	int hp;
	int dmg;
	int freezeTime;
	int difficulty;
public:
	Enemy(string name, int hp, int dmg, int difficulty);
	Enemy(const Enemy& character);
	void update();
	void action(Hero* hero);
	void damage(int damage);
	void freeze(int time);
	void attack(Hero* hero);
	void heal();
	void printInfo();
	
	string getName();
	int getHP();
	int getDamage();
	int getFreezeTime();
	int getDifficulty();
	bool isAlive();

	void setHP(int value);
	void setDamage(int value);
	void setFreezeTime(int value);
};

