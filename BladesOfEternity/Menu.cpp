#include "Menu.h"
#include <iostream>
#include "Hero.h"
#include "Skill.h"


const Skill* SKILLS[7] =
{
    new Attack("Power Strike", 1, 5, 15),
    new Attack("Fire Slash", 1, 8, 22),

    new Defend("Iron Shield", 2, 6, 18),
    new Defend("Magic Barrier", 2, 9, 25),

    new Heal("Healing Light", 3, 7, 20),
    new Heal("Regeneration", 3, 10, 30),

    new Freeze("Frost Chains", 4, 20, 1)
};

Hero* HEROES[3] =
{
    new Hero(
        "Kael Stormblade",
        120,
        20,
        std::vector<Skill*>
        {
            new Attack("Power Strike", 1, 5, 15),
            new Defend("Iron Shield", 2, 6, 18),
            new Heal("Healing Light", 3, 7, 20)
        }
    ),

    new Hero(
        "Brakka Ironfist",
        180,
        15,
        std::vector<Skill*>
        {
            new Attack("Power Strike", 1, 5, 15),
            new Defend("Magic Barrier", 2, 9, 25),
            new Heal("Regeneration", 3, 10, 30)
        }
    ),

    new Hero(
        "Lyra Nightwhisper",
        90,
        25,
        std::vector<Skill*>
        {
            new Attack("Fire Slash", 1, 8, 22),
            new Defend("Magic Barrier", 2, 9, 25),
            new Heal("Healing Light", 3, 7, 20)
        }
    )
};

void Menu::displayMainMenu() {
	cout << "========================================" << endl;
	cout << "        Blades of Eternity" << endl;
	cout << "========================================" << endl << endl;
    cout << "[1] 	" << HEROES[0]->getName() << endl
        << "        HP: " << HEROES[0]->getHP() << " Energy: " << HEROES[0]->getEnergy() << endl
        << "        Balanced fighter" << endl << endl

        << "[2] 	" << HEROES[1]->getName() << endl
        << "        HP: " << HEROES[1]->getHP() << " Energy: " << HEROES[1]->getEnergy() << endl
        << "        Tank, high survivability" << endl << endl

        << "[3] 	" << HEROES[2]->getName() << endl
        << "        HP: " << HEROES[2]->getHP() << " Energy: " << HEROES[2]->getEnergy() << endl
        << "        Mage, high damage" << endl << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter hero number: ";
    int choise;
    do {
        cin >> choise;
    } while (choise < 1 || choise > 3);
    
    switch (choise)
    {
    case 1:
        player = HEROES[0];
        break;
    case 2:
        player = HEROES[1];
        break;
    case 3:
        player = HEROES[2];
        break;
    }

    cout << "You choose " << player->getName() << "." << endl;
    while (true) {
        player->newRoom();
    }
}