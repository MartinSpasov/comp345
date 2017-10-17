

#include "document.h"
#include <iostream>
#include <fstream>


document::document(string name)
	:filename(name)
{
		fstream fin(filename);
		string content;
		while(fin >> content){
			filecontent += content + " ";
		}
		filecontent = filecontent.substr(0,filecontent.size()-1);
		filesize = filecontent.size();

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
