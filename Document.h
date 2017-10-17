

#ifndef Document_H_
#define Document_H_

#include <string>
using namespace std;

class Document{

private:
	string filename;
	string filecontent;
	size_t filesize;
public:
	Document();
	Document(string filename);
	string name() const;
	size_t size() const;
	string content() const;
	friend istream & operator>>(istream & is,Document & d);
	friend ostream & operator<<(ostream & os,Document & d);




};




#endif /* Document_H_ */
