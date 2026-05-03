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
	int type; // 1 - Attack, 2 - Defend, 3 - Heal, 
	int energyCost;
public:
	Skill(string name, int type, int energyCost);
	virtual ~Skill() {}
	virtual void useSkill(Room* room) = 0;
	virtual void upgrade() = 0;
	virtual void printInfo() = 0;

	int getEnergyCost() const;
	int getType() const;
	string getName() const;
	virtual int getPower() const = 0;
};


class Attack : public Skill {
private:
	int damage;
public:
	Attack(string name, int type, int energyCost, int damage);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower() const;
};


class Defend : public Skill {
private:
	int absorbedDamage;
public:
	Defend(string name, int type, int energyCost, int absorbedDamage);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower() const;
};


class Heal : public Skill {
private:
	int heal;
public:
	Heal(string name, int type, int energyCost, int heal);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower() const;
};


class Freeze : public Skill {
private:
	int freezeTime;
public:
	Freeze(string name, int type, int energyCost, int freezeTime);
	void useSkill(Room* room);
	void upgrade();
	void printInfo();
	int getPower() const;
};

