#include "StdAfx.h"
#include "bitshiftreg.h"

CBitShiftReg::CBitShiftReg(void)
: m_pRegister(NULL)
{
	m_CurrentPos = 0;
	m_Length = 311;
	m_pRegister = new unsigned char[m_Length];

	for ( int i=0; i<(int)m_Length; i++ )
		m_pRegister[i] = 0;
}

CBitShiftReg::~CBitShiftReg(void)
{
	if (m_pRegister!=NULL)
	{
		delete m_pRegister;
		m_pRegister = NULL;
	}
}

// Sets total length of shift register
BOOL CBitShiftReg::SetLength(ULONG Length)
{
	m_Length = Length;

	if (m_pRegister!=NULL)
		delete m_pRegister;
	m_pRegister = new unsigned char[m_Length];

	for ( int i=0; i<(int)m_Length; i++ )
		m_pRegister[i] = 0;

	m_CurrentPos = 0;

	return TRUE;
}

// Feeds a bit encoded as a byte into the shift register
void CBitShiftReg::Feed(unsigned char InBit)
{
	m_CurrentPos--;
	if ( m_CurrentPos<0 )
		m_CurrentPos = m_Length - 1;

	m_pRegister[m_CurrentPos] = InBit;
}

// Reads a bit from the index indicated in shift reg
unsigned char CBitShiftReg::Read(ULONG Index)
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
