#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

enum TipCelula
{
	NUMBER,
	TEXT
};

class Exception : public exception
{
	std::string _msg;
public:
	Exception()
	{

	}
	Exception(const char* message) : exception(message)
	{
		_msg = message;
	}

	virtual const char* what() const noexcept override
	{
		return _msg.c_str();
	}
};


class Celula
{
	string nume;
	TipCelula tipCelula;
public:
	Celula(string nume, string tipCelula)
	{
		if (!tipCelula.compare("NUMBER")) this->tipCelula = TipCelula::NUMBER;
		else this->tipCelula = TipCelula::TEXT;
		this->nume = nume;
	}

	Celula& operator=(const Celula& c)
	{
		this->nume = c.nume;
		this->tipCelula = c.tipCelula;
		return *this;
	}

	const bool operator < (const Celula &c) const {
		return (nume < c.nume);
	}

	string getNume()
	{
		return nume;
	}

	TipCelula getTipCelula()
	{
		return tipCelula;
	}

	string getTipCelulaAsString()
	{
		return tipCelula == TipCelula::NUMBER ? "NUMBER" : "TEXT";
	}
};

class Inregistrare
{
	map<Celula, string> m;
public:
	Inregistrare(vector<Celula> v, string t)
	{
		for (size_t i = 0; i < v.size(); ++i)
		{
			m.insert(pair<Celula, string>(v[i], t));
		}
	}

	void setAtIndex(size_t index, string t)
	{
		auto it = m.begin();
		advance(it, index);
		it->second = t;
	}

	string getAtIndex(size_t index)
	{
		auto it = m.begin();
		advance(it, index);
		return it->second;
	}
};

//creare tabela

class Tabela
{
	static char numeTabela[CHAR_MAX];
	const int idTabela;
	vector<Celula> celule;
	vector<Inregistrare> inregistrari;
public:



	//constructor fara parametrii
	Tabela(const char *numeTabela, int id, vector<Celula> celule) : idTabela(id)
	{
		strcpy(this->numeTabela, numeTabela);
		this->celule = celule;
	}


	//operatorul =
	Tabela& operator=(const Tabela& t)
	{
		strcpy(this->numeTabela, t.numeTabela);

		this->celule = t.celule;
		return *this;
	}
	~Tabela()
	{

	}

	//setterii si getteri

	void deleteAtIndex(size_t index)
	{
		celule.erase(celule.begin() + index);
	}

	void setAtIndex(size_t index, Celula c)
	{
		celule.at(index) = c;
	}

	Celula getAtIndex(size_t index)
	{
		return celule.at(index);
	}

	vector<Celula> getCelule()
	{ 
		return celule;
	}

	int getId()
	{
		return idTabela;
	}
};

class Database
{
	static int nextIdTabela;
	static vector<Tabela> v;
public:
	static void add(Tabela t)
	{
		v.push_back(t);
		++nextIdTabela;
	}

	Tabela getAt(size_t index)
	{
		return v.at(index);
	}

	static int getId()
	{
		return ++nextIdTabela;
	}

	void deleteAt(size_t index)
	{
		v.erase(v.begin() + index);
	}
};

char asciitolower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
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

	transform(token.begin(), token.end(), token.begin(), asciitolower);
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
					transform(token.begin(), token.end(), token.begin(), asciitolower);
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
			transform(temp.begin(), temp.end(), temp.begin(), asciitolower);
			if (!temp.substr(0, 7).compare("values("))break;
			++i;

		}
		token = comanda;
		transform(token.begin(), token.end(), token.begin(), asciitolower);
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

		vector<Celula> values;

		pos = 0;
		string token2;
		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(Celula(token2.substr(0, token2.find(" ")), token2.substr(token2.find(" "), token2.length() - 1)));
			token.erase(0, pos + delimiter2.length());
		}
		values.push_back(Celula(token.substr(0, token.find(" ")), token.substr(token.find(" "), token.length() - 1)));
	}
	else if (!token.compare("delete"))
	{

	}
	else if (!token.compare("update"))
	{

	}
	else if (!token.compare("select"))
	{

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
					transform(token.begin(), token.end(), token.begin(), asciitolower);
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
			transform(temp.begin(), temp.end(), temp.begin(), asciitolower);
			if (!temp.substr(0, 7).compare("values("))break;
			++i;

		}
		if (i == 4)
		{
			//verificam daca exista
		}
		else
		{
			//cream
		}
		token = comanda;
		transform(token.begin(), token.end(), token.begin(), asciitolower);
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

		vector<Celula> values;

		pos = 0;
		string token2;
		while ((pos = token.find(delimiter2)) != string::npos) {
			token2 = token.substr(0, pos);
			values.push_back(Celula(token2.substr(0, token2.find(" ")), token2.substr(token2.find(" "), token2.length() - 1)));
			token.erase(0, pos + delimiter2.length());
		}
		values.push_back(Celula(token.substr(0, token.find(" ")), token.substr(token.find(" "), token.length() - 1)));

		//Database::add(Tabela(tableName.c_str(), Database::getId(), values));

	}
	else
	{
		throw Exception("Comanda inexistenta!");
	}
}