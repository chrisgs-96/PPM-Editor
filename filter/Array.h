//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_
#define _ARRAY_

namespace math
{

	//---------------------------------------------------------------------------------------------
	// Do NOT modify this section. For the implementation, see comment below the class declaration
	//---------------------------------------------------------------------------------------------

	/*! The Array class implements a generic two-dimensional array of elements of type T.
	*/
	template <typename T>
	class Array
	{
	protected:
		//! Flat storage of the elements of the array of type T
		T * buffer;

		//! The width of the array (number of columns)
		unsigned int width,

			//! The height of the array (number of rows)
			height;

	public:

		/*! Reports the width (columns) of the array
		*
		* \return the width.
		*/
		unsigned int getWidth() const { return width; }

		/*! Reports the height (rows) of the array
		*
		* \return the height.
		*/
		unsigned int getHeight() const { return height; }

		/*! Obtains a constant pointer to the internal data.
		*
		*  This is NOT a copy of the internal array data, but rather a pointer
		*  to the internally allocated space.
		*/
		void * const getRawDataPtr();

		/*! Returns a reference to the element at the zero-based position (column x, row y).
		*
		* \param x is the zero-based column index of the array.
		* \param y is the zero-based row index of the array.
		*
		* \return a reference to the element at position (x,y)
		*/
		T & operator () (int x, int y);

		/*! Returns a constant reference to the element at the zero-based position (column x, row y).
		*
		* \param x is the zero-based column index of the array.
		* \param y is the zero-based row index of the array.
		*
		* \return a reference to the element at position (x,y)
		*/
		const T & operator () (int x, int y) const;

		/*! Constructor with array size.
		*
		* No default constructor is provided as it makes no sense.
		*
		* \param w is the width (columns) of the array
		* \param h is the height (rows) of the array
		*/
		Array(unsigned int w, unsigned int h);

		/*! Copy constructor.
		*
		* No default constructor is provided as it makes no sense.
		*
		* \param source is the array to replicate.
		*/
		Array(const Array<T> & source);

		/*! Copy assignment operator
		*
		* \param source is the array to replicate.
		*/
		Array & operator = (const Array<T> & source);

		/*! Equality operator.
		*
		*  \param right is the array to compare the current object to.
		*
		*  \return true if the current array and the source have the same dimensions AND
		*  one by one their elements of type T are the same.
		*/
		bool operator == (const Array<T> & right) const;

		/*! Changes the internal array data storage size.
		*
		* If the one or both of the given dimensions are smaller, the array should be clipped
		* by discarding the remaining elements in the rows and/or columns outside the margins.
		* If the new dimensions are larger, pad the old elements with default values of type T.
		* If the array is not yet allocated (zero width and height), allocate the internal buffer and
		* set the array size according to the given dimensions.
		*
		* \param new_width is the user-provided width to resize the array to.
		* \param new_height is the user-provided height to resize the array to.
		*/
		void resize(unsigned int new_width, unsigned int new_height);

		/*! Virtual destructor.
		*/
		virtual ~Array();

	};

	//---------------------------------------------------------------------------------------------
	// Do NOT add the member function implementation here. Add all implementations in the Array.hpp 
	// file included below. The two files will be concatenated upon preprocessing.
	//---------------------------------------------------------------------------------------------


} // namespace math

#include "Array.hpp"

#endif