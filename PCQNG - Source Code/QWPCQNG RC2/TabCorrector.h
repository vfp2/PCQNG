//////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved.
//

// Version History:
// 2003.07.01    PAW    Creation

#pragma once

template<typename T>
class CTabCorrector
{
public:
	// ctor
	CTabCorrector(void)
	: ShiftReg(NULL)
	, Tab(NULL)
	, TotalLength(0)
	, Number (0)
	, CurrentPos(0)
	{
	}

	// dtor
	~CTabCorrector(void)
	{
		if (ShiftReg!=NULL)
		{
			delete ShiftReg;
			ShiftReg = NULL;
		}

		if (Tab!=NULL)
		{
			delete Tab;
			Tab = NULL;
		}
	}

	// Sets Number resgister lengths as given in array pTabs
	void SetRegisters(int* pTabs, int Number)
	{
		// Remember number of Tabs;
		this->Number = Number;

		// Initializa all tabs
		if (Tab!=NULL)
			delete Tab;
		Tab = new int[Number];

		TotalLength = 0;
		for (int i=0; i<Number; i++)
		{
			TotalLength += pTabs[i];
			Tab[i] = TotalLength-1;
		}

		// Make register
		if (ShiftReg!=NULL)
			delete ShiftReg;
		ShiftReg = new T[Number*TotalLength];

		// Reset all
		Reset();
	}

	void Reset()
	{
		CurrentPos = 0;
		ZeroMemory(ShiftReg, TotalLength*sizeof(T));
	}

	// Sends a 32 bit word through the corrector
	T Run(T InWord)
	{
		// XOR Tabs with input
		T OutWord = InWord;
		for ( int i=0; i<Number; i++ )
			OutWord ^= ShiftReg[(CurrentPos+Tab[i])%TotalLength];

		// Shift register to right
		CurrentPos += TotalLength-1;
		CurrentPos %= TotalLength;

		// Feed into shift register
		ShiftReg[CurrentPos] = OutWord;

		return OutWord;
	}

protected:
	T*	ShiftReg;
	int* Tab;
	int Number;
	int TotalLength;
	int CurrentPos;
};