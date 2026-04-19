#pragma once

#include <string>

using namespace std;

class Hero;
class Skill;

class Menu
{
private:
	Hero* player = nullptr;
public:
	void displayMainMenu();
};

