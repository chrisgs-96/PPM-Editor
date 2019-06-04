#ifndef _IM
#define _IM

#include "Array.h"
#include "Serializable.h"
#include "Filter.h"
using namespace math;

typedef Vec3<float> Color;

namespace imaging{
	class Image :public Serializable, public Array<Color>,public Filter{
	public:

		Image(unsigned int x, unsigned int y);

		Image();

		Image(const Image &src);

		Image(unsigned int x, unsigned int y, const Color * data);

		/*! Obtains the color of the image at location (x,y).
		*
		*  The method should do any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to get.
		*  \param y is the (zero-based) vertical index of the pixel to get.
		*
		*  \return The color of the (x,y) pixel as a Color object. Returns a black (0,0,0) color in case of an out-of-bounds x,y pair.
		*/
		Color getPixel(unsigned int x, unsigned int y) const;

		/*! Sets the RGB values for an (x,y) pixel.
		*
		*  The method should perform any necessary bounds checking.
		*
		*  \param x is the (zero-based) horizontal index of the pixel to set.
		*  \param y is the (zero-based) vertical index of the pixel to set.
		*  \param value is the new color for the (x,y) pixel.
		*/
		void setPixel(unsigned int x, unsigned int y, Color & value);

		/*! Copies the image data from an external raw buffer to the internal image buffer.
		*
		*  The member function ASSUMES that the input buffer is of a size compatible with the internal storage of the
		*  Image object and that the data buffer has been alreeady allocated. If the image buffer is not allocated or the
		*  width or height of the image are 0, the method should exit immediately.
		*
		*  \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Image object.
		*/
		void setData(const Color * & data_ptr);

		bool operator << (std::string filename);

		bool operator >> (std::string filename);

		//Image also inherits the methods resize,getRawDataPtr,getWidth,getHeight and the overloaded operators : =,==,()

		void gray();

		void mask(Vec3<float> var);

		float NeighborhoodBlur(unsigned int x, unsigned int y, Vec3<float> *ptr);

		Color NeighborhoodOthers(unsigned int x, unsigned int y, float* red, float* green, float* blue,int mode);

		void blur();

		void medOrDiff(int x);

	};
}

#endif