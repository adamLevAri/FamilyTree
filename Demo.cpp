#include "pch.h"
#include<iostream>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)

using namespace std;

struct node
{
	char name[50];
	short int x; // x - height of node
	bool g;             // g- gender
	node* fc;           // Pointer to first child
	node* ns;           // Pointer to next sibiling
	node* ps;           // Pointer to previous sibiling
	node* p;            // Pointer to parent
	node* s;            // Pointer to spouse

	node();
	void setData(char[] , char);
};

node::node()
{
	fc = ns = ps = p = s = NULL;
	g = 0;
	strcpy(name, "");
	x = 0;
}

void node::setData(char personName[50],char gender)
{
	strcpy(name, personName);
	if (gender == 'm' || gender == 'M')
		g = 1;
}

class familyTree
{

public:

	node* start;

	familyTree();

	node* traverseDown(node*, char[]);   // Search functions
	node* traverseRight(node*, char[]);
	node* search(char[]);

	void addSib(node*, node*);           // Function for adding new members
	void addChild(node*, node*);         // Function for adding new child
	void addSpo(node*, node*);          // Function for adding new spouse
	void addNew(node * , char, node*);
	
	void find(node*, node*);                        // Function to find relations b/w 2 indeviduals
	void display(node*);                // Function to display full tree
	void destroy(node*);                // Function to destroy full tree
	void findRelation(node*, char);     // Funcion to display person relative
	void show(node*);					//function information about node

};

familyTree::familyTree()
{
	start = NULL;
}

void familyTree::destroy(node* ptr)
{
	node* temp = ptr;

	if (ptr == NULL)
		return;

	while (ptr != NULL)
	{
		destroy(ptr->fc);
		temp = ptr;
		ptr = ptr->ns;
		delete temp;
	}

	start = NULL;
}

void familyTree::show(node* ptr)
{
	char g[10];
	strcpy(g, "Female");
	if (ptr->g)
		strcpy(g, "Male");
	cout << "\n\nName: " << ptr->name << endl;
	cout << "Gender: " << g << endl;
	if (ptr->s != NULL)
		cout << "Married to: " << ptr->s->name << endl;
}

void familyTree::display(node* ptr)
{
	// Traverses the full n-array tree by recursion to display names of all people

	if (ptr == NULL)
		return;

	while (ptr != NULL)
	{
		for (int i = 0; i < ptr->x; i++) { cout << "\t"; }

		if (ptr->s != NULL)
			cout << ptr->name << "&" << ptr->s->name << endl;
		else
			cout << ptr->name << endl;
		display(ptr->fc);

		ptr = ptr->ns;
	}
}

void familyTree::find(node* name1, node* name2)
{

	/*
		Same hight: Sibiling if same parent, or married else cousin
		Difference of height = 1 - Parent if immediate, else uncule/aunt
		Difference oh height = 2 - Grand parents if same link, else idk
	*/
	node* ptr1 = search(name1->name);
	node* ptr2 = search(name2->name);
	
	if (ptr1 == NULL || ptr2 == NULL)
	{
		cout << "no sutch person";
		return;
	}

	node* ptr;
	node* ptrk = ptr1;
	node* ptrk1 = ptr2;

	switch (ptr1->x - ptr2->x)
	{

	case 0:
		char s[50];
		strcpy(s, "wife");
		if (ptr1->g)
			strcpy(s, "husband");

		ptr = ptr1->s;
		if ((ptr != NULL) && (ptr == ptr2))
		{
			cout << endl << name1->name << " is " << name2->name << "'s " << s << endl;
			return;
		}

		strcpy(s, "sister");
		if (ptr1->g)
			strcpy(s, "brother");

		ptr = ptr1;
		while (ptr != NULL)
		{
			if (ptr == ptr2)
			{
				cout << endl << name1->name << " is " << name2->name << "'s " << s << endl;
				return;
			}
			ptr = ptr->ns;
		}
		ptr = ptr2;
		while (ptr != NULL)
		{
			if (ptr == ptr1)
			{
				cout << endl << name1->name << " is " << name2->name << "'s " << s << endl;
				return;
			}
			ptr = ptr->ns;
		}
		cout << endl << name1->name << " and " << name2->name << " are Cousins";
		break;

	case 1:
		char str3[50];
		strcpy(str3, "daughter");
		if (ptr1->g)
			strcpy(str3, "son");
		ptr2 = ptr2->fc;
		while (ptr2 != NULL)
		{
			if (ptr2 == ptr1)
			{
				cout << endl << name1->name << " is " << name2->name << "'s " << str3;
				return;
			}
			ptr2 = ptr2->ns;
		}
		strcpy(str3, "niece");
		if (ptr1->g)
			strcpy(str3, "nephew");
		cout << endl << name1->name << " is " << name2->name << "'s " << str3;
		break;
	case -1:
		char str[10];
		strcpy(str, "mother");
		if (ptrk->g)
			strcpy(str, "father");

		ptr = ptrk->fc;
		while (ptr != NULL)
		{
			if (ptr == ptrk1)
			{
				cout << endl << name1->name << " is " << name2->name << "'s " << str;
				return;
			}
			ptr = ptr->ns;
		}
		strcpy(str, "aunt");
		if (ptrk->g)
			strcpy(str, "uncule");
		cout << endl << name1->name << " is " << name2->name << "'s " << str;
		break;

	case 2:
		char str1[50];
		strcpy(str1, "daughter");
		if (ptr2->g)
			strcpy(str1, "son");
		ptr2 = ptr1->p->p;

		if (ptr2->name == ptr1->p->p->name)
		{
			cout << endl << name1->name << " is grand " << str1 << " of " << name2->name;
			return;
		}
		while (ptr2 != NULL)
		{
			if (ptr2 == ptr1)
			{
				cout << endl << name1->name << " is grand " << str1 << " of " << name2->name;
				return;
			}
			ptr2 = ptr2->ns;
		}
		break;
	case -2:
		char str2[50];
		strcpy(str2, "mother");

		if (ptr1->g)
			strcpy(str2, "father");
		
		if (ptr1->name == ptr2->p->p->name)
		{
			cout << endl << name1->name << " is grand " << str2 << " of " << name2->name;
			return;
		}
		//ptr1 = ptr1->fc->fc;

		while (ptr1 != NULL)
		{
			if (ptr1 == ptr2)
			{
				cout << endl << name1->name << " is grand " << str2 << " of " << name2->name;
				return;
			}
			ptr1 = ptr1->ns;
		}

		break;
	default:
		cout << "Too far relationship";
		break;
	}
}

