#include "Database.h"
#include <cctype>

Database d;

string Database::dbName = "Database";

inline void ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

string toLowerCase(string s)
{
	for (size_t i = 0; i < s.size(); ++i)
	{
		s.at(i) = tolower(s.at(i));
	}
	return s;
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

bool areNumbersEqual(double n, double n2, size_t precision)
{
	double factor = pow(10, precision);
	return (int)(n * factor) == (int)(n2 * factor);
}

void IntrerpretareComanda(string comanda)
{
	string tableName;

	string delimiter = " ";
	size_t pos = comanda.find(delimiter);
	if (pos == std::string::npos)
	{
		throw Exception("Comanda invalida!");
	}

	string token = comanda.substr(0, pos);
	comanda.erase(0, pos + delimiter.length());

	token = toLowerCase(token);
	if (!token.compare("insert"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("into"))
					{
						throw Exception("Eroare in sintaxa comenzii INSERT! -> into");
					}

					break;
				}
				case 1:
				{
					tableName = token;
					break;
				}
				default: break;
			}
			string temp = comanda;
			token = toLowerCase(token);
			if (!temp.substr(0, 7).compare("values("))break;
			++i;

		}

		if (!d.getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		if (i != 1)
		{
			throw Exception("Eroare in sintaxa comenzii INSERT!");
		}

		token = comanda;
		token = toLowerCase(token);
		if (token.substr(0, 7).compare("values("))
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> values");
		}
		if (token.at(token.length() - 1) != ')')
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> paranteza");
		}

		token = token.substr(7, token.length() - 1);
		token = token.substr(0, token.length() - 1);

		if (token.length() == 0)
		{
			throw Exception("Eroare in sintaxa comenzii INSERT! -> valori nule");
		}

		string delimiter2 = ",";

		vector<string> values;

		pos = 0;
		string token2;

		ltrim(token);

		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(token2);
			token.erase(0, pos + delimiter2.length() + 1);
		}
		values.push_back(token);
		d.getAtByName(tableName)->addRecord(values);
	}
	else if (!token.compare("update"))
	{
		size_t i = 0;
		string celula, val, celula2, val2;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					tableName = token;
					if (!d.getAtByName(tableName))
					{
						string tmp = "Nu exista tabelul " + tableName + " !";
						throw Exception(tmp.c_str());
					}

					break;
				}
				case 1:
				{
					token = toLowerCase(token);
					if (token.compare("set"))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> set");
					}
					break;
				}
				case 2:
				{
					if (!d.getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii UPDATE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}

					celula = token;

					break;
				}
				case 3:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> primul =");
					}
					break;
				}
				case 4:
				{
					val = token;
					break;
				}
				case 5:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> where");
					}
					break;
				}
				case 6:
				{
					if (!d.getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii UPDATE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}
					celula2 = token;
					break;
				}
				case 7:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii UPDATE! -> al doilea =");
					}
					break;
				}
				default: break;
			}
			++i;

		}

		if (i != 8)
		{
			throw Exception("Eroare in sintaxa comenzii UPDATE!");
		}

		val2 = comanda;

		d.getAtByName(tableName)->setInregistrareByCondition(celula, val, celula2, val2);
		auto x = d.getAtByName(tableName)->getCelule();
	}
	else if (!token.compare("delete"))
	{
		size_t i = 0;
		string celula, val;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("from"))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> from");
					}

					break;
				}
				case 1:
				{
					tableName = token;
					if (!d.getAtByName(tableName))
					{
						string tmp = "Nu exista tabelul " + tableName + " !";
						throw Exception(tmp.c_str());
					}

					break;
				}
				case 2:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> where");
					}
					break;
				}
				case 3:
				{
					if (!d.getAtByName(tableName)->checkForCelula(token))
					{
						string tmp = "Eroare in sintaxa comenzii DELETE! -> nu exista celula " + token;
						throw Exception(tmp.c_str());
					}

					celula = token;

					break;
				}
				case 4:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii DELETE! -> =");
					}
					break;
				}
				default: break;
			}
			++i;

		}

		if (i != 5)
		{
			throw Exception("Eroare in sintaxa comenzii DELETE!");
		}

		val = comanda;

		d.getAtByName(tableName)->deleteRecords(celula, val);
	}
	else if (!token.compare("display"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii DISPLAY! -> table");
					}

					tableName = comanda;

					break;
				}
				default: break;
			}

			++i;

			if (i > 1)
			{
				throw Exception("Eroare in sintaxa comenzii DISPLAY! -> prea multe argumente");
			}
		}

		if (!d.getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		vector<string> filters;
		d.getAtByName(tableName)->printRecords(filters);
	}
	else if (!token.compare("drop"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii DROP! -> table");
					}

					tableName = comanda;

					break;
				}
				default: break;
			}

			++i;

			if (i > 1)
			{
				throw Exception("Eroare in sintaxa comenzii DROP! -> prea multe argumente");
			}
		}

		if (!d.getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		d.deleteAtByName(tableName);
	}
	else if (!token.compare("select"))
	{
		size_t i = 0;
		string celula, val;
		vector<string> values;
		bool all = false, whereToken = false;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (!token.compare("all"))
					{
						all = true;
					}
					else
					{
						string delimiter2 = ",";

						size_t pos2 = comanda.find(delimiter2);
						string token2;

						if (pos2 != string::npos)
						{
							values.push_back(token.substr(0, token.size() - 1));

							ltrim(token);
							while ((pos2 = comanda.find(delimiter2)) != string::npos) {
								token2 = comanda.substr(0, pos2);
								values.push_back(token2);
								comanda.erase(0, pos2 + delimiter2.length() + 1);
							}
							values.push_back(comanda.substr(0, comanda.find(" ")));
						}
						else
						{
							if (token.at(token.size() - 1) == ',')token.erase(token.size() - 1, token.size());
							values.push_back(token);

							string next = comanda.substr(0, comanda.find(" "));
							next = toLowerCase(next);

							if (next.compare("from"))
							{
								values.push_back(next);
								comanda = comanda.substr(comanda.find(" ") + 1, comanda.size());
							}
						}
					}

					break;
				}
				case 1:
				{
					token = toLowerCase(token);
					if (token.compare("from"))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> from");
					}

					break;
				}
				case 2:
				{
					tableName = token;
					break;
				}
				case 3:
				{
					token = toLowerCase(token);
					if (token.compare("where"))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> where");
					}

					whereToken = true;

					break;
				}
				case 4:
				{
					celula = token;

					break;
				}
				case 5:
				{
					token = toLowerCase(token);
					if (token.compare("="))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> =");
					}

					break;
				}
				default: break;
			}
			if (all)
			{
				if (i == 1)
				{
					tableName = comanda;
				}
				else if (i == 5)
				{
					val = comanda;
				}
			}
			else
			{
				if (i == 1)
				{
					if (!whereToken)
					{
						tableName = comanda;
					}
				}
				else if (i == 5)
				{
					val = comanda;
				}
			}
			++i;

		}

		if (!d.getAtByName(tableName))
		{
			string tmp = "Nu exista tabelul " + tableName + " !";
			throw Exception(tmp.c_str());
		}

		if (i != 6 && i != 2)
		{
			throw Exception("Eroare in sintaxa comenzii SELECT!");
		}

		if (all)
		{
			if (!whereToken)
			{
				//vector<string> filters;
				d.getAtByName(tableName)->printRecords(values);
			}
			else
			{
				if (!d.getAtByName(tableName)->getCelulaByName(celula))
				{
					string tmp = "Eroare in sintaxa comenzii SELECT! -> nu exista celula " + celula;
					throw Exception(tmp.c_str());
				}

				bool number = false;
				TipCelula tipCelulaCautata = d.getAtByName(tableName)->getTipCelulaByName(celula);
				if (tipCelulaCautata == TipCelula::NUMBER)
				{
					if (!is_number(val))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> tipul coloanei nu se potriveste");
					}
					number = true;
				}

				vector<Celula*> celule = d.getAtByName(tableName)->getCelule();
				size_t len = celule.size(), index;
				for (size_t i = 0; i < len; ++i)
				{
					if (!celule.at(i)->getNume().compare(celula))
					{
						index = i;
						break;
					}
				}
				//vector<string> filters;

				d.getAtByName(tableName)->printRecords(values, Filter(celula, val), index);
			}
		}
		else
		{
			size_t valuesSize = values.size();
			for (size_t i = 0; i < valuesSize; ++i)
			{
				if (!d.getAtByName(tableName)->getCelulaByName(values.at(i)))
				{
					throw Exception("Eroare in sintaxa comenzii SELECT! -> nu exista coloanele selectate");
				}
			}
			if (!whereToken)
			{
				d.getAtByName(tableName)->printRecords(values);
			}
			else
			{
				if (!d.getAtByName(tableName)->getCelulaByName(celula))
				{
					string tmp = "Eroare in sintaxa comenzii SELECT! -> nu exista celula " + celula;
					throw Exception(tmp.c_str());
				}

				bool number = false;
				TipCelula tipCelulaCautata = d.getAtByName(tableName)->getTipCelulaByName(celula);
				if (tipCelulaCautata == TipCelula::NUMBER)
				{
					if (!is_number(val))
					{
						throw Exception("Eroare in sintaxa comenzii SELECT! -> tipul coloanei nu se potriveste");
					}
					number = true;
				}

				vector<Celula*> celule = d.getAtByName(tableName)->getCelule();
				size_t len = celule.size(), index;
				for (size_t i = 0; i < len; ++i)
				{
					if (!celule.at(i)->getNume().compare(celula))
					{
						index = i;
						break;
					}
				}

				d.getAtByName(tableName)->printRecords(values, Filter(celula, val), index);
			}
		}
	}
	else if (!token.compare("create"))
	{
		size_t i = 0;
		while ((pos = comanda.find(delimiter)) != string::npos) {
			token = comanda.substr(0, pos);
			comanda.erase(0, pos + delimiter.length());
			switch (i)
			{
				case 0:
				{
					token = toLowerCase(token);
					if (token.compare("table"))
					{
						throw Exception("Eroare in sintaxa comenzii CREATE! -> table");
					}

					break;
				}
				case 1:
				{
					tableName = token;
					break;
				}
				default: break;
			}
			string temp = comanda;
			temp = toLowerCase(temp);
			if (!temp.substr(0, 7).compare("values("))break;
			++i;

		}

		if (i != 4 && i != 1)
		{
			throw Exception("Eroare in sintaxa comenzii CREATE!");
		}

		if (i == 4)
		{
			size_t len = d.getId();
			for (size_t i = 0; i < len; ++i)
			{
				if (!strcmp(d.getAt(i)->getNumeTabela(), tableName.c_str()))
				{
					return;
				}
			}
		}

		token = comanda;
		token = toLowerCase(token);
		if (token.substr(0, 7).compare("values("))
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> values");
		}
		if (token.at(token.length() - 1) != ')')
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> paranteza");
		}

		token = token.substr(7, token.length() - 1);
		token = token.substr(0, token.length() - 1);

		if (token.length() == 0)
		{
			throw Exception("Eroare in sintaxa comenzii CREATE! -> valori nule");
		}

		string delimiter2 = ",";

		vector<Celula*> values;

		pos = 0;
		string token2;

		ltrim(token);

		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(new Celula(token2.substr(0, token2.find(" ")), token2.substr(token2.find(" ") + 1, token2.length() - 1)));
			token.erase(0, pos + delimiter2.length() + 1);
		}
		values.push_back(new Celula(token.substr(0, token.find(" ")), token.substr(token.find(" ") + 1, token.length() - 1)));

		d.add(new Tabela(tableName.c_str(), d.getId(), values));
	}
	else
	{
		throw Exception("Comanda inexistenta!");
	}
}