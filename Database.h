#pragma once
#include "Utils.h"

class Tabela
{
	char numeTabela[CHAR_MAX];
	const int idTabela;
	vector<Celula*> celule;
	vector<Inregistrare*> inregistrari;
	size_t inregistrariGasite = 0;
public:

	//constructor fara parametrii
	Tabela(const char *numeTabela, int id, vector<Celula*> celule) : idTabela(id)
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

	void addRecord(vector<string> values)
	{
		size_t len = values.size();
		string tmp = "Eroare in sintaxa comenzii INSERT! -> numarul valorilor nu corespunde numarul campurilor tabelului ";
		tmp += numeTabela;
		if (len != celule.size())throw Exception(tmp.c_str());
		vector<DataCelula*> dataValues;
		for (size_t i = 0; i < len; ++i)
		{
			string val = values.at(i);
			DataCelula *dataCelula;
			if (celule.at(i)->getTipCelula() == TipCelula::NUMBER)
			{
				if (!is_number(val))
				{
					tmp = "Eroare in sintaxa comenzii INSERT! -> tipurile valorilor nu corespund tipurilor campurilor tabelului ";
					tmp += numeTabela;
					throw Exception(tmp.c_str());
				}
				double *tempVal = new double;
				*tempVal = atof(val.c_str());
				void * tempVoidVal = (void*)tempVal;
				dataCelula = new DataCelula(TipCelula::NUMBER, tempVoidVal);
			}
			else
			{
				string *tempVal = new string;
				*tempVal = val;
				void * tempVoidVal = (void*)tempVal;
				dataCelula = new DataCelula(TipCelula::TEXT, tempVoidVal);
			}
			//dataValues.push_back(celula);
			dataValues.push_back(dataCelula);
			//delete dataCelula;
		}
		inregistrari.push_back(new Inregistrare(dataValues));
		cout << "Inserarea in tabelul " << numeTabela << " a fost efectuata cu succes. ID: " << inregistrari.size() - 1 << endl;
	}

	void deleteAtIndex(size_t index)
	{
		celule.erase(celule.begin() + index);
	}

	void setAtIndex(size_t index, Celula *c)
	{
		celule.at(index) = c;
	}

	char* getNumeTabela()
	{
		return numeTabela;
	}

	Celula* getCelulaAtIndex(size_t index)
	{
		return celule.at(index);
	}

