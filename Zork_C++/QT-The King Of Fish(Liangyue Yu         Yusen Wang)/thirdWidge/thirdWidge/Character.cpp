#include "Character.h"
#include "monster.h"

Character::Character(){
    description="";
    maxHealthy = 100;
    healthy = 100;
}

Character::Character(string description):Character() {
	this->description = description;
}
void Character::addItem(Item *item) {
    items.push_back(item);
}
void Character::dropItem(int idx) {
    if(idx>=0&&idx<this->items.size()) {
        items.erase(items.begin()+idx);
    }
}
int Character::itemsCount() {
    return items.size();
}

Item* Character::getItem(int pos) {
    if(pos<0||pos>=items.size()) return NULL;
    return items[pos];
}

string Character::longDescription()
{
  string ret = this->description;
  ret += "\n Item list:\n";
  for (vector<Item*>::iterator i = items.begin(); i != items.end(); i++)
    ret += "\t"+ (*i)->getLongDescription() + "\n";
  return ret;
}

int Character::getHealthy() {
    return healthy;
}

void Character::setHealthy(int value) {
    this->healthy = value;
}

int Character::getMaxHealthy() {
    return maxHealthy;
}

void Character::attack(Monster* monster) {

    int weaponPower = 0;
    for(int i=0; i<this->items.size();i++) {
        Item* item = this->items[i];
        if(item->getType()!="weapon") continue;
        Weapon* weapon = (Weapon*)item;
        if(weaponPower < weapon->getPower()) {
            weaponPower = weapon->getPower();
        }
    }

    int a = abs(rand())%5+2+ weaponPower;
    int b = abs(rand())%5+7;
    if(this->healthy-b<0) this->healthy = 0;
    else this->healthy -= b;
    if(monster->getHealthy()-a<0) monster->setHealthy(0);
    else monster->setHealthy(monster->getHealthy()-a);
}
