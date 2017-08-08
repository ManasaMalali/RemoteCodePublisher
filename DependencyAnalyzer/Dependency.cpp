/////////////////////////////////////////////////////////////////////
//  Deoendency.cpp - Determines depedencies based on #include      //
//																   //
//  Language:      Visual C++ 2015                                 //
//  Platform:      MicroSoft Surface Pro, Windows 10               //
//  Application:   Code Publisher - CSE 687 Project 3              //
//  Author:        Manasa Malali Nagabhushana SUID:845368670       //
/////////////////////////////////////////////////////////////////////

#include "Dependency.h"
#include <fstream>

using namespace std;

DepAnalyzer::DepAnalyzer()
{

}

// function to analyze the dependencies using #include and regular expression
std::unordered_map<std::string, std::vector<std::string>> DepAnalyzer::Analyze(Files ipfiles)
{
	std::string s1;
	smatch ss1, ss2;
	for (auto file : ipfiles)
	{
		ifstream temp(file);
		if (temp.is_open())
		{
			while (std::getline(temp, s1))
			{
				if (regex_match(s1, ss1, regex("(\\s*#include\\s*)(\")(.*)")))
				{
					if (regex_match(s1, ss2, regex("(.*)(\")((.*/)*)(.*)(\\.h\")($)")))
					{
						std::string ext = ".h";
						std::string name = ss2[ss2.size() - 3];
						std::string filename = name + ext;
						Dependencies[file].push_back(filename);
					}
					else if (regex_match(s1, ss2, regex("(.*)(\")((.*/)*)(.*)(\\.cpp\")($)")))
					{
						std::string ext = ".cpp";
						std::string name = ss2[ss2.size() - 2];
						std::string filename = name + ext;
						Dependencies[file].push_back(filename);
					}
				}
				else
				{
					Dependencies[file];
				}
			}
		}
	}
	return Dependencies;
}

#ifdef Dependency
int main()
{
	Dependency dp;
	Files src;
	std::string file1 = "C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\GrandParent.h";
	std::string file2 = "C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Invalid.h";
	std::string file3 = "C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Parent.cpp";
	std::string file4 = "C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Parent.h";
	std::string file5 = "C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Test.cpp";
	src.push_back(file1);
	src.push_back(file2);
	src.push_back(file3);
	src.push_back(file4);
	src.push_back(file5);
	dp.Analyze(src);	
	dp.DepAnalyzer();
	return 0;
}
#endif