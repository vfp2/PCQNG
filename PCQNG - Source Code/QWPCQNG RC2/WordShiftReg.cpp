#include "StdAfx.h"
#include "wordshiftreg.h"

CWordShiftReg::CWordShiftReg(void)
: m_pRegister(NULL)
{
	m_CurrentPos = 0;
	m_Length = 112;
	m_pRegister = new BYTE[m_Length];

	for ( int i=0; i<(int)m_Length; i++ )
		m_pRegister[i] = 0;
}

CWordShiftReg::~CWordShiftReg(void)
{
	if (m_pRegister!=NULL)
	{
		delete m_pRegister;
		m_pRegister = NULL;
	}
}

// Sets total length of shift register
BOOL CWordShiftReg::SetLength(ULONG Length)
{
	m_Length = Length;

	if (m_pRegister!=NULL)
		delete m_pRegister;
	m_pRegister = new BYTE[m_Length];

	for ( int i=0; i<(int)m_Length; i++ )
		m_pRegister[i] = 0;

	return TRUE;
}

// Feeds 32-bit word into register
void CWordShiftReg::Feed(BYTE InWord8)
{
	m_CurrentPos--;
	if ( m_CurrentPos<0 )
		m_CurrentPos = m_Length - 1;

	m_pRegister[m_CurrentPos] = InWord8;
}

// Reads a 32-bit word from shift reg at index
BYTE CWordShiftReg::Read(ULONG Index)
{
	// error code = 255 on Index>Length
	if ( Index >= m_Length )
		return 0xff;

	// find correct spot
	Index += m_CurrentPos;
	Index %= m_Length;

	// read
	return m_pRegister[Index];
}
