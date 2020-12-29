#include "Database.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{ 
	try
	{
		if (argc == 1) throw Exception("Trebuie cel putin 1 fisier specificat!");
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