	Celula* getCelulaByName(string name)
	{
		size_t len = celule.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (!celule.at(i)->getNume().compare(name))
			{
				return celule.at(i);
			}
		}
		return nullptr;
	}

	TipCelula getTipCelulaByName(string name)
	{
		size_t len = celule.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (!celule.at(i)->getNume().compare(name))
			{
				return celule.at(i)->getTipCelula();
			}
		}
		return TipCelula::TEXT;
	}

	bool checkForCelula(string name)
	{
		size_t len = celule.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (!celule.at(i)->getNume().compare(name))
			{
				return true;
			}
		}
		return false;
	}

	void deleteRecords(string celula, string value)
	{
		size_t len = celule.size(), index;
		TipCelula tipCelula;
		for (size_t i = 0; i < len; ++i)
		{
			if (!celule.at(i)->getNume().compare(celula))
			{
				index = i;
				tipCelula = celule.at(i)->getTipCelula();
				break;
			}
		}

		bool first = false;
		len = inregistrari.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (tipCelula == TipCelula::NUMBER)
			{
				if (!areNumbersEqual(inregistrari.at(i)->getAtIndex(index)->dData, atof(value.c_str())))
				{
					continue;
				}
			}
			else
			{
				if (inregistrari.at(i)->getAtIndex(index)->sData.compare(value))
				{
					continue;
				}
			}
			if (!first)first = true;

			inregistrari.erase(inregistrari.begin() + i);
			--i;
			--len;
		}
		if (first)
		{
			cout << "Inregistrarile cu coloana '" << celula << "' cu valoarea '" << value << "' au fost sterse." << endl;
		}
		else
		{
			cout << "Nu s-a sters nimic deoarece nu exista nici o valoare '" << value << "' pe coloana '" << celula << "'. " << endl;
		}
	}

	void setInregistrareByCondition(string celula, string valueCelula, string celulaCautare, string valueCelulaCautare)
	{
		size_t len = celule.size(), index = -1, index2 = -1;
		bool foundFirst = false, foundSecond = false;
		for (size_t i = 0; i < len; ++i)
		{
			if (!celule.at(i)->getNume().compare(celula))
			{
				index = i;
				foundFirst = true;
				if (foundSecond)break;
			}
			if (!celule.at(i)->getNume().compare(celulaCautare))
			{
				index2 = i;
				foundSecond = true;
				if (foundFirst)break;
			}
		}

		bool first = false;
		len = inregistrari.size();
		for (size_t i = 0; i < len; ++i)
		{
			TipCelula tipCelulaCautare = celule.at(index2)->getTipCelula();
			if (tipCelulaCautare == TipCelula::NUMBER)
			{
				if (!areNumbersEqual(inregistrari.at(i)->getAtIndex(index2)->dData, atof(valueCelulaCautare.c_str())))
				{
					continue;
				}
			}
			else
			{
				if (inregistrari.at(i)->getAtIndex(index2)->sData.compare(valueCelulaCautare))
				{
					continue;
				}
			}
			if (!first)first = true;
			TipCelula tipCelula = celule.at(index)->getTipCelula();

			if (tipCelula == TipCelula::NUMBER)
			{
				if (!is_number(valueCelula))
				{
					throw Exception("Eroare in sintaxa comenzii UPDATE! -> tipul celulei care trebuie actualizata este diferita de tipul valorii");
				}

				double *tempVal = new double;
				*tempVal = atof(valueCelula.c_str());
				void * tempVoidVal = (void*)tempVal;

				inregistrari.at(i)->setDataAtIndex(index, tipCelula, tempVoidVal);
			}
			else
			{
				string *tempVal = new string;
				*tempVal = valueCelula;
				void * tempVoidVal = (void*)tempVal;

				inregistrari.at(i)->setDataAtIndex(index, tipCelula, tempVoidVal);
			}

		}
		if (first)
		{
			cout << "Celulele cu numele '" << celula << "' cu conditia ca celula '" << celulaCautare << "' sa aiba valoarea '" << valueCelulaCautare << "' au fost actualizate cu valoarea '" << valueCelula << "'." << endl;
		}
		else
		{
			cout << "Nu s-a actualizat nimic deoarece nu exista nici o valoare '" << valueCelulaCautare << "' pe coloana '" << celulaCautare << "'. " << endl;
		}
	}

	Inregistrare* getAtIndex(size_t index)
	{
		return inregistrari.at(index);
	}

	void printRecordAt(size_t index, vector<string> filters)
	{
		size_t filtersLen = filters.size();
		if (filtersLen)
		{
			size_t celuleLen = celule.size();
			string msg = "\nInregistrarea #";
			msg += to_string(index);
			msg += "\n";

			for (size_t i = 0; i < filtersLen; ++i)
			{
				for (size_t j = 0; j < celuleLen; ++j)
				{
					if (!celule.at(j)->getNume().compare(filters.at(i)))
					{
						if (celule.at(j)->getTipCelula() == TipCelula::NUMBER)
						{
							msg += to_string(inregistrari.at(index)->getAtIndex(j)->dData);
							msg += " | ";
						}
						else
						{
							msg += inregistrari.at(index)->getAtIndex(j)->sData;
							msg += " | ";
						}
					}
				}
			}
			msg.erase(msg.size() - 2, msg.size() - 1);
			cout << msg << endl;

		}
		else
		{
			size_t celuleLen = celule.size();
			string msg = "\nInregistrarea #";
			msg += to_string(index);
			msg += "\n";

			for (size_t i = 0; i < celuleLen; ++i)
			{
				if (celule.at(i)->getTipCelula() == TipCelula::NUMBER)
				{
					msg += to_string(inregistrari.at(index)->getAtIndex(i)->dData);
					msg += " | ";
				}
				else
				{
					msg += inregistrari.at(index)->getAtIndex(i)->sData;
					msg += " | ";
				}
			}
			msg.erase(msg.size() - 2, msg.size() - 1);
			cout << msg << endl;
		}
	}

	void printRecords(vector<string> filters, Filter filter = Filter("", ""), size_t celulaIndex = -1)
	{
		if (celulaIndex != -1 && !filter.celula.empty() && !filter.value.empty())
		{
			size_t len = inregistrari.size();
			bool first = false;
			for (size_t i = 0; i < len; ++i)
			{
				if (celule.at(celulaIndex)->getTipCelula() == TipCelula::NUMBER)
				{
					if (areNumbersEqual(inregistrari.at(i)->getAtIndex(celulaIndex)->dData, atof(filter.value.c_str())))
					{
						if (!first)
						{
							first = true;
							cout << "Se afiseaza tabelul " << numeTabela << " cu conditia ca '" << filter.celula << "' sa fie '" << filter.value << "'." << endl;
							size_t filtersLen = filters.size();
							if (filtersLen)
							{
								cout << "Se afiseaza coloanele ";
								for (size_t j = 0; j < filtersLen; ++j)
								{
									cout << filters.at(j);
									if (j != filtersLen - 1)
										cout << ", ";
								}
								cout << endl;
							}
						}
						++inregistrariGasite;
						printRecordAt(i, filters);
					}
				}
			}
		}
		else
		{
			cout << "Se afiseaza tot tabelul " << numeTabela << "." << endl;
			size_t filtersLen = filters.size();
			if (filtersLen)
			{
				cout << "Se afiseaza coloanele ";
				for (size_t j = 0; j < filtersLen; ++j)
				{
					cout << filters.at(j);
					if (j != filtersLen - 1)
						cout << ", ";
				}
				cout << endl;
			}
			size_t len = inregistrari.size();
			for (size_t i = 0; i < len; ++i)
			{
				printRecordAt(i, filters);
			}
			inregistrariGasite = len;
		}
		if (!inregistrariGasite)
		{
			cout << "Nu s-au gasit inregistrari cu coloana '" << filter.celula << "' sa aiba valoarea '" << filter.value << "'!" << endl;
		}
		else
		{
			if (inregistrariGasite != inregistrari.size())
			{
				cout << endl << "S-au gasit " << inregistrariGasite << " inregistrari cu coloana '" << filter.celula << "' avand valoarea '" << filter.value << "'." << endl;
			}
		}
		cout << endl;
		inregistrariGasite = 0;
	}

	size_t getCeluleSize()
	{
		return celule.size();
	}

	vector<Celula*> getCelule()
	{
		return celule;
	}

	size_t getLast()
	{
		return inregistrari.size() - 1;
	}

	int getId()
	{
		return idTabela;
	}
};

