#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Character.h"
#include "Parser.h"
#include "Room.h"
#include "weapon.h"
#include <iostream>
#include <string>
using namespace std;

class ZorkUL {
private:
    Character player;
	Parser parser;
	Room *currentRoom;
    Room *startRoom;
    Room *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
	void createRooms();
    void goRoom(Command command);
	void printHelp();
    void createItems();
    void displayItems();


public:
	ZorkUL();
    Room* getStartRoom();
    Room* getCurrentRoom();
    Character* getPlayer();
    bool processCommand(Command command);
    bool isGameOver();

    void play();
    void printWelcome();
    void teleportation();
    void initialRoom();
	string go(string direction);
};

#endif /*ZORKUL_H_*/
