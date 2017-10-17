

#include "tokenizer.h"
#include "stopwords.h"
#include <algorithm>
#include <sstream>
#include <iterator>

tokenizer::tokenizer(){}

vector<string> tokenizer::tokenize(string s)
{
	vector<string> temp;
	vector<string> tokens;
	stopwords stpw("stopwords.txt");
	istringstream iss(s);
	// splitting by whitespace and pushing to array temp
	copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(temp));
	for(int i=0;i<temp.size();i++){
		string s = temp[i];
		// to lowercase
		transform(s.begin(), s.end(), s.begin(), ::tolower);
		// if the word is stop word push it as it is.
		if(stpw(s))
			tokens.push_back(s);
		// else remove punctuation
		else {
			string result;
			// remove punctuation
			remove_copy_if(s.begin(), s.end(),back_inserter(result), ptr_fun<int, int>(&std::ispunct));
			tokens.push_back(result);
		}
	}
	return tokens;

}


