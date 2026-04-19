#pragma once
#include <string>
#include <vector>

using namespace std;

class Skill;
class Menu;
class Room;

const int MAXSKILLS = 5;

class Hero
{
private:
	string name;
	int hp, maxHP;
	int energy, maxEnergy;
	int level, exp, expForLevel;
	int absDamage;
	vector<Skill*> skills;
	Room* currentRoom;
public:
	Hero(string name, int maxHP, int maxEnergy, vector<Skill*> skills);
	void printSkills();
	void printSkills(int type);
	void addSkill(Skill* skill);
	void removeSkill(int index);
	void changeSkill(Skill* skill, int index);
	void addExp(int value);
	void levelUp();
	void update();
	void newRoom();

	void useSkill(int index, Room* room);
	void damage(int damage);
	void heal(int heal);
	void useEnergy(int cost);

	string getName();
	int getHP();
	int getMaxHP();
	int getEnergy();
	int getMaxEnergy();
	int getExp();
	int getExpForLevel();
	int getLevel();
	int getAbsDamage();
	vector<Skill*>& getSkills();

	void setHP(int value);
	void setMaxHP(int value);
	void setEnergy(int value);
	void setMaxEnergy(int value);
	void setExp(int value);
	void setExpForLevel(int value);
	void setAbsDamage(int value);


	vector<Skill*> generateSkills();

	~Hero();
};

