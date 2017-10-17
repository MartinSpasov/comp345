

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
using namespace std;

class document{

private:
	//! @brief A private string: the document's file name.
	string filename;

	//! @brief A private string: the document's content.
	string filecontent;

	//! @brief a private size_t: the document's size.
	size_t filesize;
public:
	//! @brief A default contructor.
	document();

	//! @brief Another constructor.
	/*!  @param filename: filname of the document to be constructed.
	 */
	document(string filename);

	//! @brief An accessor for the document's name.
	/*!
	 * @return A string: name of the document.
	 */
	string name() const;

	//! @brief An accessor for the document's size.
	/*!
	 * @return A size_t: the size of the document.
	 */
	size_t size() const;

	//! @brief An accessor for the document's content.
	/*!
	 * @return A string: the content of the document.
	 */
	string content() const;

	//! @brief A friend operator<< overload.
	/*!
	 * Prints the document information
	 * @param is:
	 * @param d: the document which's information we print out
	 * @return
	 */
	friend ostream & operator<<(ostream & os,document & d);




};




#endif /* DOCUMENT_H_ */
