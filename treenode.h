#ifndef _TREENODE_H
#define _TREENODE_H

#include <string>

using namespace std;

class TreeNode 
{
	public: 
		TreeNode();

		int lineNumber;
		int nValue;
		string sValue;
		int nodeType;
		int typeSpecifier;
		string rename;
		bool visited;

		TreeNode *C1;
		TreeNode *C2;
		TreeNode *C3;
		TreeNode *sibling;
};

#endif
