#include "Room.h"
#include "Command.h"


Room::Room(string description) {
	this->description = description;
    this->monster = NULL;
}

void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
	if (north != NULL)
		exits["north"] = north;
	if (east != NULL)
		exits["east"] = east;
	if (south != NULL)
		exits["south"] = south;
	if (west != NULL)
		exits["west"] = west;
}

string Room::shortDescription() {
	return description;
}

string Room::longDescription() {
	return "room = " + description + ".\n" + displayItem() + exitString();
}

string Room::exitString() {
	string returnString = "\nexits =";
	for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
		// Loop through map
        returnString += "  " + i->first;
	return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction);
	if (next == exits.end())
        return NULL;
    return next->second;

}

void Room::addItem(Item *inItem) {

    itemsInRoom.push_back(inItem);
}

string Room::displayItem() {
    string tempString = "items in room = ";
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "no items in room";
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x]->getShortDescription() + "  " ;
            x++;
            }
        }
    return tempString;
    }

int Room::numberOfItems() {
    return itemsInRoom.size();
}

int Room::isItemInRoom(string inString)
{
    int sizeItems = (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return false;
        }
    else if (itemsInRoom.size() > 0) {
       int x = (0);
        for (int n = sizeItems; n > 0; n--) {
            // compare inString with short description
            int tempFlag = inString.compare( itemsInRoom[x]->getShortDescription());
            if (tempFlag == 0) {
                itemsInRoom.erase(itemsInRoom.begin()+x);
                return x;
            }
            x++;
            }
        }
    return -1;
}

Monster* Room::getMonster() {
    return this->monster;
}

void Room::setMonster(Monster* monster) {
    this->monster = monster;
}

Item* Room::getItem(int pos) {
    if(pos<0||pos>=this->itemsInRoom.size()) return NULL;
    return this->itemsInRoom[pos];
}

void Room::removeItemFromRoom(int pos) {
    if(pos<0||pos>=this->itemsInRoom.size()) return;
    this->itemsInRoom.erase(this->itemsInRoom.begin()+pos);
}

