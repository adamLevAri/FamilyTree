
#include "familyTree.h"


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
	string g;
	g = "Female";
	if (ptr->g)
		g = "Male";
	printf("\nName: %s", ptr->name.c_str());
	printf("\nGender: %s", g.c_str());
	if (ptr->s != NULL)
		printf("\nMarried to: %s", ptr->s->name.c_str()
		);
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
			printf("%s & %s\n ", ptr->name.c_str(), ptr->s->name.c_str());
		else
			printf("%s\n ", ptr->name.c_str());
		display(ptr->fc);

		ptr = ptr->ns;
	}
}

string familyTree::find(string name1, string name2)
{

	/*
		Same hight: Sibiling if same parent, or married else cousin
		Difference of height = 1 - Parent if immediate, else uncule/aunt
		Difference oh height = 2 - Grand parents if same link, else idk
	*/
	node* ptr1 = search(name1);
	node* ptr2 = search(name2);

	if (ptr1 == NULL || ptr2 == NULL)
		return "no sutch person";


	node* ptr;
	node* ptrk = ptr1;
	node* ptrk1 = ptr2;

	string s, str, str1, str2, str3;
	switch (ptr1->x - ptr2->x)
	{

	case 0:
		s = "wife";
		if (ptr1->g)
			s = "husband";

		ptr = ptr1->s;
		if ((ptr != NULL) && (ptr == ptr2))
		{
			return s;
		}

		s = "sister";
		if (ptr1->g)
			s = "brother";

		ptr = ptr1;
		while (ptr != NULL)
		{
			if (ptr == ptr2)
			{
				return s;
			}
			ptr = ptr->ns;
		}
		ptr = ptr2;
		while (ptr != NULL)
		{
			if (ptr == ptr1)
			{
				return s;
			}
			ptr = ptr->ns;
		}
		return "Cousins";
		break;

	case 1:
		str3 = "daughter";
		if (ptr1->g)
			str3 = "son";
		ptr2 = ptr2->fc;
		while (ptr2 != NULL)
		{
			if (ptr2 == ptr1)
			{
				return str3;
			}
			ptr2 = ptr2->ns;
		}
		str3 = "niece";
		if (ptr1->g)
			str3 = "nephew";
		return str3;
		break;
	case -1:
		str = "mother";
		if (ptrk->g)
			str = "father";

		ptr = ptrk->fc;
		while (ptr != NULL)
		{
			if (ptr == ptrk1)
			{
				return str;
			}
			ptr = ptr->ns;
		}
		str = "aunt";
		if (ptrk->g)
			str = "uncule";
		return str;
		break;

	case 2:
		str1 = "daughter";
		if (ptr2->g)
			str1 = "son";
		ptr2 = ptr1->p->p;

		if (ptr2->name == ptr1->p->p->name)
		{
			return "grand" + str1;
		}
		while (ptr2 != NULL)
		{
			if (ptr2 == ptr1)
			{
				return "grand" + str2;
			}
			ptr2 = ptr2->ns;
		}
		break;
	case -2:
		str2 = "mother";

		if (ptr1->g)
			str2 = "father";

		if (ptr1->name == ptr2->p->p->name)
		{
			return ("grand" + str2);
		}
		
		while (ptr1 != NULL)
		{
			if (ptr1 == ptr2)
			{
				return ("grand" + str1);
			}
			ptr1 = ptr1->ns;
		}

		break;
	default:
		return "Too far relationship";
		break;
	}
    return "";
}

string familyTree::findRelation(string name, char r)
{
	node* ptr = search(name);
	node* ptrk;
	string s;

	switch (r) {
		//Wife relation
	case 'W':
	case 'w':
		return ptr->s->name;
		break;

		//Parent relation
	case 'f':
	case 'F':
	case 'M':
	case 'm':
		if (ptr->p != NULL)
			return ptr->p->name;
		else
			return "God";
		break;

		//Cousin relation
	case 'C':
	case 'c':
		ptrk = ptr;
		while (ptrk->ps != NULL)
			ptrk = ptrk->ps;
		if (ptrk->p->ns->fc != NULL)
			return ptrk->p->ns->fc->name;
		else
			return "None";
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
			return ptr->ns->name;
		else if (ptr->s->ns != NULL)
			return ptr->s->ns->name;
		//we check both parents side for uncle/aunt - left side.
		else if (ptr->ps != NULL)
			return ptr->ps->name;
		else if (ptr->s->ps != NULL)
			return  ptr->s->ps->name;
		else
			return "None";
		break;

		//Grandparent relation
	case 'G':
	case 'g':
		if (ptr->p->p != NULL)
			return ptr->p->p->name;
		break;

		//Sibling relation
	case 'S':
	case 's':
		s = "sister";
		if (ptr->g)
			s = "brother";

		if (ptr->ns != NULL)
			return s;
		else if (ptr->ps != NULL)
			return s;
		else
			return "None";
		break;

	default:
		cout << "NO SUCH REALTION.";
		break;
	}
    return "";
}

node* familyTree::search(string s)
{
	/*
		Searches for the given name from start to it's sibilings and their children
		Returns the pointer of node where the name is present
	*/

	node *ptr = start;

	if (ptr->name == s)
		return ptr;
	else if ((ptr->s != NULL) && (ptr->s->name == s))
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

node* familyTree::traverseDown(node* ptr, string s)
{
	// Searches all the children

	ptr = ptr->fc;

	while (ptr != NULL)
	{
		if (ptr->name == s)
			return ptr;
		else if ((ptr->s != NULL) && (ptr->s->name == s))
			return ptr->s;
		else if (traverseRight(ptr, s) != NULL)
			return traverseRight(ptr, s);
		else
			ptr = ptr->fc;
	}
	return NULL;
}

node* familyTree::traverseRight(node* ptr, string s)
{

	//  Searches all the sibilings

	ptr = ptr->ns;

	while (ptr != NULL)
	{
		if (ptr->name == s)
			return ptr;
		else if ((ptr->s != NULL) && (ptr->s->name == s))
			return ptr->s;
		else if (traverseDown(ptr, s) != NULL)
			return traverseDown(ptr, s);
		else
			ptr = ptr->ns;
	}
	return NULL;
}

void familyTree::addNew(string name, char g)
{
	if (start == NULL)
	{
		node* temp = new node();
		temp->setData(name, g);
		start = temp;
		temp->x = 0;
	}
}

void familyTree::addNew(string name1, char g, char relation, string name2)
{

	node* temp = new node();

	{
		temp->setData(name1, g);

		switch (relation)
		{
		case 'c':
		case 'C':
			addChild(search(name2), temp);
			break;
		case 's':
		case 'S':
			addSib(search(name2), temp);
			break;
		case 'w':
		case 'W':
			addSpo(search(name2), temp);
			break;
		}
	}

}

void familyTree::addSpo(node* a, node* b)
{
	// b is added as spouse of a

	if (a->s != NULL)
		printf("married already");
	else
	{
		a->s = b;
		b->s = a;
		b->x = a->x;
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
	//cout << "\nPerson sucessfully added.\n";
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
		//cout << "\nPerson sucessfully added.\n";
	}
	else
		cout << "Need to have a spouse first!\n";

}

familyTree::~familyTree()
{
}
