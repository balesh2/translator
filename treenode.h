#ifndef _TREENODE_H
#define _TREENODE_H

#include <string>

using namespace std;

class TreeNode {
	public: 
		TreeNode();

		bool visited;

		int lineNumber;
		int nodeType;
		int nValue;
		int typeSpecifier;

		string rename;
		string sValue;

		TreeNode *C1;
		TreeNode *C2;
		TreeNode *C3;
		TreeNode *sibling;
};

#endif
