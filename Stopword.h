

#ifndef STOPWORDS_H_
#define STOPWORDS_H_

#include <vector>
#include <string>
using namespace std;

class stopwords{

private:
	string filename;
	vector<string> stopword;
public:
	stopwords();
	stopwords(string filename);
	bool operator ()(string word);

};


#endif /* STOPWORDS_H_ */
