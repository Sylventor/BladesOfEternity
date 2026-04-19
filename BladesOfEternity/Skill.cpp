#include "Skill.h"
#include "Room.h"
#include "Hero.h"
#include "Enemy.h"
#include <iostream>

using namespace std;

Skill::Skill(string name, int type, int energyCost) : name(name), type(type), energyCost(energyCost) {};
Attack::Attack(string name, int type, int energyCost, int damage) : Skill(name, type, energyCost), damage(damage) {};
Defend::Defend(string name, int type, int energyCost, int absorbedDamage) : Skill(name, type, energyCost), absorbedDamage(absorbedDamage) {};
Heal::Heal(string name, int type, int energyCost, int heal) : Skill(name, type, energyCost), heal(heal) {};
Freeze::Freeze(string name, int type, int energyCost, int FreezeTime) : Skill(name, type, energyCost), freezeTime(freezeTime) {};


int Skill::getEnergyCost() {
	return energyCost;
}

int Skill::getType() {
	return type;
}

string Skill::getName() {
	return name;
}

int Attack::getPower() {
	return damage;
}
int Defend::getPower() {
	return absorbedDamage;
}
int Heal::getPower() {
	return heal;
}
int Freeze::getPower() {
	return freezeTime;
}

void Attack::printInfo() {
	cout << name << " (Cost: " << energyCost << ", Damage: " << damage << endl;
}
void Defend::printInfo() {
	cout << name << " (Cost: " << energyCost << ", Absorbed damage: " << absorbedDamage << endl;
}
void Heal::printInfo() {
	cout << name << " (Cost: " << energyCost << ", Heal: " << heal << endl;
}
void Freeze::printInfo() {
	cout << name << " (Cost: " << energyCost << ", Freeze time: " << freezeTime << endl;
}

void Attack::upgrade() {
	damage *= 1.5;
}
void Defend::upgrade() {
	absorbedDamage *= 2;
}
void Heal::upgrade() {
	heal *= 1.3;
}
void Freeze::upgrade() {
	freezeTime += 1;
	energyCost *= 1.5;
}

void Attack::useSkill(Room* room) {
	if (room->getPlayer()->getEnergy() < energyCost) {
		cout << endl << "Not enough energy." << endl;
		return;
	}
	cout << endl << "Choose target:" << endl;
	int i = 1;
	for (Enemy* e : room->getEnemies()) {
		cout << "[" << i << "]";
		e->printInfo();
		i++;
	}
	cout << endl << "> ";
	int choise;
	do {
		cin >> choise;
	} while (choise < 1 || choise > i);
	
	room->getEnemies()[choise - 1]->damage(damage);
	cout << endl << "----------------------------------------" << endl;
	cout << room->getPlayer()->getName() << " uses " << name << "!" << endl;
	cout << endl << room->getEnemies()[choise - 1]->getName() << " takes " << damage << " damage!" << endl;
	cout << room->getEnemies()[choise - 1]->getName() << " HP: " << room->getEnemies()[choise - 1]->getHP() << endl;
	room->getPlayer()->useEnergy(energyCost);
}
void Defend::useSkill(Room* room) {
	if (room->getPlayer()->getEnergy() < energyCost) {
		cout << endl << "Not enough energy." << endl;
		return;

	}
	room->getPlayer()->setAbsDamage(room->getPlayer()->getAbsDamage() + absorbedDamage);
	cout << endl << "----------------------------------------" << endl;
	cout << room->getPlayer()->getName() << " uses " << name << "!" << endl;
	cout << room->getPlayer()->getName() << " absorbed damage: " << room->getPlayer()->getAbsDamage() << endl;
	room->getPlayer()->useEnergy(energyCost);
}
void Heal::useSkill(Room* room) {
	if (room->getPlayer()->getEnergy() < energyCost) {
		cout << endl << "Not enough energy." << endl;
		return;
	}
	room->getPlayer()->heal(heal);
	cout << endl << "----------------------------------------" << endl;
	cout << room->getPlayer()->getName() << " uses " << name << "!" << endl;
	cout << room->getPlayer()->getName() << " HP: " << room->getPlayer()->getHP() << endl;
	room->getPlayer()->useEnergy(energyCost);
}
void Freeze::useSkill(Room* room) {
	if (room->getPlayer()->getEnergy() < energyCost) {
		cout << endl << "Not enough energy." << endl;
		return;
	}
	cout << endl << "Choose target:" << endl;
	int i = 1;
	for (Enemy* e : room->getEnemies()) {
		cout << "[" << i << "]";
		e->printInfo();
		i++;
	}
	cout << endl << "> ";
	int choise;
	do {
		cin >> choise;
	} while (choise < 1 || choise > i);

	room->getEnemies()[choise - 1]->freeze(freezeTime);
	cout << endl << "----------------------------------------" << endl;
	cout << room->getPlayer()->getName() << " uses " << name << "!" << endl;
	cout << endl << room->getEnemies()[choise - 1]->getName() << " freezed for " << freezeTime << " turns!" << endl;
	cout << room->getEnemies()[choise - 1]->getName() << " Freeze time: " << room->getEnemies()[choise - 1]->getFreezeTime() << endl;
	room->getPlayer()->useEnergy(energyCost);
}
