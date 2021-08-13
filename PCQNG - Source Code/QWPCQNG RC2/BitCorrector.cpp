#include "StdAfx.h"
#include "bitcorrector.h"

CBitCorrector::CBitCorrector(void)
{
	Reset();
}

CBitCorrector::~CBitCorrector(void)
{
}

// Sends a bit (encoded in single byte) through the bit corrector, returns corrected bit
BYTE CBitCorrector::Run(BYTE InBit)
{
	BYTE OutBit = InBit;

	for ( ULONG i=0; i<m_Tabs; i++ )
	{
		OutBit ^= ShiftReg.Read( m_Tab[i] );
	}

	ShiftReg.Feed( OutBit );

	return OutBit&0x1;
}
// Sets a tab for XORing
void CBitCorrector::SetTab(ULONG TabIndex)
{
	m_Tab[m_Tabs] = TabIndex;
	m_Tabs++;
}

// Clears all XORing tabs
void CBitCorrector::ClearTabs(void)
{
	for ( int i=0; i<10; i++ )
		m_Tab[i] = 0;

	m_Tabs = 0;
}

void CBitCorrector::Reset(void)
{
	ClearTabs();

	ShiftReg.SetLength(311);
	// Bit Corrector Tabs
	SetTab(30);
	SetTab(30+37);
	SetTab(30+37+41);
	SetTab(30+37+41+43);
	SetTab(30+37+41+43+47);
	SetTab(30+37+41+43+47+53);
	SetTab(30+37+41+43+47+53+59);
}
