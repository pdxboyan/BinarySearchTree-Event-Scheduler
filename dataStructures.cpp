/***********************************************************************
Class: CS202
Assignment: Project03
Author: Boyan Gankov
File: dataStructures.cpp
Purpose: Implementation file for the dataStructures classes (Node and BST)
Contains: Functions to manipulate and define a Node and Binary Search tree 
classes. Some functionality includes adding, removing, retrieving, and 
displaying nodes containing event pointers.
***********************************************************************/
#include "dataStructures.h"



/***********************************************************************
Description: Constructs an empty Node object

Parameters: None

Returned: Nothing
***********************************************************************/
Node::Node() : left(nullptr), right(nullptr), event(nullptr) {}



/***********************************************************************
Description: Constructs a Node object with a new Event to point to

Parameters: An Event pointer by reference

Returned: Nothing
***********************************************************************/
Node::Node(Event* &newEvent) {
	left = nullptr;
	right = nullptr;
	event = newEvent;
}



/***********************************************************************
Description: Destructs a Node object and frees memory allocated for it's
respecitve Event object

Parameters: None

Returned: Nothing
***********************************************************************/
Node::~Node() {
	if(event) delete event;
}




/***********************************************************************
Description: Gets an event's name

Parameters: None

Returned: A const char name
***********************************************************************/
const char* Node::getName() {
	return this->event->getName();
}



/***********************************************************************
Description: Returns an event

Parameters: None

Returned: An event
***********************************************************************/
Event* Node::getEvent() {
	return event;
}


/***********************************************************************
Description: Gets the current Node object's left pointer

Parameters: None

Returned: A left Node pointer
***********************************************************************/
Node* Node::getLeft() {
	return left;
}



/***********************************************************************
Description: Gets the current Node object's right pointer

Parameters: None

Returned: A right Node pointer
***********************************************************************/
Node* Node::getRight() {
	return right;
}



/***********************************************************************
Description: Sets the current Node object's left Node pointer

Parameters: A Node pointer by reference

Returned: Nothing
***********************************************************************/
void Node::setLeft(Node* &newLeft) {
	left = newLeft;
}



/***********************************************************************
Description: Sets the current Node object's right Node pointer

Parameters: A Node pointer by reference

Returned: Nothing
***********************************************************************/
void Node::setRight(Node* &newRight) {
	right = newRight;
}



/***********************************************************************
Description: Compares two Node object's events using overloaded operators

Parameters: An event to compare

Returned: True or false - (Passed in value is smaller = true)
***********************************************************************/
int Node::compareNode(const Event* compare) {
	if(*this->event > *compare) return 1;
	return 0;
}



/***********************************************************************
Description: Checks if the passed name is equal to the Event's name,
calls the Event compareName function

Parameters: String by reference

Returned: True or false
***********************************************************************/
int Node::compareName(const char* name) {
	if(event->compareName(name) == 1) return 1;
	return 0;
}



/***********************************************************************
Description: Calls the overloaded display function for an Event object

Parameters: None

Returned: Nothing
***********************************************************************/
void Node::display() {
	cout << *event;
}




//___________________________________________________________________________________________________________________________________
//___________________________________________________________________________________________________________________________________




/***********************************************************************
Description: Constructs an empty tree

Parameters: None

Returned: Nothing
***********************************************************************/
BST::BST() : root(nullptr) {}



/***********************************************************************
Description: Destructor for a BST object, calls the recursive destroy 
function.

Parameters: None

Returned: Nothing
***********************************************************************/
BST::~BST() {
	destroy(this->root);
}



/***********************************************************************
Description: Recursively frees the memory allocated for each of the 
nodes in the tree

Parameters: The root of the tree by reference

Returned: Nothing
***********************************************************************/
void BST::destroy(Node* currRoot) {
    if (currRoot) {
        destroy(currRoot->getLeft());
        destroy(currRoot->getRight());
        delete currRoot;
    }
}



/***********************************************************************
Description: Takes and validates user input for a desired event to be
added to the tree

Parameters: None

Returned: Nothing
***********************************************************************/
void BST::queryAdd() {
	int usrIndex;
	Safari tempSafari;
	Aviary tempAviary;
	PetZoo tempPetZoo;
	Event* ptr;

	cout << "What kind of Event would you like to add?\n"
	<< "1.) Safari\n"
	<< "2.) Aviary\n"
	<< "3.) Petting Zoo\n" << endl;

	cout << "Please enter an index number: ";
	cin >> usrIndex;
	if(!cin) throw "\nCannot cast type char as type int";

	while(usrIndex < 1 || usrIndex > 3) {
		cout << "\nUnknown index!" << endl;

		cout << "Please enter an index number: ";
		cin >> usrIndex;
		if(!cin) throw "\nCannot cast type char as type int";
	}

	if(usrIndex == 1) {
		cin >> tempSafari;
		ptr = new Safari(tempSafari);
	}

	else if(usrIndex == 2) {
		cin >> tempAviary;
		ptr = new Aviary(tempAviary);
	}
	
	else {
		cin >> tempPetZoo;
		ptr = new PetZoo(tempPetZoo);
	}

	add(this->root, ptr);
}



