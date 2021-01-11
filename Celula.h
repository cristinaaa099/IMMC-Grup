#pragma once
#include "Utils.h"

class Celula
{
	string nume;
	TipCelula tipCelula;
public:
	Celula(string nume, string tipCelula)
	{
		if (!toLowerCase(tipCelula).compare("number") || !toLowerCase(tipCelula).compare("numeric")) this->tipCelula = TipCelula::NUMBER;
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