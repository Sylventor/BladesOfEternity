#include "Hero.h"
#include "Room.h"
#include "Skill.h"
#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

extern const Skill* SKILLS[7];

Hero::Hero(string name, int maxHP, int maxEnergy, vector<Skill*> skills) : name(name), maxHP(maxHP), maxEnergy(maxEnergy), hp(maxHP), energy(maxEnergy), level(0), exp(0), expForLevel(300), absDamage(0), skills(skills) {};

string Hero::getName() { return name; }
int Hero::getHP() { return hp; }
int Hero::getMaxHP() { return maxHP; }
int Hero::getEnergy() { return energy; }
int Hero::getMaxEnergy() { return maxEnergy; }
int Hero::getExp() { return exp; }
int Hero::getExpForLevel() { return expForLevel; }
int Hero::getLevel() { return level; }
int Hero::getAbsDamage() { return absDamage; }

vector<Skill*>& Hero::getSkills() { return skills; }

void Hero::setHP(int value)
{
    hp = value;
    if (hp > maxHP) hp = maxHP;
    if (hp < 0) hp = 0;
}

void Hero::setMaxHP(int value)
{
    maxHP = value;
    if (hp > maxHP) hp = maxHP;
}

void Hero::setEnergy(int value)
{
    energy = value;
    if (energy > maxEnergy) energy = maxEnergy;
    if (energy < 0) energy = 0;
}

void Hero::setMaxEnergy(int value)
{
    maxEnergy = value;
    if (energy > maxEnergy) energy = maxEnergy;
}

void Hero::setExp(int value)
{
    exp = value;
    if (exp < 0) exp = 0;
}

void Hero::setExpForLevel(int value)
{
    expForLevel = value;
    if (expForLevel < 1) expForLevel = 1;
}

void Hero::setAbsDamage(int value) {
    absDamage = value;
    if (absDamage < 0) absDamage = 0;
}


void Hero::useEnergy(int cost) {
    setEnergy(energy-cost);
}

void Hero::damage(int damage) {
    int new_damage = damage-absDamage;
    setAbsDamage(absDamage - damage);
    if (new_damage <= 0) {
        cout << "Attack failed!";
        return;
    }
    cout << "Damage: " << new_damage;
    setHP(getHP() - new_damage);
}

void Hero::heal(int heal) {
    setHP(getHP() + heal);
}

void Hero::addExp(int value) {
    setExp(getExp() + value);
}

void Hero::addSkill(Skill* skill)
{
    if (!skill) return;

    if (skills.size() >= MAXSKILLS)
    {
        std::cout << "Max skills reached!\n";
        return;
    }

    skills.push_back(skill);
}

void Hero::removeSkill(int index)
{
    if (index < 0 || index >= skills.size())
    {
        std::cout << "Invalid index!\n";
        return;
    }

    delete skills[index];
    skills.erase(skills.begin() + index);
}

void Hero::changeSkill(Skill* skill, int index)
{
    if (!skill) return;

    if (index < 0 || index >= skills.size())
    {
        std::cout << "Invalid index!\n";
        return;
    }

    delete skills[index];
    skills[index] = skill;
}

void Hero::levelUp() {
    if (getExp() >= getExpForLevel()) {
        level += 1;
        setExpForLevel(getExpForLevel() + 1000 + level * 100);
        cout << endl << "========================================" << endl;
        cout << "                 Level up!" << endl;
        cout << "========================================" << endl;
        cout << endl << "Choose your upgrade:" << endl;
        cout << endl << "[1] Learn new skill";
        cout << endl << "[2] Upgrade existing skill";
        cout << endl << "[3] Improve stats" << endl;
        int action = 0;
        do {
            cout << endl << "> ";
            cin >> action;
        } while (action < 1 || action > 3);

        if (action == 1) {
            cout << endl << "----------------------------------------" << endl;
            cout << endl << "Choose a new skill: " << endl;

        } else if (action == 2) {
            cout << endl << "----------------------------------------" << endl;
            cout << endl << "Choose skill to upgrade: " << endl;
            int i = 1;
            for (Skill* s : skills) {
                if (s->getType() == 1) {
                    cout << "[" << i << "] " << s->getName() << " (Damage: " << s->getPower() << " -> " << s->getPower() * 1.5 << ")" << endl;
                }
                else if (s->getType() == 2) {
                    cout << "[" << i << "] " << s->getName() << " (Absorbed damage: " << s->getPower() << " -> " << s->getPower() * 2 << ")" << endl;
                }
                else if (s->getType() == 3) {
                    cout << "[" << i << "] " << s->getName() << " (Heal: " << s->getPower() << " -> " << s->getPower() * 1.3 << ")" << endl;
                }
                else if (s->getType() == 4) {
                    cout << "[" << i << "] " << s->getName() << " (Freeze time: " << s->getPower() << " -> " << s->getPower() + 1 << ")" << endl;
                }
            }
            int choise;
            do {
                cout << endl << "> ";
                cin >> choise;
            } while (choise < 1 || choise > skills.size());

            skills[choise - 1]->upgrade();
        }
        else if (action == 3) {
            cout << endl << "----------------------------------------" << endl;
            cout << endl << "Improve your stats: " << endl;
            cout << endl << "[1] +" << level * 3 << "Max HP";
            cout << endl << "[2] +" << level << "Max Energy";

            int choise;
            do {
                cout << endl << "> ";
                cin >> choise;
            } while (choise < 1 || choise > 2);

            setMaxHP(getMaxHP() + level * 3);
            setMaxEnergy(getMaxEnergy() + level);
        }

        return levelUp();
    }
    return;
}

void Hero::useSkill(int index, Room* room) {
    if (index >= 0 && index < skills.size())
    {
        skills[index]->useSkill(room);
    }
}

void Hero::printSkills() {
    int i = 1;
    for (Skill* s : skills) {
        cout << "[" << i << "] ";
        s->printInfo();
    }
}

void Hero::printSkills(int type) {
    int i = 1;
    for (Skill* s : skills) {
        if (s->getType() == type) {
            cout << "[" << i << "] ";
            s->printInfo();
        }
        i++;
    }
}

void Hero::update() {
    setAbsDamage(0);
    setEnergy(maxEnergy);
}

void Hero::newRoom() {
    int enemiesCount = rand() % (level / 2 + 4) + 1;
    int roomDifficulty = level + (rand() % 5 - 2);
    if (roomDifficulty < 1) roomDifficulty = 1;
    currentRoom = new Room(enemiesCount, roomDifficulty, (enemiesCount * roomDifficulty) * 100, this);
    currentRoom->fight();
    delete currentRoom;
}

vector<Skill*> Hero::generateSkills() {
    vector<Skill*> result;
    while (result.size() < 3) {
        int index = rand() % (sizeof(SKILLS) / sizeof(SKILLS[0]));
        
    }

    return result;
}

Hero::~Hero()
{
    for (Skill* skill : skills)
    {
        delete skill;
    }
}
