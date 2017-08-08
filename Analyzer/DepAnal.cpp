/////////////////////////////////////////////////////////////////////
//  DepAnal.cpp - Determines depedancies based on #include         //
//                                                                 //
//  Language:      Visual C++ 2015                                 //
//  Platform:      Lenovo Yoga, Windows 8.1                        //
//  Application:   Code Publisher - CSE 687 Project 3              //
//  Author:        Soumyashree Mohan Reddy SUID:291434954          //
/////////////////////////////////////////////////////////////////////


#include "DepAnal.h"
#include <fstream>

using namespace std;

DependencyAnalyzer::DependencyAnalyzer()
{
}
// Function to determine dependencies based on #include
std::unordered_map<std::string, std::vector<std::string>> DependencyAnalyzer::DepAnal(Files FilesForAnal)
{
	std::string match;
	smatch smatch1;
	std::regex tomatch = std::regex("(\\s*#include.*)");
	std::regex temp = regex("(\\s*#include\\s*)(\")((\\.*/*)*)((.*/)*)(.*)(\")");
	for (auto file : FilesForAnal)
	{
		ifstream srcfile(file);
		if (srcfile.is_open())
		{
			while (std::getline(srcfile, match))
			{
				if (regex_match(match, tomatch))
				{
					if (regex_match(match, smatch1, temp)) {
						std::string result = smatch1[smatch1.size() - 2];
						FileDependencies[file].push_back(result);
					}
				}
				else
				{
					FileDependencies[file];
				}
			}
		}
	}
	return FileDependencies;
}

//Function to display dependancies
void DependencyAnalyzer::Display() {
	std::cout << "\n\n Dependency Analysis : " << std::endl;
	std::regex temp = std::regex("(.*:\\\\)((.*\\\\.*\\\\)*)(.*)");
	smatch s;
	for (auto x : FileDependencies)
	{
		std::cout << "Filename:" << std::endl;
		(regex_match(x.first, s, temp));
		std::string result = s[s.size() - 1];
		std::cout << result << std::endl;
		std::cout << "The above file depends on" << std::endl;
		for (auto xx : x.second)
		{
			std::cout << "  --  " << xx << std::endl;
		}
		std::cout << "\n\n";
	}
}

#ifdef testDepAnalysis
int main() {
	DependencyAnalyzer d1;
	std::vector<std::string> files;
	files.push_back("C:\\Users\\Soumyashree\\Documents\\Syracuse Blackboard\\Spring-2017\\OOD\\Project-3\\Project3\\Publisher\\files\\Invalid.h");
	files.push_back("C:\\Users\\Soumyashree\\Documents\\Syracuse Blackboard\\Spring-2017\\OOD\\Project-3\\Project3\\Publisher\\files\\Parent.cpp");
	d1.DepAnalfiles();
	d1.Display();
}
#endif // DEBUG
