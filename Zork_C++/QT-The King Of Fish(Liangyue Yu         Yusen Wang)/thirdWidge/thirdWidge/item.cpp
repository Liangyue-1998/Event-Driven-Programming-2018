#include "item.h"

Item::Item (string inDescription, int inWeightGrams, float inValue/**, int weaponCheck*/) {
    description = inDescription;
    setWeight(inWeightGrams);
    value = inValue;
}

Item::Item(string inDescription) {
    description = inDescription;
}


void Item::setWeight(int inWeightGrams)
{
    if (inWeightGrams > 9999 || inWeightGrams < 0)
       cout << "weight invalid, must be 0<weight<9999" ;
    else
       weightGrams = inWeightGrams;
}

void Item::setValue(float inValue)
{
    if (inValue > 9999 || inValue < 0)
       cout << "value invalid, must be 0<value<9999" ;
    else
       value = inValue;
}

string Item::getShortDescription()
{
    return description;
}

string Item::getLongDescription()
{
    return " item(s), " + description + ".\n";
}
string Item::getType() {
    return this->type;
}
