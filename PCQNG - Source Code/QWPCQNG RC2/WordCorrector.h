#pragma once

#include "WordShiftReg.h"

class CWordCorrector
{
public:
	CWordCorrector(void);
	~CWordCorrector(void);

	// Sends a 32 bit word through the corrector
	BYTE Run(BYTE InWord8);

	// Sets tab for XORing
	void SetTab(ULONG TabIndex);
	// Clears all tabs
	void ClearTabs(void);

protected:
	ULONG	m_Tab[10];
	ULONG	m_Tabs;
	CWordShiftReg ShiftReg;
public:
	void Reset(void);
};
