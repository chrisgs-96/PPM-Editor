#include "ppm_format.h"
#include <string>
#include <iostream>
using namespace std;
using namespace imaging;
using namespace math;
//#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

int main(int argc, char * argv[])
{
	string s;
	if (argc >= 2)
	{
		s = argv[argc - 1];
		Image* sd = new Image();
		if (!(*sd << s))
		{
			cout << "File failed to open." << endl;
			delete sd;
			return 0;
		}
		float r, g, b;
		int count = 1;
		while (count < (argc - 1))
		{
			s = argv[count];
			if (s.compare("-f") == 0)
			{
				count++;
				s = argv[count];
				if (s.compare("blur")==0) sd->blur();
				else if (s.compare("gray") == 0) sd->gray();
				else if (s.compare("diff") == 0) sd->medOrDiff(2);
				else if (s.compare("median") == 0) sd->medOrDiff(1);
				else if (s.compare("color") == 0)
				{
					try
					{
						count++;
						r = std::stof(argv[count]);
						count++;
						g = std::stof(argv[count]);//na kanei kapws error checking
						count++;
						b = std::stof(argv[count]);
						sd->mask(Color(r, g, b));
					}
					catch (...)
					{
						cout << "Error in reading the mask's color,terminating program...";
						delete sd;
						return 0;
					}

				}
				else
				{
					cout << "No filter found.exiting..." << endl;
					delete sd;
					return 0;
				}
				count++;
			}
			else
			{
				cout << "No -f found before the filter,exiting..." << endl;
				delete sd;
				return 0;
			}
		}
		s = argv[argc - 1];
		string sub = s.substr(s.length() - 4,s.length() - 1);
		if (sub.compare(".ppm") == 0)
		{
			s.insert(s.length() - 4, ".filtered");
		}
		else
		{
			s.insert(s.length() - 1, ".filtered");
		}
		if ((*sd) >> s.c_str())	cout << "Image written to " << s << endl;
		else cout << "Image not written,an error occured" << endl;
		delete sd;
	}
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}