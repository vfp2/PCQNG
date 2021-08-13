#pragma once

class COrigWordCorrector
{
public:
	COrigWordCorrector(void);
	~COrigWordCorrector(void);
	// Sends an 8 bit word through the corrector
	BYTE Run(BYTE InWord8);

protected:
	BYTE	SReg8[6][29];
	BYTE*	pSReg8Pos[6];
	BYTE*	pInReg8;
	BYTE	SReg8Length[6];
	BYTE	CurrentReg8;
	BYTE	CurrentPos8;
public:
	void Reset(void);
};
