#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <trim.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;
typedef set<string> TYPE_KEYWORD_DICTIONARY;
typedef unsigned long int TYPE_COUNTER;

 const char* const delimiter = "`-=[]\\;\',./~!@#$%^&*()+{}|:\"<>? \n\t\v\b\r\f\a"; 
 bool is_word(std::string& s)
{   bool flagd =true, flagc = false;  int count = 0;
std::string::iterator it = s.begin();
    for (it = s.begin();it != s.end(); ++it)  {
	count++;
    if (std::isalpha(*it)){}
	else {flagd = false; 	
}
    if (count > 6)  flagc = true;
	}
	
	
    return (flagd && flagc);
}
int extractWords_using_find_first_of(TYPE_KEYWORD_DICTIONARY &rKeywordsDictionary,
		TYPE_COUNTER *pKeywordNum,
		ifstream &rFin){

	bool capture = false;
	string line, word;
	while(getline(rFin, line)) 
    {
		size_t prev = 0, pos;
		boost::trim(line);
		while ((pos = line.find_first_of(delimiter, prev)) != std::string::npos)
		{
			if (pos > prev)
            {
				word = line.substr(prev, pos-prev);
				boost::trim(word);
                //convert the word to lower case
                std::transform(word.begin(),word.end(),word.begin(),::tolower);
				if (word == "origin") capture=true;
				if (is_word(word) && capture && *pKeywordNum <= 20){
                rKeywordsDictionary.insert(word);
				*pKeywordNum = *pKeywordNum + 1;}
			}

			prev = pos+1;
		}
		if (prev < line.length()){
			word = line.substr(prev, std::string::npos);
			boost::trim(word);

            //convert the word to lower case
            std::transform(word.begin(),word.end(),word.begin(),::tolower);
			if (word == "origin") capture=true;
			if (is_word(word)&& capture && *pKeywordNum <= 20){
            rKeywordsDictionary.insert(word);
			*pKeywordNum = *pKeywordNum + 1;}
		}

	}

	return 0;
}
int extractKeywords(TYPE_KEYWORD_DICTIONARY &rKeywordsDictionary,
		string file_name ,string path) 
{ 
	TYPE_COUNTER keyword_num = 0;
	string fname_with_path;

	// create a file-reading object
	ifstream fin;

	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append(".txt");

	// open a file
	fin.open(fname_with_path.c_str(),std::fstream::in);
	if (!fin.good()){
		return -1; // exit if file not found
	}
	// Extract keywords from a file
	extractWords_using_find_first_of(rKeywordsDictionary, &keyword_num, fin);

	fin.close();

	return 0;
}

void writeKeywords(TYPE_KEYWORD_DICTIONARY keywordSet, string file_name, string path){
	
	string fname_with_path;
	set<string>::iterator it;

	fname_with_path.append(path);
	fname_with_path.append(file_name);
	fname_with_path.append("kw");
	fname_with_path.append(".txt");

	ofstream myfile;
	myfile.open (fname_with_path.c_str(), ios::out | ios::binary); 
	for (it=keywordSet.begin(); it!=keywordSet.end(); ++it){
		myfile << ' ' << *it;
	}
	
	
}
