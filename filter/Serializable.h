//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _SERIALIZABLE_
#define _SERIALIZABLE_

#include <iostream>
#include <string>

/*! Interface for object serialization to a file.
*
* Provides two operators that objects derived from this class can use to store and load their data from a file,
* Using a custom implementation for them.
*/
class Serializable
{
public:
	/*! Reads the contents of an object from the specified file.
	*
	*  The operator can be used for the implementation of "de-serialization".
	*
	*  \param filename is the name of the file to use for loading the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	virtual bool operator << (std::string filename) = 0;

	/*! Writes the contents of an object to the specified file.
	*
	*  The operator can be used for the implementation of "serialization".
	*
	*  \param filename is the name of the file to use for saving the data.
	*
	*  \return true if the operation was successful, false otherwise.
	*/
	virtual bool operator >> (std::string filename) = 0;
};


#endif