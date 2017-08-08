#pragma once
//////////////////////////////////////////////////////////////////////////
//  ExpandCollapseControl.h - Provides expand and collapse functionality//
//                              to hide and unhide data on web browser  //
//																        //
//  Language:      Visual C++ 2015                                      //
//  Platform:      MicroSoft Surface Pro, Windows 10	                //
//  Application:   Code Publisher - CSE 687 Project 3                   //
//  Author:        Manasa Malali Nagabhushana SUID:845368670            //
//////////////////////////////////////////////////////////////////////////
#include<string.h>
#include<unordered_map>
#include<iostream>
#include<vector>
#include<stack>
#include<unordered_set>
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include"../Parser/ActionsAndRules.h"

using namespace CodeAnalysis;

class ExpandCollapse {
public:
	ExpandCollapse();
	void TreeWalkDemo(ASTNode* root);
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> RetrieveFileLength();
	void CheckType(ASTNode* root, std::pair<int, int> lcount);
private:
	std::string newType;
	AbstrSynTree &node;
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> FileLength;
};