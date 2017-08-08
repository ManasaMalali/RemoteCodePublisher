#pragma once
/////////////////////////////////////////////////////////////////////
//  Deoendency.h - Determines depedencies based on #include	       //
//																   //
//  Language:      Visual C++ 2015                                 //
//  Platform:      MicroSoft Surface Pro, Windows 10               //
//  Application:   Code Publisher - CSE 687 Project 3              //
//  Author:        Manasa Malali Nagabhushana SUID:845368670       //
/////////////////////////////////////////////////////////////////////
#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <unordered_map>

using Files = std::vector<std::string>;

class DepAnalyzer
{
public:
	DepAnalyzer();
	std::unordered_map<std::string, std::vector<std::string>>Analyze(Files sourcefiles);

private:
	Files InputFiles;
	std::unordered_map<std::string, std::vector<std::string>> Dependencies;
};
