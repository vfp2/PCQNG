#pragma once

#include "BitShiftReg.h"

class CBitCorrector
{
public:
	CBitCorrector(void);
	~CBitCorrector(void);

	// Sends a bit (encoded in single byte) through the bit corrector, returns corrected bit
	BYTE Run(BYTE InBit);

	// Sets a tab for XORing
	void SetTab(ULONG TabIndex);
	// Clears all XORing tabs
	void ClearTabs(void);

protected:
	ULONG	m_Tab[10];
	ULONG	m_Tabs;
	CBitShiftReg ShiftReg;
public:
	void Reset(void);
};