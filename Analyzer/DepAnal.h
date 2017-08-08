/////////////////////////////////////////////////////////////////////
//  DepAnal.h - Determines depedancies based on #include           //
//                                                                 //
//  Language:      Visual C++ 2015                                 //
//  Platform:      Lenovo Yoga, Windows 8.1                        //
//  Application:   Code Publisher - CSE 687 Project 3              //
//  Author:        Soumyashree Mohan Reddy SUID:291434954          //
/////////////////////////////////////////////////////////////////////

/*
Dependency Analyzer gives the determines dependensies based on #include
*  Required Files:
*  ---------------
*  DepAnal.h DepAnal.cpp Executive.h Executive.cpp
*  Public Interface:
* =================
*  DepAnal(sourcefiles)
*  Display()
*  Maintanence History:
*  --------------------
*  Added DependencyAnalyzer class which helps in the finding Deprndencies
*/
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <unordered_map>

using Files = std::vector<std::string>;

class DependencyAnalyzer
{
public:
	DependencyAnalyzer();
	std::unordered_map<std::string, std::vector<std::string>> DepAnal(Files sourcefiles);
	void Display();
private:
	Files FilesForAnal;
	std::unordered_map<std::string, std::vector<std::string>> FileDependencies;
};