class Database
{
	int nextIdTabela;
	vector<Tabela*> v;
	static string dbName;
public:
	void add(Tabela *t)
	{
		v.push_back(t);
		++nextIdTabela;

		cout << "Tabelul " << t->getNumeTabela() << "(#" << nextIdTabela << ") a fost creat. Structura:" << endl;
		size_t len = t->getCeluleSize();
		vector<Celula*> celule = t->getCelule();
		for (size_t i = 0; i < len; ++i)
		{
			cout << celule.at(i)->getNume() << " -> " << celule.at(i)->getTipCelulaAsString();
			if (i != len - 1) cout << " | ";
		}
		cout << endl;
	}

	Tabela* getAt(size_t index)
	{
		return v.at(index);
	}

	Tabela* getAtByName(string name)
	{
		size_t len = v.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (!name.compare(v.at(i)->getNumeTabela())) return v.at(i);
		}
		return nullptr;
	}

	void deleteAtByName(string name)
	{
		size_t len = v.size();
		for (size_t i = 0; i < len; ++i)
		{
			if (!name.compare(v.at(i)->getNumeTabela()))
			{
				v.erase(v.begin() + i);
				break;
			}
		}
		cout << "Tabelul " << name << " a fost sters!" << endl;
	}

	int getId()
	{
		return nextIdTabela;
	}

	void deleteAt(size_t index)
	{
		v.erase(v.begin() + index);
	}
};