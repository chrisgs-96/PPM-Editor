//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//
//-------------------------------------------------------------

#ifndef _PPM
#define _PPM

#include "Image.h"


namespace imaging
{
	/*! Reads a PPM image file and returns a pointer to a newly allocated Image object containing the image.
	*
	*  \param filename is the null-terminated string of the name of the file to open.
	*
	*  \return a pointer to a new Image object, if the read operation was successful, nullptr otherwise.
	*/
	Image * ReadPPM(const char * filename);


	/*! Writes an existing image as a PPM file.
	*
	*  \param image is the Image object to save to a file in the PPM format.
	*  \param filename is the null-terminated string of the name of the file to create.
	*
	*  \return true if the image save operation was successful, false otherwise.
	*/
	bool WritePPM(Image & image, const char * filename);

} //namespace imaging

#endif