

#include "document.h"
#include <iostream>
#include <fstream>


document::document(string name)
	:filename(name),filesize(0)
{
		ifstream fin(d.filename);
		string content;
		while(fin >> content){
			d.filecontent += content + " ";
		}
		d.filecontent = d.filecontent.substr(0,d.filecontent.size()-1);
		d.filesize = d.filecontent.size();

}
document::document()
	:filename(""),filecontent(""),filesize(0)
{

}

string document::name() const{
	return filename;
}

size_t document::size() const{
	return filesize;
}

string document::content() const{
	return filecontent;
}


ostream & operator<<(ostream & os,document & d){

	cout << d.filecontent;
	return os;
}
