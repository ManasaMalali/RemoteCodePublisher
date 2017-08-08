#pragma once
////////////////////////////////////////////////////////////////////////
//  Publisher.h - Publishes files from various packages in web browser//
//																      //
//  Language:      Visual C++ 2015                                    //
//  Platform:      MicroSoft Surface Pro, Windows 10	              //
//  Application:   Code Publisher - CSE 687 Project 3                 //
//  Author:        Manasa Malali Nagabhushana SUID:845368670          //
////////////////////////////////////////////////////////////////////////
#include <fstream>
#include<iostream>
#include<iostream>
#include <ctype.h>
#include <atlstr.h>
#include <string>
#include<regex>
#include <direct.h>
#include<stack>
#include <unordered_map>


class Publisher {
public:
	void GetAllFiles(std::unordered_map<std::string, std::vector<std::string>> dependancyFiles, std::unordered_map<std::string, std::vector<std::pair<int, int>>> MappingLines);
	void HTMLMain();
	void DisplayDependencies(std::unordered_map<std::string, std::vector<std::string>> FileNames, std::unordered_map<std::string, std::vector<std::string>>::iterator i);
	void createCSSfile();
	void createIndexPage();
	void createJavaScriptfile(int count);
	void createHTMLfile();
	void ReplaceAll(std::string filename);
	void ReplaceCharacter(std::string str, std::string filename, int count);
	void GetAllHTMLFiles();
	void GetFileNames(std::unordered_map<std::string, std::vector<std::string>> FileMap);
	void GetFileLength(std::unordered_map<std::string, std::vector<std::pair<int, int>>> FILELENGTH);

private:
	int ncount;
	std::ofstream HTMLfile;
	std::ofstream JSfile;
	std::ofstream CSSfile;
	std::ofstream IndexFile;
	std::unordered_map<std::string, std::string> Display_Links;
	std::unordered_map<std::string, std::vector<std::string>> FileNames;
	//std::vector<std::string> FilePath;
	//std::vector<std::string> Name;
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> FileLengthNew;
	std::stack<int> endlineNum;
};









///////////////////////////////////////////////////////////////////////
////  Publisher.cpp - Generates and Publishes the html files         //
////                                                                 //
////  Language:      Visual C++ 2015                                 //
////  Platform:      Lenovo Yoga, Windows 8.1                        //
////  Application:   Code Publisher - CSE 687 Project 3              //
////  Author:        Soumyashree Mohan Reddy SUID:291434954          //
///////////////////////////////////////////////////////////////////////
//
///*
//This Package is to help help the HTML page generation it uses the Abstract Syntax tree for finding start and endline 
//hence helping in the generation of javascript and html page enabling expand and collapse for the classes and functions
//
//*  Required Files:
//*  ---------------
//*  DepAnal.h DepAnal.cpp Executive.h Executive.cpp Publisher.h Publisher.cpp AbstrSynTree.h AbstrSynTree.cpp
//*  Public Interface
//*  ----------------
//*  tohtml(std::unordered_map<std::string, std::vector<std::string>> dependancyFiles, std::string argv)
//*  htmlLinks()
//*  Maintanence History:
//*  --------------------
//*  Added publisher class which helps in generation of html pages
//*  Added a Collapse class which helps determine start and endline count 
//*/
//#pragma once
//#include <fstream>
//#include<iostream>
//#include <ctype.h>
//#include <atlstr.h>
//#include <string>
//#include<regex>
//#include <direct.h>
//#include<unordered_map>
//#include<stack>
//#include<string.h>
//#include<vector>
//#include<stack>
//#include<unordered_set>
//#include "../AbstractSyntaxTree/AbstrSynTree.h"
//#include"../Parser/ActionsAndRules.h"
//
//class Publisher {
//public:
//	void toHtml(std::unordered_map<std::string, std::vector<std::string>> dependancyFiles, std::string argv);
//	void htmlLinks();
//	void gen_Stylesheet();
//	void gen_Homepage();
//	void htmlbody(std::string filename, std::string displayfilename);
//	void htmlHead();
//	void includeEscapeChar(std::string filename);
//private:
//	std::ofstream writeHTML;
//	std::unordered_map<std::string, std::vector<std::string>> files;
//	std::unordered_map<std::string, std::vector<std::pair<int, int>>> FileLineIndicator;
//	void gen_js();
//	std::ofstream writeJS;
//	int Tag;
//	std::unordered_map<std::string, std::vector<std::pair<int, int>>> MapFiles;
//	std::unordered_map<std::string, std::string> map_Homepage;
//};
//
//using namespace CodeAnalysis;
//
//class Collapse {
//public:
//	Collapse();
//	bool flagFn(ASTNode * node);
//	void RecursiveFn(ASTNode* root);
//	void gen_Map();
//	std::unordered_map<std::string, std::vector<std::pair<int, int>>> toreturn();
//private:
//	std::string parentType;
//	AbstrSynTree &Tree_ref;
//	std::unordered_map<std::string, std::vector<std::pair<int, int>>> FileLineIndicator;
//};
//
