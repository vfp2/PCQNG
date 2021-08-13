#include "StdAfx.h"
#include "origwordcorrector.h"

COrigWordCorrector::COrigWordCorrector(void)
{
	Reset();
}

COrigWordCorrector::~COrigWordCorrector(void)
{
}

// Sends an 8 bit word through the corrector
BYTE COrigWordCorrector::Run(BYTE InWord8)
{
	BYTE	OutWord;	// Return Value

	BYTE	XVal;		// XOR result
	BYTE	i;			// Universal index

	// Remeber place to insert new word
	pInReg8 = pSReg8Pos[CurrentReg8];

	// Calculate OutWord = XOR all of 0th words of all regs
	XVal = *pSReg8Pos[0];
	// After XOR, rotate register to right (=advance pointer to left)
	if ( pSReg8Pos[0] <= &SReg8[0][0] )
		pSReg8Pos[0] = &SReg8[0][SReg8Length[0]-1];
	else
		pSReg8Pos[0]--;

	for ( i=1; i<6; i++ )
	{
		XVal ^= *pSReg8Pos[i];

		// After XOR, rotate register to right (=advance pointer to left)
		if ( pSReg8Pos[i] <= &SReg8[i][0] )
			pSReg8Pos[i] = &SReg8[i][SReg8Length[i]-1];
		else
			pSReg8Pos[i]--;
	}

	OutWord = XVal;

	// Insert word into current register at 0th position (last pointer pos before rotation)
	XVal ^= InWord8; // Mix with InWord
	*pInReg8 = XVal;

	// Cycle through current register, then rotate to new current reg
	CurrentPos8--;	// Cycle
	// At end of cycle? Then rotate to new current register.
	if ( CurrentPos8 == 0 )
	{
		CurrentReg8++;
		if ( CurrentReg8>5 ) CurrentReg8 = 0;
		CurrentPos8 = SReg8Length[CurrentReg8];
	}

	return OutWord;
}

void COrigWordCorrector::Reset(void)
{
	int i;
	int j;
	for ( i=0; i<=5; i++ )
	{
		for ( j=0; j<=28; j++ )
		{
			SReg8[i][j] = 0;
		}
	}

	SReg8Length[0] = 11;
	SReg8Length[1] = 13;
	SReg8Length[2] = 17;
	SReg8Length[3] = 19;
	SReg8Length[4] = 23;
	SReg8Length[5] = 29;

	CurrentReg8 = 0;
	CurrentPos8 = SReg8Length[0];

	for ( i=0; i<=5; i++ )
	{
		pSReg8Pos[i] = &SReg8[i][0];
	}
}
