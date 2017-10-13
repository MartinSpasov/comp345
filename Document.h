/*
 * Document.h
 *
 *  Created on: Oct 12, 2017
 *      Author: Spasov
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_
#include <string>
#include <vector>

class Document {

private:
	int size;
	std::string name;
	std::vector<std::string> content;

public:
	Document();
	Document(std::string);
	virtual ~Document();

	std::string getName() const;
	int getSize() const;
	std::vector<std::string> getContent() const;
};

#endif /* DOCUMENT_H_ */
