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

class Stopword {

private:
	std::vector<std::string> stopdwords;

public:
	Stopword();
	Stopword(Std);
	virtual ~Stopword();

	bool operator()(const std::string &) const;
};

#endif /* STOPWORD_H_ */
