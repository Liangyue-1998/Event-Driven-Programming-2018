#include <iostream>
using namespace std;
#include "ZorkUL.h"

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {


    a = new Room("a");
        a->addItem(new Weapon("Axe", 5));
    b = new Room("b");
        b->addItem(new Weapon("ShortGun", 10));
	c = new Room("c");
	d = new Room("d");
        d->addItem(new Weapon("Bow", 4));
	e = new Room("e");
	f = new Room("f");
	g = new Room("g");
	h = new Room("h");
        h->addItem(new Weapon("Sword", 6));
    i = new Room("i");
    j = new Room("j");

//             (N, E, S, W)
	a->setExits(f, b, d, c);
    b->setExits(NULL, j, NULL, a);
	c->setExits(NULL, a, NULL, NULL);
	d->setExits(a, e, NULL, i);
	e->setExits(NULL, NULL, NULL, d);
	f->setExits(NULL, g, a, h);
	g->setExits(NULL, NULL, NULL, f);
	h->setExits(NULL, f, NULL, NULL);
    i->setExits(NULL, d, NULL, NULL);
    j->setExits(NULL, NULL,NULL, b);
    currentRoom = j;
    startRoom =j;

    i->setMonster(new Monster());
    f->setMonster(new Monster());
    g->setMonster(new Monster());
}

void ZorkUL::play() {
	printWelcome();

	bool finished = false;
	while (!finished) {

		Command* command = parser.getCommand();

		finished = processCommand(*command);

		delete command;
    }
	cout << endl;
	cout << "end" << endl;
}

void ZorkUL::printWelcome() {
	cout << "start"<< endl;
	cout << "info for help"<< endl;
	cout << endl;
	cout << currentRoom->longDescription() << endl;
}


bool ZorkUL::processCommand(Command command) {
	if (command.isUnknown()) {
		cout << "invalid input"<< endl;
		return false;
	}

	string commandWord = command.getCommandWord();
	if (commandWord.compare("info") == 0)
		printHelp();
    else if (commandWord.compare("teleport") == 0)
        goRoom(command);
    else if (commandWord.compare("quit") == 0)
        goRoom(command);
	else if (commandWord.compare("map") == 0)
		{
        cout << "[h] --- [f] --- [g]" << endl;
		cout << "         |         " << endl;
        cout << "         |         " << endl;
        cout << "[c] --- [a] --- [b] --- [j]" << endl;
		cout << "         |         " << endl;
		cout << "         |         " << endl;
		cout << "[i] --- [d] --- [e]" << endl;
		}

	else if (commandWord.compare("go") == 0)
		goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
       	if (!command.hasSecondWord()) {
            cout << "incomplete input"<< endl;
        }
        else if (command.hasSecondWord()) {
            int idx = atoi(command.getSecondWord().c_str());
            Item* item = getCurrentRoom()->getItem(idx);
            getCurrentRoom()->removeItemFromRoom(idx);
            getPlayer()->addItem(item);

        }
    }
    else if (commandWord.compare("put") == 0)
    {
        if (!command.hasSecondWord()) {
            cout << "incomplete input"<< endl;
        }else{
            int idx = atoi(command.getSecondWord().c_str());
            Item* item =  getPlayer()->getItem(idx);
            getPlayer()->dropItem(idx);
            getCurrentRoom()->addItem(item);
        }
    }
    else if (commandWord.compare("attack") == 0)
    {
        Monster* monster = getCurrentRoom()->getMonster();
        if(monster!=NULL) {
            getPlayer()->attack(monster);
            if(monster->getHealthy()==0) {
                getCurrentRoom()->setMonster(NULL);
                delete monster;
            }
        }
    }

	return false;
}
/** COMMANDS **/
void ZorkUL::printHelp() {
	cout << "valid inputs are; " << endl;
	parser.showCommands();

}
void ZorkUL::teleportation()
{

        int number = (rand() % 10) + 1;
        switch(number){
        case 1: currentRoom = a;
            break;
        case 2: currentRoom= b;
            break;
        case 3: currentRoom= c;
            break;
        case 4: currentRoom = d;
            break;
        case 5: currentRoom= e;break;
        case 6: currentRoom= f;break;
        case 7: currentRoom= g;break;
        case 8: currentRoom= h;break;
        case 9: currentRoom= i;break;
        case 10: currentRoom= j;break;
        }
         cout << currentRoom->longDescription() << endl;

}
void ZorkUL::initialRoom(){
    currentRoom = j;
}


void ZorkUL::goRoom(Command command) {
    if(command.getCommandWord() == "teleport"){
        ZorkUL::teleportation();
    }
    if(command.getCommandWord() == "quit"){
        ZorkUL::initialRoom();

    }
    else if (!command.hasSecondWord()) {
		cout << "incomplete input"<< endl;
		return;
	}

	string direction = command.getSecondWord();

	// Try to leave current room.
	Room* nextRoom = currentRoom->nextRoom(direction);

	if (nextRoom == NULL)
		cout << "underdefined input"<< endl;
	else {
		currentRoom = nextRoom;
		cout << currentRoom->longDescription() << endl;
	}
}


string ZorkUL::go(string direction) {

	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
		return currentRoom->longDescription();
	}
}

Room* ZorkUL::getStartRoom(){
    return this->startRoom;
    //currentRoom = startRoom
}

Room* ZorkUL::getCurrentRoom() {
    return this->currentRoom;
}

Character* ZorkUL::getPlayer(){
    return &this->player;
}

bool ZorkUL::isGameOver() {
    return i->getMonster()==NULL&&f->getMonster()==NULL&&g->getMonster()==NULL;
}