void familyTree::findRelation(node* ptr, char r)
{
	node* ptrk;

	switch (r) {
		//Wife relation
	case 'W':
	case 'w':
		cout << ptr->name << " is married to " << ptr->s->name << endl;
		break;

		//Parent relation
	case 'f':
	case 'F':
	case 'M':
	case 'm':
		if (ptr->p != NULL)
			cout << ptr->p->name << endl;
		else
			cout << "God" << endl;
		break;

		//Cousin relation
	case 'C':
	case 'c':
		ptrk = ptr;
		while (ptrk->ps != NULL)
			ptrk = ptrk->ps;
		if (ptrk->p->ns->fc != NULL)
			cout << ptr->name << "'s cousin is " << ptrk->p->ns->fc->name << endl;
		else
			cout << "No cousin was found.";
		break;

		//Uncle or Aunt relation
	case 'U':
	case 'u':
	case 'A':
	case 'a':
		while (ptr->ps != NULL)
			ptr = ptr->ps;
		ptr = ptr->p;

		//we check both parents side for uncle/aunt - right side.
		if (ptr->ns != NULL)
			cout << ptr->ns->name << endl;
		else if (ptr->s->ns != NULL)
			cout << ptr->s->ns->name << endl;
		//we check both parents side for uncle/aunt - left side.
		else if (ptr->ps != NULL)
			cout << ptr->ps->name << endl;
		else if (ptr->s->ps != NULL)
			cout << ptr->s->ps->name << endl;
		else
			cout << "No uncle or aunt were found." << endl;
		break;

		//Grandparent relation
	case 'G':
	case 'g':
		if (ptr->p->p != NULL)
			//ptr = ptr->p;
			cout << ptr->p->p->name << endl;
		break;

		//Sibling relation
	case 'S':
	case 's':
		char s[50];
		strcpy(s, "sister");
		if (ptr->g)
			strcpy(s, "brother");

		if (ptr->ns != NULL)
			cout << endl << ptr->ns->name << " is " << ptr->name << "'s " << s << endl;
		else if (ptr->ps != NULL)
			cout << endl << ptr->ps->name << " is " << ptr->name << "'s " << s << endl;
		else
			cout << "No sibling was found.";
		break;

	default:
		cout << "NO SUCH REALTION.";
		break;
	}
}

node* familyTree::search(char s[50])
{
	/*
		Searches for the given name from start to it's sibilings and their children
		Returns the pointer of node where the name is present
	*/

	node *ptr = start;

	if (strcmp(ptr->name, s) == 0)
		return ptr;
	else if ((ptr->s != NULL) && (strcmp(ptr->s->name, s) == 0))
		return ptr->s;
	else if (traverseRight(start, s) != NULL)
		return traverseRight(start, s);
	else if (traverseDown(start, s) != NULL)
		return traverseDown(start, s);
	else
	{
		return NULL;
	}
}

