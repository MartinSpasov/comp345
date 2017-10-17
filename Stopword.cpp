
#include "stopwords.h"
#include <fstream>

stopwords::stopwords()
{

}

stopwords::stopwords(string fname)
	:filename(fname)
{
	ifstream fin(filename);
	string words;
	while(fin >> words){
		stopword.push_back(words);
	}

}

bool stopwords::operator ()(string word)
{

	for(string w:stopword){
		if(w == word)return true;
	}
	return false;
}


