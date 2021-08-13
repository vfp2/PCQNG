#pragma once

// Use: create and array

template<typename T>
class CRegCorrector
{
public:

	CRegCorrector(void)
	: SRegLength(NULL)
	, pSRegPos(NULL)
	, SReg(NULL)
	, pInReg(NULL)
	, CurrentReg(0)
	, CurrentPos(0)
	, MaxLength(0)
	{
	}

	~CRegCorrector(void)
	{
		if (SRegLength!=NULL)
		{
			delete SRegLength;
			SRegLength = NULL;
		}

		if (pSRegPos!=NULL)
		{
			delete pSRegPos;
			pSRegPos = NULL;
		}

		if (SReg!=NULL)
		{
			delete SReg;
			SReg = NULL;
		}
	}

	// Sends an 8 bit word through the corrector
	virtual T Run(T InWord)
	{
		T	XVal;		// XOR result, & Return Value
		T	i;			// Universal index

		// Remeber place to insert new word
		pInReg = pSRegPos[CurrentReg];

		// Calculate OutWord = XOR all of 0th words of all regs
		XVal = *pSRegPos[0];
		// After XOR, rotate register to right (=advance pointer to left)
		if ( pSRegPos[0] <= &SReg[0] )
			pSRegPos[0] = &SReg[SRegLength[0]-1];
		else
			pSRegPos[0]--;

		for ( i=1; i<Number; i++ )
		{
			XVal ^= *pSRegPos[i];

			// After XOR, rotate register to right (=advance pointer to left)
			if ( pSRegPos[i] <= &SReg[(i*Number)] )
				pSRegPos[i] = &SReg[(i*Number)+SRegLength[i]-1];
			else
				pSRegPos[i]--;
		}

		// Insert word into current register at 0th position (last pointer pos before rotation)
		XVal ^= InWord; // Mix with InWord
		*pInReg = XVal;

		// Cycle through current register, then rotate to new current reg
		CurrentPos--;	// Cycle
		// At end of cycle? Then rotate to new current register.
		if ( CurrentPos == 0 )
		{
			CurrentReg++;
			if ( CurrentReg>(Number-1) ) CurrentReg = 0;
			CurrentPos = SRegLength[CurrentReg];
		}

		return XVal;
	}

	// Sets Number resgister lengths as given in array pTabs
	void SetRegisters(int* pRegLengths, int Number)
	{
		this->Number = Number;

		if (SRegLength!=NULL)
			delete SRegLength;
		SRegLength = new T[Number];

		MaxLength = 0;
		for (int i=0; i<Number; i++)
		{
			SRegLength[i] = pRegLengths[i];

			if (pRegLengths[i]>MaxLength)
				MaxLength = pRegLengths[i];
		}

		if (SReg!=NULL)
			delete SReg;
		SReg = new T[Number*MaxLength];

		if (pSRegPos!=NULL)
			delete pSRegPos;
		pSRegPos = new T*[Number];
	}

	// Resets the corrector (zero's registers)
	void Reset(void)
	{
		ZeroMemory(SReg, (Number*MaxLength*sizeof(T)));

		CurrentReg = 0;
		CurrentPos = SRegLength[0];

		int i;
		for ( i=0; i<Number; i++ )
		{
			pSRegPos[i] = &SReg[(i*Number)];
		}
	}

protected:
	T* SReg;
	T**	pSRegPos;
	T*	pInReg;
	T*	SRegLength;
	T	CurrentReg;
	T	CurrentPos;
	int Number;
	int MaxLength;
};
