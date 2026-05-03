#include "Room.h"
#include "Hero.h"
#include "Enemy.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

const Enemy ENEMIES[30] =
{
    Enemy("Slime", 10, 2, 1),
    Enemy("Tiny Spider", 12, 3, 2),
    Enemy("Rat", 15, 3, 2),
    Enemy("Goblin", 20, 5, 3),
    Enemy("Skeleton", 25, 6, 4),
    Enemy("Zombie", 35, 5, 4),
    Enemy("Wild Wolf", 30, 7, 5),
    Enemy("Bandit", 40, 8, 6),
    Enemy("Orc", 50, 10, 7),
    Enemy("Dark Mage", 35, 12, 7),

    Enemy("Cave Troll", 80, 12, 9),
    Enemy("Giant Spider", 60, 14, 9),
    Enemy("Fire Imp", 45, 15, 8),
    Enemy("Ice Elemental", 70, 13, 10),
    Enemy("Shadow Assassin", 50, 18, 11),

    Enemy("Ogre", 100, 15, 12),
    Enemy("Warlock", 60, 20, 12),
    Enemy("Stone Golem", 150, 10, 13),
    Enemy("Berserker", 90, 22, 14),
    Enemy("Necromancer", 70, 18, 14),

    Enemy("Wyvern", 120, 20, 15),
    Enemy("Blood Knight", 110, 22, 16),
    Enemy("Lich", 90, 25, 17),
    Enemy("Demon Brute", 160, 18, 17),
    Enemy("Storm Elemental", 130, 24, 18),

    Enemy("Dragon Whelp", 140, 26, 18),
    Enemy("Ancient Guardian", 200, 20, 19),
    Enemy("Void Reaper", 120, 30, 19),
    Enemy("Infernal Beast", 180, 28, 20),
    Enemy("Elder Dragon", 250, 35, 20)
};

Room::Room(int enemiesCount, int roomDifficulty, int exp, Hero* player) : enemiesCount(enemiesCount), roomDifficulty(roomDifficulty), exp(exp), player(player) {
    for (int i = 0; i < enemiesCount; i++)
    {
        Enemy* randomEnemy = new Enemy(ENEMIES[rand() % 30]);
        while (randomEnemy->getDifficulty() > roomDifficulty) {
            delete randomEnemy;
            randomEnemy = new Enemy(ENEMIES[rand() % 30]);
        }
        if (roomDifficulty > 20) {
            randomEnemy->setDamage((roomDifficulty - 10) / 10 * randomEnemy->getDamage());
            randomEnemy->setHP((roomDifficulty - 10) / 10 * randomEnemy->getHP());
        }

        enemies.push_back(randomEnemy);
    }
}

Room::~Room() {
    for (Enemy* e : enemies)
    {
        delete e;
    }
}

// --------- GETTER ---------

Hero* Room::getPlayer() {
    return player;
}
vector<Enemy*> Room::getEnemies() {
    return enemies;
}

// --------- GAME LOGIC ---------

int Room::winner() {
    if (player->getHP() == 0) return 2;
    for (Enemy* e : enemies) {
        if (e->isAlive()) return 0;
    }
    return 1;
}

void Room::printStats() {
    cout << player->getName() << endl;
    cout << "HP: " << player->getHP() << "/" << player->getMaxHP() << " Energy: " << player->getEnergy() << "/" << player->getMaxEnergy() << endl;
    cout << endl << "Enemies:" << endl;
    int i = 1;
    for (Enemy* e : enemies) {
        cout << "[" << i << "] ";
        e->printInfo();
        i++;
    }
}

void Room::fight() {
    player->setHP(player->getMaxHP());
    cout << endl <<"========================================" << endl;
    cout << "            BATTLE START" << endl;
    cout << "========================================" << endl;
    cout << endl;
    do {
        player->update();
        printStats();
        cout << endl << "----------------------------------------" << endl;
        playerTurn();
        cout << endl << "========================================" << endl;
        cout << endl << "Enemies turn..." << endl;
        enemyTurn();
        cout << endl << "========================================" << endl << endl;
    } while (!winner());
    
    if (winner() == 1) {
        cout << "            VICTORY!" << endl << endl;
        cout << "========================================" << endl << endl;
        cout << "Rewards:" << endl;
        cout << "+ " << exp << " XP" << endl;
        player->addExp(exp);
        player->levelUp();
    }

    if (winner() == 2) {    
        cout << "            DEFEAT!" << endl << endl;
        cout << "========================================" << endl;
        exit(0);
    }
}

void Room::playerTurn() { 
    while (true){
        cout << endl << "Choose action:" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Defense" << endl;
        cout << "3. Heal" << endl;
        cout << "4. Freeze" << endl;
        cout << "0. End turn" << endl;
        int action;
        cout << endl;
        do {
            cout << "> ";
            cin >> action;
        } while (action < 0 || action > 4);
        
        cout << "Choose skill: " << endl;
    
        switch (action) {
        case 1:
           player->printSkills(1);
           break;
        case 2:
            player->printSkills(2);
            break;
        case 3:
           player->printSkills(3);
           break;
        case 4:
           player->printSkills(4);
           break;
        case 0:
            cout << endl << "Turn ended." << endl;
            return;
        }
        cout << "[0] Back" << endl;
        do {
            cout << "> ";
            cin >> action;
        } while (action < 0);  
        if (action == 0) {
            continue;
        }
        else {
            player->useSkill(action - 1, this);
            cout << endl << "----------------------------------------" << endl << endl;
            printStats();
            cout << endl << "----------------------------------------" << endl;
        }
    }
}

void Room::enemyTurn() {
    for (Enemy* e : enemies) {
        e->action(player);
        e->update();
    }
}