#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
using namespace std;
#include <vector>
using std::vector;
#include <weapon.h>
#include "monster.h"

class Character {
private:
	string description;
    vector<Item*> items;
    int healthy;
    int maxHealthy;
public:
    void addItem(Item *item);
    void dropItem(int idx);
    int itemsCount();
    Item* getItem(int pos);
    int getHealthy();
    int getMaxHealthy();
    void setHealthy(int value);
    void attack(Monster* monster);
public:
    Character();
	Character(string description);
	string shortDescription();
	string longDescription();

};

#endif /*CHARACTER_H_*/
