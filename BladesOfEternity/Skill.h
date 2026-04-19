#pragma once

#include <string>
using namespace std;

class Room;
class Hero;
class Enemy;

class Skill
{
protected:
	string name;
	int type;
	int energyCost;
public:
	Skill(string name, int type, int energyCost);
	virtual ~Skill() {}
	virtual void useSkill(Room* room) = 0;
	virtual void upgrade() = 0;
	virtual void printInfo() = 0;

	int getEnergyCost();
	int getType();
	string getName();
	virtual int getPower() = 0;
};


class Attack : public Skill {
private:
	int damage;
public:
	Attack(string name, int type, int energyCost, int damage);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower();
};


class Defend : public Skill {
private:
	int absorbedDamage;
public:
	Defend(string name, int type, int energyCost, int absorbedDamage);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower();
};


class Heal : public Skill {
private:
	int heal;
public:
	Heal(string name, int type, int energyCost, int heal);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower();
};


class Freeze : public Skill {
private:
	int freezeTime;
public:
	Freeze(string name, int type, int energyCost, int freezeTime);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower();
};

