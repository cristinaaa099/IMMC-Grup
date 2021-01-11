#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

enum TipCelula
{
	NUMBER,
	TEXT
};

class Exception;
class Celula;
class Inregistrare;
class Tabela;
class Database;
struct Filter;

using namespace std;

constexpr size_t COMPARE_PRECISION = 4;

void IntrerpretareComanda(string comanda);

string toLowerCase(string s);

inline void ltrim(std::string &s);

bool is_number(const std::string& s);
bool areNumbersEqual(double n, double n2, size_t precision = COMPARE_PRECISION);

union DataCelula
{
	double dData;
	string sData;
	DataCelula(TipCelula tipCelula, void* data)
	{
		memset(this, 0, sizeof(DataCelula));

		if (tipCelula == TipCelula::TEXT)
		{
			string * temp = reinterpret_cast<string*>(data);
			sData = string();
			sData = *temp;
		}
		else
		{
			double *temp = reinterpret_cast<double*>(data);
			dData = *temp;
		}
	}
	~DataCelula() {}
};

#include "DataCelula.h"
#include "Exception.h"
#include "Filter.h"
#include "Celula.h"
#include "Inregistrare.h"
#include "Tabela.h"