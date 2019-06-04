//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2016
//
//

#ifndef _ARRAY_IMPLEMENTATION_
#define _ARRAY_IMPLEMENTATION_

#include "Array.h"
#include "Vec3.h"
#include <iostream>

namespace math
{

	//--------------------------------------------------------------------------------------------
	// This file is included from the templated Array class header.
	// TODO: Provide its member function implementations here:
	//--------------------------------------------------------------------------------------------
	template <typename T> void * const  Array<T>::getRawDataPtr()
	{
		return buffer;
	}

	template <typename T> T & Array<T>::operator () (int x, int y)
	{
		return *(buffer + ((y*width) + x));
	}

	template <typename T> const T & Array<T>::operator () (int x, int y) const
	{
		return  *(buffer + ((y*width) + x));
	}

	template <typename T> Array<T>::Array(unsigned int w, unsigned int h) : width(w), height(h), buffer(nullptr){}

	template <typename T> Array<T>::Array(const Array<T> & source)
	{
		width = source.width;
		height = source.height;
		buffer = new T[width*height];
		std::memcpy(buffer, source.buffer, width*height*sizeof(T));
	}

	template <typename T> Array<T> & Array<T>::operator = (const Array<T> & source)
	{
		width = source.width;
		height = source.height;
		buffer = new T[width*height];
		std::memcpy(buffer, source.buffer, width*height*sizeof(T));
		return *this;
	}

	template <typename T> bool Array<T>::operator == (const Array<T> & right) const
	{
		if (width != right.width || height != right.height) return false;
		for (int i = 0; i < width*height; i++)
		{
			if ((*(buffer + i)) != (*(right.buffer + i))) return false;
		}
		return true;
	}

	template <typename T> void Array<T>::resize(unsigned int new_width, unsigned int new_height)
	{
		if (new_height <= height)
		{
			height = new_height;
		}
		T *mArray = new T[new_width*new_height];//the new array
		T *pArray = mArray;//pointer to the new array(pArray is going to get changed,so we keep mArray intact)
		std::memset(mArray, 0.0f, new_width*new_height*sizeof(T));//sets all the elements of the array to 0
		T *pBuff = buffer;//we'll delete the buffer's array later but because we'll be changing buffer we're using this pointer in order to know it's location
		if (new_width <= width)
		{//if our new width is less than the current one,the program copies the bytes that we need from buffer,and then increases the buffer 
			for (unsigned int i = 0; i <height; i++)
			{
				std::memcpy(pArray, buffer, sizeof(T)*new_width);
				buffer = buffer + width;
				pArray = pArray + new_width;
				if (i == 0) //we figured that if we didn't do this then both arrays would go out of bounds 
				{
					pArray--;
					buffer--;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < height; i++)
			{//same concept as before,but this time the new_width is bigger than the current one,so we can't just add new_width to the buffer because it will go out of bounds
				std::memcpy(pArray, buffer, sizeof(T)*width);
				buffer = buffer + width;
				pArray = pArray + new_width;
				if (i == 0)
				{
					pArray--;
					buffer--;
				}
			}
		}
		delete[] pBuff;
		width = new_width;
		height = new_height;
		buffer = mArray;
	}

	template <typename T> Array<T>::~Array()
	{
		delete[] buffer;
	}



} // namespace math

#endif