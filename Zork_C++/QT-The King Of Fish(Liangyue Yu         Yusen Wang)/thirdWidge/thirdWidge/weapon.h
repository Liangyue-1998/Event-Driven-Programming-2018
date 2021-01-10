#ifndef ITEM_H_
#define ITEM_H_

#include <map>
#include <string>
#include <iostream>
#include "item.h"
using namespace std;

class Weapon :public Item{
private:
    int power;

public:
    Weapon (string description, int inWeight, float inValue);
    Weapon (string description);
    Weapon (string description, int power);
    int getPower();
    void setPower(int value);
};

#endif /*ITEM_H_*/
