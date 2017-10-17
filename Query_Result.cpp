
#include "Query_Result.h"
#include <fstream>

Query_Result::Query_Result() {}


Query_Result::Query_Result(Document d, int s)
	:document(d),score(s)
{
	Document x = new Document();
}

