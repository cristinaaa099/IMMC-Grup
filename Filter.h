#pragma once
#include "Utils.h"

struct Filter
{
	string celula;
	string value;
	Filter()
	{

	}

	Filter(string celula, string value)
	{
		this->celula = celula;
		this->value = value;
	}
};