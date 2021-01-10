#ifndef ITEM_H
#define ITEM_H
#include <map>
#include <string>
#include <iostream>
using namespace std;


class Item
{
public:
    Item (string description, int inWeight, float inValue);
    Item (string description);

    string getShortDescription();
    string getLongDescription();
    int getWeight();
    void setWeight(int weightGrams);
    float getValue();
    void setValue(float value);
    string getType();

protected:
    string description;
    string longDescription;
    int weightGrams;
    float value;
    string type;

};

#endif // ITEM_H
