///////////////////////////////////////////////////////////////////////////
//  Publisher.cpp - Publishes files from various packages in web browser //
//																         //
//  Language:      Visual C++ 2015                                       //
//  Platform:      MicroSoft Surface Pro, Window 10                      //
//  Application:   Code Publisher - CSE 687 Project 3                    //
//  Author:        Manasa Malali Nagabhushana SUID:845368670             //
///////////////////////////////////////////////////////////////////////////
#include"Publisher.h"
#include "../FileSystem/FileSystem.h"
#include <fstream>

// function to retrieve the filenames and filepaths
void Publisher::GetAllFiles(std::unordered_map<std::string, std::vector<std::string>> FileMap, std::unordered_map<std::string, std::vector<std::pair<int, int>>> FILELENGTH)
{
	GetFileNames(FileMap);
	GetFileLength(FILELENGTH);
}

// function to retrieve filenames
void Publisher::GetFileNames(std::unordered_map<std::string, std::vector<std::string>> FileMap)
{
	FileNames = FileMap;
}

// function to retrieve filepaths
void Publisher::GetFileLength(std::unordered_map<std::string, std::vector<std::pair<int, int>>> FILELENGTH)
{
	FileLengthNew = FILELENGTH;
}

// function that crates stylesheet and javascript
void Publisher::HTMLMain()
{
	//_mkdir("..\\HTMLfiles");
	ncount = 0;
	JSfile.open("../ServerRepository/JavaScript.js");
	createCSSfile();
	createHTMLfile();
	createIndexPage();
	std::string homepage = "../ServerRepository/Index.htm";
	std::string launchHomepage("start \"\"  \"" + homepage + "\"");
	std::system(launchHomepage.c_str());
}

// function to create HTML files
void Publisher::createHTMLfile() {
	for (std::unordered_map<std::string, std::vector<std::string>>::iterator i = FileNames.begin(); i != FileNames.end(); i++)
	{
		std::string str = (*i).first;
		std::smatch s1;
		std::regex temp = std::regex("(.*:\\\\)((.*\\\\.*\\\\)*)(.*)");
		(regex_match(str, s1, temp));
		std::string result = s1[s1.size() - 1];
		std::string filename = "../ServerRepository/" + result + ".htm";
		std::string newFile = result + ".htm";
		Display_Links[newFile] = result;
		std::cout << Display_Links[newFile] + ".htm" << std::endl;
		HTMLfile.open(filename);
		HTMLfile << "<!/////////////////////////////////////////////////////////////////////" << std::endl;
		HTMLfile << "//  Filename : " + result + "								           //" << std::endl;
		HTMLfile << "//																   //" << std::endl;
		HTMLfile << "//  Language:      Visual C++ 2015                                 //" << std::endl;
		HTMLfile << "//  Platform:      MicroSoft Surface Pro, Windows 10	           //" << std::endl;
		HTMLfile << "//  Application:   Code Publisher - CIS 687 Project 3              //" << std::endl;
		HTMLfile << "//  Author:        Manasa Malali Nagabhushana SUID:845368670       //" << std::endl;
		HTMLfile << "/////////////////////////////////////////////////////////////////////>" << std::endl;
		HTMLfile << "<html>" << std::endl;
		HTMLfile << "<head>" << std::endl;
		HTMLfile << "<link rel = \"stylesheet\" type =\"text/css\" href = \"Stylesheet.css\">" << std::endl;
		HTMLfile << "<script type = \"text/javascript\" src= \"JavaScript.js\"></script>" << std::endl;
		HTMLfile << "</head>" << std::endl;
		HTMLfile << "<body>" << std::endl;
		HTMLfile << "  <h1 align = \"center\">" << "Code Publisher" << "</h1>";
		HTMLfile << "  <h3>" << result.c_str() << "</h3>";
		HTMLfile << "   <hr />" << std::endl;
		HTMLfile << "   <div class=\"indent\">" << std::endl;
		HTMLfile << "     <h4>Dependencies:</h4>" << std::endl;
		DisplayDependencies(FileNames, i);
		HTMLfile << "   </div>" << std::endl;
		HTMLfile << "   <hr />" << std::endl;
		ReplaceAll((*i).first);
		HTMLfile << "</body>" << std::endl;
		HTMLfile << "</html>";
		HTMLfile.close();
	}
			
}

// function to display the dependencies on web browser
void Publisher::DisplayDependencies(std::unordered_map<std::string, std::vector<std::string>> FileNames, std::unordered_map<std::string, std::vector<std::string>>::iterator i)
{
	//int i, j;
	for (std::vector<std::string>::iterator j = FileNames[(*i).first].begin(); j != FileNames[(*i).first].end(); j++) {
		HTMLfile << "<a href =" << (*j).c_str() << ".htm" << ">" << (*j).c_str() << " </a> </br>" << std::endl;
		HTMLfile << std::endl;
	}
}

void Publisher::ReplaceAll(std::string filename) {
	std::ifstream readfile(filename);
	std::string str;
	int count = 0;
	if (readfile.is_open()) {
		while (std::getline(readfile, str)) {
			count++;
			ReplaceCharacter(str, filename, count);
		}
	}
}

