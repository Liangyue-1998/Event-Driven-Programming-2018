#include "weapon.h"

Weapon::Weapon (string inDescription, int inWeightGrams, float inValue):Item(inDescription, inWeightGrams, inValue) {
    this->type = "weapon";
}

Weapon::Weapon(string inDescription):Item(inDescription) {
    this->type = "weapon";
}

Weapon::Weapon (string description, int power):Weapon(description) {
    this->type = "weapon";
    this->power = power;
}

int Weapon::getPower() {
    return this->power;
}

void Weapon::setPower(int value) {
    this->power = value;
}
