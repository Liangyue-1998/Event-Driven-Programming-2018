#include "Parser.h"

Parser::Parser() {
	commands = new CommandWords();
}

Command* Parser::getCommand() {
    string inputLine = "";
	string word1;
	string word2;
	string buffer;
	vector<string> words;

    cout << "> ";

    getline(cin, buffer, '\n');
	string::size_type pos = 0, last_pos = 0;


	bool finished = false;
	while (!finished) {
        pos = buffer.find_first_of(' ', last_pos);
        if (pos == string::npos ) {
            words.push_back(buffer.substr(last_pos));
            finished = true;
        } else {
			words.push_back(buffer.substr(last_pos, pos - last_pos));
			last_pos = pos + 1;
		}
	}

    if (words.size() == 1)
        word1 = words[0];
    else if (words.size() >= 2) {
        word1 = words[0];
        word2 = words[1];
	}



	if (commands->isCommand(word1))
		return new Command(word1, word2);
	else
		return new Command("", word2);
}

/**
 * Print out a list of valid command words.
 */
void Parser::showCommands() {
	commands->showAll();
}
