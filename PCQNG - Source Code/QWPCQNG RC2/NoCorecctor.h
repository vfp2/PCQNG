#pragma once
#include "regcorrector.h"

class CNoCorecctor :
	public CRegCorrector<T>
{
public:

	CNoCorecctor(void)
	{
	}

	~CNoCorecctor(void)
	{
	}

	// The InWord equals the outword = no correction
	virtual T Run(T InWord)
	{
		return InWord;
	}
};
