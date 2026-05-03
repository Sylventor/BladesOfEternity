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


// --------- GAME LOGIC ---------

bool Enemy::isAlive()
{
    return hp > 0;
}

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

void Enemy::damage(int damage)
{
    if (damage < 0) return;

    hp -= damage;

    if (hp < 0)
        hp = 0;
}

void Enemy::heal()
{
    hp += dmg;
}

void Enemy::attack(Hero* hero) {
    hero->damage(dmg);
}

void Enemy::freeze(int time)
{
    if (time <= 0) return;

    freezeTime = time;
}

void Enemy::update()
{
    if (freezeTime > 0)
    {
        freezeTime--;
    }
}

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

void Enemy::printInfo() {
    cout << name << " HP: " << hp;
    if (freezeTime && isAlive()) cout << " (Freezed for:" << freezeTime << " turns)";
    if (!isAlive()) cout << " (Dead)";
    cout << endl;
}