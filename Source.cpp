#include "Database.h"
#include <stdlib.h>

extern Database d;

int main(int argc, char* argv[])
{
	try
	{
		if (argc > 1)
			for (int i = 1; i < argc; ++i)
			{
				ifstream file(argv[i]);
				string data;
				while (getline(file, data))
				{
					IntrerpretareComanda(data);
				}
			}
	}
	catch (Exception &e)
	{
		cout << e.what() << endl;
	}

	return 0;
}