node* familyTree::traverseDown(node* ptr, char s[50])
{
	// Searches all the children

	ptr = ptr->fc;

	while (ptr != NULL)
	{
		if (strcmp(ptr->name, s) == 0)
			return ptr;
		else if ((ptr->s != NULL) && (strcmp(ptr->s->name, s) == 0))
			return ptr->s;
		else if (traverseRight(ptr, s) != NULL)
			return traverseRight(ptr, s);
		else
			ptr = ptr->fc;
	}
	return NULL;
}

node* familyTree::traverseRight(node* ptr, char s[50])
{

	//  Searches all the sibilings

	ptr = ptr->ns;

	while (ptr != NULL)
	{
		if (strcmp(ptr->name, s) == 0)
			return ptr;
		else if ((ptr->s != NULL) && (strcmp(ptr->s->name, s) == 0))
			return ptr->s;
		else if (traverseDown(ptr, s) != NULL)
			return traverseDown(ptr, s);
		else
			ptr = ptr->ns;
	}
	return NULL;
}

void familyTree::addNew(node *temp,char opt = NULL, node *ptr = NULL)
{
	if (start == NULL )
	{
		start = temp;
		temp->x = 0;
	}

	else
	{	
		switch (opt)
		{
		case 'c':
		case 'C':
			addChild(search(ptr->name), temp);
			break;
		case 's':
		case 'S':
			addSib(search(ptr->name), temp);
			break;
		case 'w':
		case 'W':
			addSpo(search(ptr->name), temp);
			break;
		}
	}

}

void familyTree::addSpo(node* a, node* b)
{
	// b is added as spouse of a

	if (a->s != NULL)
		cout << a->name << "is married already" << endl;
	else
	{
		a->s = b;
		b->s = a;
		b->x = a->x;
		cout << "\n" << a->name << " married to " << b->name << ".\n";
	}

}

void familyTree::addSib(node* a, node* b)
{
	// b is added as sibling of a

	while (a->ns != NULL)
		a = a->ns;
	a->ns = b;
	b->ps = a;
	b->p = a->p;

	b->x = a->x;
	cout << "\nPerson sucessfully added.\n";
}

void familyTree::addChild(node* a, node* b)
{

	// b is added if married:
	//as child as a (or) b is added as sibiling to last child of a

	if (a->s != NULL)
	{
		if (a->fc == NULL)
		{
			a->fc = b;
			a->s->fc = b;
			b->p = a;
		}
		else
			addSib(a->fc, b);

		b->x = a->x + 1;
		cout << "\nPerson sucessfully added.\n";
	}
	else
		cout << "Need to have a spouse first!\n";

}

int main()
{
	familyTree T[100];
	int opt, n;
	char c, name[50];
	n=7;

	strcpy(name, "adam");
	node *adam = new node();
	adam->setData(name,'m');
	T[n].addNew(adam);


	strcpy(name, "hava");
	node *hava = new node();
	hava->setData(name, 'f');
	T[n].addNew(hava,'w',adam);

	strcpy(name, "shem");
	node *shem = new node();
	shem->setData(name, 'm');
	T[n].addNew(shem, 'c', adam);


	strcpy(name, "ham");
	node *ham = new node();
	ham->setData(name, 'm');

	T[n].addNew(ham, 'c', hava);

	strcpy(name, "yefet");
	node *yefet = new node();
	yefet->setData(name, 'm');

	T[n].addNew(yefet, 's', ham);

	strcpy(name, "kar");
	node *kar = new node();
	kar->setData(name, 'f');

	T[n].addNew(kar, 'w', ham);

	strcpy(name, "posher");
	node *posher = new node();
	posher->setData(name, 'f');

	T[n].addNew(posher, 'c', ham);

	//Display tree
	T[n].display(T[n].start);

	//"Find relation with relation assign (Father/Mother/Wife/Sibling/Cousin/Uncle/Aunt/Grandparent)"
	T[n].findRelation(adam,'f' );
	T[n].findRelation(posher, 'u');
	T[n].findRelation(posher, 'g');
	T[n].findRelation(yefet, 's');

	//finds relation between 2 nodes in the tree
	T[n].find(ham,posher);
	T[n].find(ham, kar);
	T[n].find(posher, shem);
	T[n].find(yefet, posher);
	T[n].find(adam, posher);
	T[n].find(posher,adam);

	cin >> c;

	T[n].destroy(T[n].start);
}
