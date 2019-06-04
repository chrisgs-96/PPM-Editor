#ifndef _IM_IMPLEMENTATION
#define _IM_IMPLEMENTATION

#include "ppm_format.h"
#include "Image.h"
#include "algorithm"
using namespace math;

namespace imaging{

	Image::Image(unsigned int x, unsigned int y) : Array(x, y) {}

	Image::Image() : Array(0, 0){}

	Image::Image(const Image &src) : Array(src) {}

	Image::Image(unsigned int x, unsigned int y, const Color * data) : Array(x, y)
	{
		this->setData(data);
	}

	Color Image::getPixel(unsigned int x, unsigned int y) const
	{
		if (y < height && y >= 0 && x >= 0 && x < width)
		{
			return operator() (x, y);
		}
		else
		{
			return (0, 0, 0);
		}
	}

	void Image::setPixel(unsigned int x, unsigned int y, Color & value)
	{
		if (y < height && y >= 0 && x >= 0 && x < width)
		{
			operator() (x, y) = value;
		}
	}

	void Image::setData(const Color * & data_ptr)
	{
		if (width == 0 || height == 0 || data_ptr == nullptr)return;
		Color *pArr = new Color[width*height];
		std::memcpy(pArr, data_ptr, width*height*sizeof(Color));
		buffer = pArr;
	}

	bool Image::operator << (std::string filename)
	{
		Image* img = ReadPPM(filename.c_str());
		this->width = img->getWidth();
		this->height = img->getHeight();
		const Color* ptr = (Color *)(img->getRawDataPtr());
		this->setData(ptr);
		delete img;
		return true;
	}

	bool Image::operator >> (std::string filename)
	{
		return WritePPM(*this, filename.c_str());
	}

	void Image::gray()
	{
		Color temp;
		double grayscale;
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = 0; j < width; j++)
			{
				temp = getPixel(j, i);
				grayscale = (temp.r + temp.g + temp.b) / 3;
				temp = (grayscale, grayscale, grayscale);
				setPixel(j, i, temp);
			}
		}
	}

	void Image::mask(Vec3<float> var)
	{
		Color temp;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				temp = getPixel(j, i);
				temp = temp*var;
				setPixel(j, i, temp);
			}
		}
	}

	float Image::NeighborhoodBlur(unsigned int x, unsigned int y, Vec3<float> *ptr)
	{
		int N = 0;
		int index = 0;
		for (int i = -1; i <= 1; i++)
		{
			for(int j = -1; j <= 1; j++)
			{
				if (x + j >= 0 && x + j < width && y+i>=0 && y+i < height) N++;
				ptr[index] = this->getPixel(x + j, y + i);
				index++;
			}
		}
		return N;
	}

	Color Image::NeighborhoodOthers(unsigned int x, unsigned int y, float* red, float* green, float* blue,int mode)//1 is for median,2 is for the other one
	{
		int N = 0;
		Color temp = (0, 0, 0);
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (x + j >= 0 && x + j < width && y + i >= 0 && y + i < height)
				{
					temp = getPixel(x + j, y + i);
					red[N] = temp.r;
					green[N] = temp.g;
					blue[N] = temp.b;
					N++;
				}
			}
		}
		std::sort(red, red + N);
		std::sort(blue, blue + N);
		std::sort(green, green + N);
		if (mode == 1) return Color((red[(N-1) / 2]), green[(N-1) / 2], blue[(N-1) / 2]);
		else if (mode == 2)
		{
			float r = red[N - 1] - red[0];
			float g = green[N - 1] - green[0];
			float b = blue[N - 1] - blue[0];
			return (Color(r, g, b));
		}
	}


	void Image::blur()
	{
		float N;
		Image* im = new Image(*this);
		Color temp;
		Color* mArray = new Color[9];
		for (unsigned int i = 0; i < height; i++)
		{
			for (unsigned int j = 0; j < width; j++)
			{
				N=im->NeighborhoodBlur(j, i,mArray);
				for (int c = 0; c < 9; c++)
				{
					temp = temp + mArray[c];
				}
				temp = temp / N;
				setPixel(j, i, temp);
				temp = (0, 0, 0);
			}
		}
		delete im;
		delete[] mArray;
	}

	void Image::medOrDiff(int x)
	{
		Color temp = (0, 0, 0);
		float* red = new float[9];
		int mode = x;
		float* green = new float[9];
		float* blue = new float[9];
		Image* im = new Image(*this);
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				temp = im->NeighborhoodOthers(j, i, red, green, blue, mode);
				this->setPixel(j, i, temp);
			}
		}
		delete[] red, green, blue;
		delete im;
	}



}

#endif