
#include "Demo.h"
#include "familyTree.h"
#include<vector>


int main()
{
	familyTree T;

	T.addNew("adam", 'm');
	T.addNew("hava", 'f', 'w', "adam");
	T.addNew("shem", 'm', 'c', "adam");
	T.addNew("ham", 'm', 'c', "hava");
	T.addNew("yefet", 'm', 's', "ham");
	T.addNew("kar", 'f', 'w', "ham");
	T.addNew("posher", 'm', 'c', "ham");
	T.display(T.start);

	//"Find relation with relation assign (Father/Mother/Wife/Sibling/Cousin/Uncle/Aunt/Grandparent)"
	T.findRelation("adam", 'f');
	T.findRelation("posher", 'u');
	T.findRelation("posher", 'g');
	T.findRelation("yefet", 's');

	//finds relation between 2 nodes in the tree
	T.find("ham", "posher");
	T.find("ham", "kar");
	T.find("posher", "shem");
	T.find("yefet", "posher");
	T.find("adam", "posher");
	T.find("posher", "adam");

    return 0;
}
