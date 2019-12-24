
#include "node.h"

node::node()
{
	fc = ns = ps = p = s = NULL;
	g = 0;
	name = "";
	x = 0;
}


void node::setData(string personName, char gender)
{
	this->name = personName;
	if (gender == 'm' || gender == 'M')
		g = 1;
}

node::~node()
{
}
