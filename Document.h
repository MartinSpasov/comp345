

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
using namespace std;

class document{

private:
	string filename;
	string filecontent;
	size_t filesize;
public:
	document();
	document(string filename);
	string name() const;
	size_t size() const;
	string content() const;
	friend ostream & operator<<(ostream & os,document & d);




};




#endif /* DOCUMENT_H_ */
