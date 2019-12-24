#pragma once
#include<iostream>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

using namespace std;
class node
{
public:

	string name;
	short int x; // x - height of node
	bool g;             // g- gender
	node* fc;           // Pointer to first child
	node* ns;           // Pointer to next sibiling
	node* ps;           // Pointer to previous sibiling
	node* p;            // Pointer to parent
	node* s;            // Pointer to spouse

	node();
	void setData(string, char);
	~node();
};