// function to replace special characters
void Publisher::ReplaceCharacter(std::string str, std::string filename, int count)
{
	std::string newstr;
	std::vector<char> v(str.c_str(), str.c_str() + str.length() + 1);
	for (int i = 0; i < v.size(); i++) {
		switch (v.at(i)) {
		case '&':
			newstr = newstr + "&amp;";
			break;
		case '<':
			newstr = newstr + "&lt;";
			break;
		case '>':
			newstr = newstr + "&gt;";
			break;
		case '"':
			newstr = newstr + "&quot;";
			break;
		case '\'':
			newstr = newstr + "&apos;";
			break;
		default:
			newstr = newstr + v.at(i);
			break;
		}
	}
	bool flag = 0;
	for (int j = 0; j < FileLengthNew[filename].size(); j++) {
		if ((count == FileLengthNew[filename].at(j).first) && (FileLengthNew[filename].at(j).first != FileLengthNew[filename].at(j).second)) {
			ncount++;
			HTMLfile << "<button onclick=\"toggle(" << ncount << ")\">-</button>";
			HTMLfile << "<pre>" << newstr << "</pre>";
			HTMLfile << "<div id=" << "\"" << ncount << "\"" << ">";
			createJavaScriptfile(ncount);
			endlineNum.push(FileLengthNew[filename].at(j).second);
			flag = 1;
		}
	}
	if (flag == 0) {
		HTMLfile << "<pre>";
		HTMLfile << newstr;
		HTMLfile << std::endl;
		HTMLfile << "</pre>";
	}
	if (!endlineNum.empty()) {
		if (count == endlineNum.top()) {
			HTMLfile << "</div>" << "</br>" << std::endl;
			endlineNum.pop();
		}
	}
}

// function to create javascript file
void Publisher::createJavaScriptfile(int count)
{
	JSfile << "function toggle(count) {";
	JSfile << "var x = document.getElementById(count);";
	JSfile << "if (x.style.display === 'none')" << "{";
	JSfile << "x.style.display = 'block';" << "}";
	JSfile << "else" << "{";
	JSfile << "x.style.display = 'none';" << "}" << "}";
	JSfile << std::endl;
}

//function to create stylesheet
void Publisher::createCSSfile() {
	CSSfile.open("../ServerRepository/Stylesheet.css");
	CSSfile << "    body {" << std::endl;
	CSSfile << "      margin: 20px;" << std::endl;
	CSSfile << "      color: black;" << std::endl;
	CSSfile << "      background-color:#F0FFFF;" << std::endl;
	CSSfile << "      font-family: Consolas,sans-serif;" << std::endl;
	CSSfile << "      font-weight: 600;" << std::endl;
	CSSfile << "      font-size: 110%;" << std::endl;
	CSSfile << "    }" << std::endl;
	CSSfile << "    .indent{" << std::endl;
	CSSfile << "      margin-left: 20px;" << std::endl;
	CSSfile << "      margin-right: 20px;" << std::endl;
	CSSfile << "    }" << std::endl;
	CSSfile << "    h4 {" << std::endl;
	CSSfile << "      margin-bottom: 3px;" << std::endl;
	CSSfile << "      margin-top: 3px;" << std::endl;
	CSSfile << "    }" << std::endl;
	CSSfile << "pre{" << std::endl;
	CSSfile << "display: inline;" << std::endl;
	CSSfile << "}" << std::endl;
}

// function to create index page
void Publisher::createIndexPage() {
	IndexFile.open("../ServerRepository/Index.htm");
	std::string filepath = FileSystem::Directory::getCurrentDirectory();
	std::cout << "current directory is:" << filepath << std::endl;
	IndexFile << "<html>" << std::endl;
	IndexFile << "<head>" << std::endl;
	IndexFile << "<link rel = \"stylesheet\" type =\"text/css\" href = \"Stylesheet.css\">" << std::endl;
	IndexFile << "</head>" << std::endl;
	IndexFile << "  <h1 align = \"center\">" << "Remote Code Publisher" << "</h1>";
	IndexFile << "<body>" << std::endl;
	IndexFile << "  <h3>" << "Index:" << "</h3>";
	IndexFile << "   <hr />" << std::endl;
	IndexFile << "   <div class=\"indent\">" << std::endl;
	IndexFile << "     <h4>Below is a list of the generated HTML files:</h4>" << std::endl;
	GetAllHTMLFiles();
	IndexFile << "   </div>" << std::endl;
	IndexFile << "   <hr />" << std::endl;
	IndexFile << "</body>" << std::endl;
	IndexFile << "</html>" << std::endl;
	IndexFile.close();
}

void Publisher::GetAllHTMLFiles()
{
	for (auto EachFile : Display_Links) {
		IndexFile << "<a href =" << EachFile.first << ">" << EachFile.second << " </a> </br>" << std::endl;
		IndexFile << std::endl;
	}
}

// test stub
#ifdef Publisher
int main() {
	CodePublisher p;
	std::unordered_map<std::string, std::vector<std::string>> FILES;
	path_file["C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Grandparent.h"];
	path_file["C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Invalid.h"];
	path_file["C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Parent.cpp"].push_back("C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Parent.h");
	path_file["C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Parent.cpp"].push_back("C:\\Users\\manasa\\Desktop\\OOD\\Project3\\CodeAnalyzerEx\\CodeAnalyzerEx\\testfiles\\Child.h");
	path_file["Child.cpp"].push_back("Child.h");
	path_file["Child.cpp"].push_back("Grandparent.h");
	path_file["Child.h"].push_back("j1");
	path_file["Grandparent.h"].push_back("j2");
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> MapLines;
	std::pair<int, int> line, line1;
	line.first = 3;
	line1.first = 10;
	line.second = 4;
	line1.second = 20;
	MapLines["C:\\Users\\manasa\\Desktop\\Project3.1\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Grandparent.h"].push_back(line);
	MapLines["C:\\Users\\manasa\\Desktop\\Project3.1\\CodeAnalyzerEx\\CodeAnalyzerEx\\files\\Grandparent.h"].push_back(line1);
	p.FileMapping(path_file, MapLines);
	p.ConverttoHTML();

	return 0;
}
#endif
