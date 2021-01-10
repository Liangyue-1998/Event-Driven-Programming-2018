#include "monster.h"

Monster::Monster()
{
    maxHealthy = 30;
    healthy = 30;
}
Monster::Monster(string desp):Monster(){
    this->description = desp;
}

int Monster::getHealthy() {
    return healthy;
}
void Monster::setHealthy(int value) {
    this->healthy = value;
}
string Monster::getDescription() {
    return this->description;
}
void Monster::setDescription(string desp) {
    this->description = desp;
}
string Monster::getLongDescription() {
    return this->longDescription;
}
void Monster::setLongDescription(string longesp) {
    this->longDescription = longesp;
}

int Monster::getMaxHealthy() {
    return maxHealthy;
}

void Monster::setMaxHealty(int value) {
    maxHealthy = value;
}
