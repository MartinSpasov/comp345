

#include "indexer.h"
#include "document.h"
#include "Query_String.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(){
	const int size = 2;
	indexer<size> idx;
	cout << "Enter filename:" << endl;
	string filename;
	cin >> filename;
	fstream fin(filename.c_str());
	for(int i=0;i<size;i++){
		string d;
		fin >> d;
		document doc(d);
		cin >> doc;
		doc >> idx;
	}
	cout << idx;
	Query_String q;
	string query = "";
	while(true){
		cout << "\nEnter query you want to search for or -1 to exit:" << endl;
		cin >> query;
		if(query == "-1")break;
		cout << "Enter number of documents for the top queries or -1 to skip:" << endl;
		int n;
		cin >> n;
		if(n == -1)
		q.query(idx,query);
		else
		q.query(idx,query,n);
	}

	return 0;
}



