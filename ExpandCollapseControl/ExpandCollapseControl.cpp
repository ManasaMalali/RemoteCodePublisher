//////////////////////////////////////////////////////////////////////////
//  ExpandCollapseControl.cpp - Provides expand and collapse functionality//
//                              to hide and unhide data on web browser  //
//																        //
//  Language:      Visual C++ 2015                                      //
//  Platform:      MicroSoft Surface Pro, Windows 10                    //
//  Application:   Code Publisher - CSE 687 Project 3                   //
//  Author:        Manasa Malali Nagabhushana SUID:845368670            //
//////////////////////////////////////////////////////////////////////////
#include "ExpandCollapseControl.h"


ExpandCollapse::ExpandCollapse() :node(Repository::getInstance()->AST()) {}

// function that walks through the AST to retrieve the type
void ExpandCollapse::TreeWalkDemo(ASTNode* root)
{
	std::pair<int, int> lcount;
	CheckType(root, lcount);
	for (auto children : root->children_)
	{
		newType = root->type_;
		TreeWalkDemo(children);
		newType = root->type_;
	}
}

// function that checks for the type
void ExpandCollapse::CheckType(ASTNode* root, std::pair<int, int> lcount)
{
	if ((root->type_ == "function") || (root->type_ == "struct") || (root->type_ == "class") || (root->type_ == "enum"))
	{
		lcount = std::make_pair(int(root->startLineCount_), int(root->endLineCount_));
		FileLength[root->path_].push_back(lcount);
	}
}

// function to retrieve the length of function, struct or class
std::unordered_map<std::string, std::vector<std::pair<int, int>>> ExpandCollapse::RetrieveFileLength()
{
	ASTNode *root = node.root();
	TreeWalkDemo(root);
	return FileLength;
}

// test stub
#ifdef Expand
int main()
{
	ExpandCollapse ex;
	ASTNode *Root;
	ex.TreeWalkDemo(Root);
	ex.RetrieceFileLength();
	return 0;
}
#endif