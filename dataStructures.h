/***********************************************************************
Class: CS202
Assignment: Project03
Author: Boyan Gankov
File: dataStructures.h
Purpose: Header file for the dataStructures classes (Node and BST)
Defines: Defines and controls each of the classes set in place; 
including a Node and Binary Search Tree classes. The BST
is the data structure which contains many Node objects. 
***********************************************************************/
#include "event.h"



/***********************************************************************

Class: Node

Purpose: Holds information from the Event class strcutre

Contains: Two Node pointers, left and right, as well as an Event pointer

***********************************************************************/
class Node {

	public:
		Node();
		Node(Event* &newEvent);
		~Node();

		Event* getEvent();
		Node* getLeft();
		Node* getRight();
		void setLeft(Node* &newLeft);
		void setRight(Node* &newRight);
		bool compareNode(const Event* compare);
		bool compareName(const char* name);
		void display();

	protected:
		Node* left;
		Node* right;
		Event* event;
};



/***********************************************************************

Class: BST

Purpose: Creates, manipulates, and destroys a binary search tree 
containing Node objects

Contains: A Node pointer which acts as the root of the tree

***********************************************************************/
class BST {

	public:
		BST();
		~BST();

		void build();
		void queryAdd();
		void add(Event* &tempEvent);
		Event* retrieve();
		void remove();
		void removeAll();
		void display();

	protected:
		Node* root;

		void destroy(Node* &currRoot);
		void add(Node* &currRoot, Event* &tempEvent);
		int retrieve(Node* &currRoot, const char* usrIn, Event* &retrieved);
		void remove(Node* &currRoot, Node* &currP, const char* usrIn);
		void display(Node* currRoot, int &currPos) const;
};