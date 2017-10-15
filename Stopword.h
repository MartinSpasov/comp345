/*
 * Stopword.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Spasov
 */

#ifndef STOPWORD_H_
#define STOPWORD_H_
#include <string>
#include <vector>
using namespace std;

class Stopword {

private:
	string filename;
	vector<string> stopdwords;

public:
	Stopword();
	Stopword(string filename);
	~Stopword();
	bool operator ()(string word);
};

#endif /* STOPWORD_H_ */
