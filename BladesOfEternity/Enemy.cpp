#include "Enemy.h"
#include "Hero.h"
#include <ctime>
#include <cstdlib>
#include <iostream>



Enemy::Enemy(string name, int hp, int dmg, int difficulty) : name(name), hp(hp), dmg(dmg), difficulty(difficulty) {}
Enemy::Enemy(const Enemy& character) {
    name = character.name;
    hp = character.hp;
    dmg = character.dmg;
    freezeTime = character.freezeTime;
    difficulty = character.difficulty;
}

// --------- GETTER ---------

string Enemy::getName() { return name; }
int Enemy::getHP() { return hp; }
int Enemy::getDamage() { return dmg; }
int Enemy::getFreezeTime() { return freezeTime; }
int Enemy::getDifficulty() { return difficulty; }


// --------- SETTER ---------

void Enemy::setHP(int value)
{
    hp = value;
    if (hp < 0) hp = 0;
}
void Enemy::setDamage(int value)
{
    dmg = value;
    if (dmg < 0) dmg = 0;
}
void Enemy::setFreezeTime(int value)
{
    freezeTime = value;
    if (freezeTime < 0) freezeTime = 0;
}

// --------- GAME LOGIC ---------

/*
* isAlive:
* Checks if enemy is alive
* ref: Room -> winner()
*/
bool Enemy::isAlive()
{
    return hp > 0;
}

/*
* damage:
* Damages enemy
* ref: Attack -> useSkill()
*/
void Enemy::damage(int damage)
{
    if (damage < 0) return;

    hp -= damage;

    if (hp < 0)
        hp = 0;
}

/*
* damage:
* Heals enemy
* ref: Enemy -> action()
*/
void Enemy::heal()
{
    hp += dmg;
}

/*
* attack:
* Enemy attacks hero
* ref: Enemy -> action()
*/
void Enemy::attack(Hero* hero) {
    hero->damage(dmg);
}

/*
* freeze:
* Hero freezes enemy
* time - Amount of turns to freeze
* ref: Freeze -> useSkill()
*/
void Enemy::freeze(int time)
{
    if (time <= 0) return;

    freezeTime = time;
}

/*
* update:
* Updates enemy stats every turn
* ref: Room -> enemyTurn()
*/
void Enemy::update()
{
    if (freezeTime > 0)
    {
        freezeTime--;
    }
}

/*
* action:
* Random action of enemy (attack/heal)
* ref: Room -> enemyTurn()
*/
void Enemy::action(Hero* hero) {
    if (!freezeTime && isAlive()) {
        int heal_chance;
        if (hp < 10) heal_chance = 80;
        else heal_chance = 20;

        if (rand() % 101 < heal_chance) {
            heal();
            cout << endl << name << " heals." << endl;
            cout << "HP: " << hp;
        }
        else {
            cout << endl << name << " attacks " << hero->getName() << "!" << endl;
            attack(hero);
            cout << endl;
        }
    }
}

/*
* printInfo:
* Prints stats of enemy
* ref: Room -> printStats()
*/
void Enemy::printInfo() {
    cout << name << " HP: " << hp;
    if (freezeTime && isAlive()) cout << " (Freezed for:" << freezeTime << " turns)";
    if (!isAlive()) cout << " (Dead)";
    cout << endl;
}