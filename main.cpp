/***********************************************************************
Class: CS202
Assignment: Project03
Author: Boyan Gankov
File: main.cpp
Purpose: To run the menu based UI which allows the user to interact 
		 with the heirarchy. A user can add to, remove from, display
		 and retrieve activities from a binary search tree
***********************************************************************/
#include "dataStructures.h"

void displayMenu();
void displayDevMenu();
char usrChoice(bool dev);
void displayVector(vector <Event*> const &print, unsigned int index);



/***********************************************************************
Description: The driver for the program, runs the menus and facilitates
			 communication between the hierarchy

Parameters: None

Returned: 0
***********************************************************************/
int main() {
	char quit = '0';
	bool dev = 0;
	Event* scheduledPtr = nullptr;
	vector <Event*> scheduledEvents;
	BST tree;

	cout << "\n << Time to pick an animal event >> \n" << endl;

	while(quit != 'q') {
		switch(usrChoice(dev)) {
			case 'v':
				tree.display();
				break;
			case 's':
				try {
					scheduledPtr = tree.retrieve();
					scheduledEvents.push_back(scheduledPtr);
					scheduledPtr = nullptr;
				}
				catch(const char* msg) {
					cerr << msg << endl;
					scheduledPtr = nullptr;
				}
				break;
			case 'l':
				displayVector(scheduledEvents, 0);
				break;
			case 'd':
				dev = 1;
				cout << "Accessing developer module.." << endl;
				while(dev) {
					switch(usrChoice(dev)) {
						case 'a':
							try {
								tree.queryAdd();
							}
							catch(const char* msg) {
								cerr << msg << endl;
								cin.clear();
								cin.ignore(MAX, '\n');
							}
							break;
						case 'r':
							tree.remove();
							break;
						case 'c':
							cout << "Removing all events.." << endl;
							tree.removeAll();
							break;
						case 'b':
							dev = 0;
							cout << "Closing module.." << endl;
							break;
						default:
							cout << "\nUnknown command!\n" << endl;
							break;
					}
				}
				break;
			case 'q':
				quit = 'q';
				break;
			default:
				cout << "\nUnknown command!\n" << endl;
				break;
		}
	}

	cout << "\n << Shutting down.. >>\n" << endl;

	return 0;
}



/***********************************************************************
Description: Displays a menu of options for the user to choose from

Parameters: None

Returned: Nothing
***********************************************************************/
void displayMenu() {
	cout << "______________________________________\n"
	<< "\n\tv: View full event list\n"
	<< "\ts: Schedule an event (Retrieve)\n"
	<< "\tl: List my scheduled events\n"
	<< "\td: Developer Commands\n"
	<< "\tq: Quit\n"
	<< "______________________________________\n" << endl;
}



/***********************************************************************
Description: Displays a menu of options for the user to choose from

Parameters: None

Returned: Nothing
***********************************************************************/
void displayDevMenu() {
	cout << "______________________________________\n"
	<< "\n\ta: Add an event\n"
	<< "\tr: Remove an event\n"
	<< "\tc: Clear all events\n"
	<< "\tb: Back\n"
	<< "______________________________________\n" << endl;
}




/***********************************************************************
Description: Validates a user input for one of the commands listed in
one of the displayMenu functions

Parameters: A bool to determine which display to print

Returned: A char variable for the user input
***********************************************************************/
char usrChoice(bool dev) {
	char uInput;

	if(!dev) displayMenu();
	else displayDevMenu();

	cout << "Please enter a command: ";
	cin >> uInput;
	cout << endl;

	return tolower(uInput);
}



/***********************************************************************
Description: Recursively displays the contents of the vector of 
scheduled events

Parameters: A const Event pointer vector by reference and an unsigned
integer index

Returned: Nothing
***********************************************************************/
void displayVector(vector <Event*> const &print, unsigned int index) {
	if(index < print.size()) cout << *print.at(index) << endl;
	else return;

	++index;
	displayVector(print, index);
}