

#include "Document.h"
#include <iostream>
#include <fstream>


// intialize document with filename and size 0
Document::Document(string name)
	:filename(name),filesize(0)
{


}
// empty constructor
Document::Document()
	:filename(""),filecontent(""),filesize(0)
{

}

string Document::name() const{
	return filename;
}

size_t Document::size() const{
	return filesize;
}

string Document::content() const{
	return filecontent;
}
// read file content and store in document
istream & operator>>(istream & is,Document & d)
{

	ifstream fin(d.filename);
	string content;
	while(fin >> content){
		d.filecontent += content + " ";
	}
	d.filecontent = d.filecontent.substr(0,d.filecontent.size()-1);
	d.filesize = d.filecontent.size();
	return is;
}

// print file content
ostream & operator<<(ostream & os,Document & d){

	cout << d.filecontent;
	return os;
}
