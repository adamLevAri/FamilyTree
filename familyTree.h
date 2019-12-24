#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include"node.h"
#pragma warning(disable:4996)

using namespace std;
class familyTree
{

public:
	node* start;

	familyTree();

	node* traverseDown(node*, string);   // Search functions
	node* traverseRight(node*, string);
	node* search(string);

	void addSib(node*, node*);           // Function for adding new members
	void addChild(node*, node*);         // Function for adding new child
	void addSpo(node*, node*);          // Function for adding new spouse
	void addNew(string, char, char, string);
	void addNew(string, char);


	string find(string, string);                        // Function to find relations b/w 2 indeviduals
	void display(node*);                // Function to display full tree
	void destroy(node*);                // Function to destroy full tree
	string findRelation(string, char);     // Funcion to display person relative
	void show(node*);					//function information about node

	~familyTree();
};

