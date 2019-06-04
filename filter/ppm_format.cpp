#ifndef _PPM_IMPL
#define _PPM_IMPL

#include "ppm_format.h"
#include <fstream>
using namespace std;
using namespace math;

namespace imaging{

	Image * ReadPPM(const char * filename)
	{
		string word;
		unsigned int width, height, sd;
		ifstream file(filename, ios::binary); //creates the ifstream

		if (file.fail()) //if opening the file went wrong an exception is thrown
		{
			std::cerr << "Can't open file";
			return nullptr;
		}
		file >> word >> width >> height >> sd; //initialises the file's header and then checks if everything is OK 
		if (word.compare("P6"))
		{
			std::cerr << "File's not a P6 one!";
			return nullptr;
		}
		if (sd != 255)
		{
			std::cerr << "The color max value isn't 255";
			return nullptr;
		}

		file.ignore(1, '\n'); //ignores the empty line that follows after the file's width,size,type and max_value
		unsigned int size = width*height; //array's size
		char * arr = new char[3];
		Color * mArray = new Color[size];//this array will have the image's data
		for (unsigned int i = 0; i < size; i++)
		{
			file.read(arr, 3);//reads from the file byte by byte and stores it to the arr variable
			mArray[i] = Color((((unsigned char)arr[0]) / 255.0f), (((unsigned char)arr[1]) / 255.0f), (((unsigned char)arr[2]) / 255.0f)); //then it converts the arr variable into an unsigned int,divides it with 255.0f,turns it into a float number and saves it in the array
		}

		double r = 0; //these will be the image's average colors
		double g = 0;
		double b = 0;

		for (unsigned int i = 0; i < size; i = i + 1)
		{
			r = r + mArray[i].r;//adds every color of the image
			g = g + mArray[i].g;
			b = b + mArray[i].b;
		}
		r = r / (width*height);//calculating the average color
		g = g / (width*height);
		b = b / (width*height);
		cout << "Image dimensions are : " << width << " x " << height << endl;
		cout << "The average color of the image is(" << r << ", " << g << ", " << b << ")" << endl;
		Image* im = new Image(width, height, (const Color*)mArray); //creates the image pointer to be returned
		delete[] mArray;
		delete[] arr;
		return im;
	}

	//--------------------------------------------------------------------------------------------------------
	//--------------------------------------------------------------------------------------------------------

	bool WritePPM(Image & image, const char * filename)
	{
		int width = image.getWidth();
		int height = image.getHeight();
		Color* pointer = ((Color*)image.getRawDataPtr());
		if ((pointer == nullptr) || (width <= 0) || (width <= 0))return false;
		unsigned char *tArray = new unsigned char[width*height * 3];
		for (unsigned int i = 0; i < width*height * 3; i = i + 3)
		{
			tArray[i] = (*pointer).r * 255;
			tArray[i + 1] = (*pointer).g * 255;
			tArray[i + 2] = (*pointer).b * 255;
			pointer++;
		}
		ofstream file(filename, ios::binary);
		if (file.fail()) return false;
		file << "P6" << "\n" << width << "\n" << height << "\n" << 255 << "\n";
		file.write((char *)tArray, width*height * 3 * sizeof(unsigned char));
		delete[] tArray;
		return true;
	}
}
#endif
