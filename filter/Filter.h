
#ifndef _FILTER
#define _FILTER

#include <iostream>
#include <string>
using namespace math;

namespace imaging{
	class Filter
	{
	public:

		virtual void gray() = 0;

		virtual void mask(Vec3<float> var) = 0;

		virtual void blur() = 0;

		virtual void medOrDiff(int x) = 0;

		virtual float NeighborhoodBlur(unsigned int x, unsigned int y,Vec3<float> *ptr) = 0;

		virtual Vec3<float> NeighborhoodOthers(unsigned int x, unsigned int y, float *red,float *green,float *blue,int mode) = 0;

	};
}
#endif