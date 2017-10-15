/*
 * Stopword.cpp
 *
 *  Created on: Oct 12, 2017
 *      Author: Spasov
 */

#include "Stopword.h"
#include <fstream>

Stopword::Stopword() {}


Stopword::Stopword(string filename)
{
	ifstream fin(filename);
	string words;
	while(fin >> words){
		stopwords.push_back(words);
	}

}

Stopword::~Stopword() {}

bool Stopword::operator ()(string word)
{

	for(string w:stopwords){
		if(w == word)return true;
	}
	return false;
}

