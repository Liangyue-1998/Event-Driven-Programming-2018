#ifndef MONSTER_H
#define MONSTER_H
#include <string>

using namespace std;

class Monster
{
public:
    Monster();
    Monster(string desp);
    int getHealthy();
    void setHealthy(int value);
    int getMaxHealthy();
    void setMaxHealty(int value);
    string getDescription();
    void setDescription(string desp);
    string getLongDescription();
    void setLongDescription(string longesp);

private:
    string description;
    string longDescription;
    int healthy, maxHealthy;

};

#endif // MONSTER_H
