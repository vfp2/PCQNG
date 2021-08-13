#include "StdAfx.h"
#include "wordcorrector.h"

CWordCorrector::CWordCorrector(void)
{
	Reset();
}

CWordCorrector::~CWordCorrector(void)
{
}

// Sends a 32 bit word through the corrector
BYTE CWordCorrector::Run(BYTE InWord8)
{
	BYTE OutWord = InWord8;

	for ( ULONG i=0; i<m_Tabs; i++ )
	{
		OutWord ^= ShiftReg.Read( m_Tab[i] );
	}

	ShiftReg.Feed( OutWord );

	return OutWord;
}

// Sets tab for XORing
void CWordCorrector::SetTab(ULONG TabIndex)
{
	m_Tab[m_Tabs] = TabIndex;
	m_Tabs++;
}

// Clears all tabs
void CWordCorrector::ClearTabs(void)
{
	for ( int i=0; i<10; i++ )
		m_Tab[i] = 0;

	m_Tabs = 0;
}

void CWordCorrector::Reset(void)
{
	ClearTabs();

	ShiftReg.SetLength(112);

	// Word Corrector Tabs
	SetTab(10);
	SetTab(10+13);
	SetTab(10+13+17);
	SetTab(10+13+17+19);
	SetTab(10+13+17+19+23);
	SetTab(10+13+17+19+23+29);
}