/***********************************************************************
Description: Wrapper function for the recursive add function for the 
tree

Parameters: An Event pointer by reference to be added into the tree

Returned: Nothing
***********************************************************************/
void BST::add(Event* &tempEvent) {
	add(this->root, tempEvent);
}



/***********************************************************************
Description: Recursive add function to add new Nodes with Events into 
the tree

Parameters: A Node pointer by reference for the current root and an Event
pointer by reference to be added into the tree

Returned: Nothing
***********************************************************************/
void BST::add(Node* &currRoot, Event* &tempEvent) {
	Node* tempLeft;
	Node* tempRight;

	if(!currRoot) {
		currRoot = new Node(tempEvent);
		return;
	}
	if(currRoot->compareNode(tempEvent) == 1) {
		tempLeft = currRoot->getLeft();
		add(tempLeft, tempEvent);
		currRoot->setLeft(tempLeft);
	}
	
	else {
		tempRight = currRoot->getRight();
		add(tempRight, tempEvent);
		currRoot->setRight(tempRight);
	}
	
}



/***********************************************************************
Description: Wrapper function for the recursive retrieve function to 
find a node in the tree with a matching name

Parameters: None

Returned: An Event pointer
***********************************************************************/
Event* BST::retrieve() {
	char usrIn[MAX];
	Event* retrieved = nullptr;

	cin.ignore(MAX, '\n');
	cout << "What is the name of the event you would like to schedule? ";
	cin.get(usrIn, MAX, '\n');
	cin.ignore(MAX, '\n');

	if(retrieve(this->root, usrIn, retrieved) == 1) {
		return retrieved;
	}
	else throw "\nNo event found!";
}



/***********************************************************************
Description: Recursive retrieve function 

Parameters: Node pointer for the current root and a user input string by 
reference

Returned: An Event pointed
***********************************************************************/
int BST::retrieve(Node* currRoot, const char* usrIn, Event* &retrieved) {
    if (currRoot == nullptr) {
        return 0; // Node not found
    }

    int comparison = currRoot->compareName(usrIn);

    if (comparison == 0) {
        retrieved = currRoot->getEvent();
        return 1; // Node found
    } else if (comparison < 0) {
        return retrieve(currRoot->getLeft(), usrIn, retrieved);
    } else {
        return retrieve(currRoot->getRight(), usrIn, retrieved);
    }
}



/***********************************************************************
Description: Wrapper function for the recursive remove function to 
remove one node in the tree

Parameters: None

Returned: Nothing
***********************************************************************/
void BST::remove() {
	char usrIn[MAX];

	cin.ignore(MAX, '\n');
	cout << "What is the name of the event you would like to remove? ";
	cin.get(usrIn, MAX, '\n');
	cin.ignore(MAX, '\n');

	remove(this->root, this->root, usrIn);
}



/***********************************************************************
Description: Recursive remove function which removes one node from the 
tree specified by name from the user

Parameters: A Node pointer to the current root by reference, a Node
pointer to the current parent by reference, and a constant char array

Returned: Nothing
***********************************************************************/
void BST::remove(Node* &currRoot, Node* &currP, const char* usrIn) {
    Node* tempLeft;
    Node* tempRight;
    Node* tempP;

    if (currRoot) {
        tempP = currRoot;
        tempLeft = currRoot->getLeft();
        remove(tempLeft, tempP, usrIn);

        if (currRoot->compareName(usrIn) == 0) {
            tempLeft = currRoot->getLeft();
            tempRight = currRoot->getRight();

            if (tempLeft && tempRight) {
                Node* successor = findMin(tempRight);
                currRoot = successor;
                remove(tempRight, currRoot, successor->getName());
            } else {
                if (currP) {
                    Node* temp = currRoot;
                    currRoot = (tempLeft) ? tempLeft : tempRight;
                    delete temp;
                } else {
                    // If currP is null, it means currRoot is the root of the tree
                    delete currRoot;
                    currRoot = nullptr;
                }
            }
            return;
        }

        tempP = currRoot;
        tempRight = currRoot->getRight();
        remove(tempRight, tempP, usrIn);
    }
}



/***********************************************************************
Description: Private function which finds the min value of the tree
for the recursive remove

Parameters: A node pointer to the current root

Returned: A node pointer to the current root
***********************************************************************/
Node* BST::findMin(Node* currRoot) {
    while (currRoot->getLeft()) {
        currRoot = currRoot->getLeft();
    }
    return currRoot;
}



/***********************************************************************
Description: Wrapper function for the recursive destroy function to 
remove all of the nodes

Parameters: None

Returned: Nothing
***********************************************************************/
void BST::removeAll() {
	destroy(this->root);
}



/***********************************************************************
Description: Wrapper function for the recursive display function for the
tree

Parameters: None

Returned: Nothing
***********************************************************************/
void BST::display() {
	int pos = 1;
	display(root, pos);
}



/***********************************************************************
Description: Recursive display function 

Parameters: Node pointer for the current root and an int position by 
reference

Returned: Nothing
***********************************************************************/
void BST::display(Node* currRoot, int &currPos) const {
	Node* temp;

	if(currRoot) {
		temp = currRoot->getLeft();
		display(temp, currPos);
		cout << currPos << ". ";
		currRoot->display();
		++currPos;
		temp = currRoot->getRight();
		display(temp, currPos);
	} 
}