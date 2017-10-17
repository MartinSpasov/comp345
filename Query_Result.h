#ifndef QUERY_RESULT_H_
#define QUERY_RESULT_H_
#include <string>
#include "Document.h"
using namespace std;

class Query_Result {

public:
	Document document;
	int score;

	Query_Result();
	Query_Result(Document d, int s);

};

#endif
