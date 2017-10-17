

#include "indexer.h"
#include "document.h"
#include "Query_String.h"
#include <iostream>
using namespace std;

int main(){
	document d1("index.txt");
	cin >> d1;
	document d2("index2.txt");
	cin >> d2;
	document d3("index3.txt");
	cin >> d3;
	indexer<3> idx;
	d1 >> idx;
	d2 >> idx;
	d3 >> idx;
	cout << idx;
	Query_String q;
	q.query(idx,"comp345",idx.indexersize());
	return 0;
}



