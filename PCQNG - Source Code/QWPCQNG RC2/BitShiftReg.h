#pragma once

class CBitShiftReg
{
public:
	CBitShiftReg(void);
	~CBitShiftReg(void);
	// Sets total length of shift register
	BOOL SetLength(ULONG Length);
	// Feeds a bit encoded as a byte into the shift register
	void Feed(unsigned char InBit);
	// Reads a bit from the index indicated in shift reg
	unsigned char Read(ULONG Index);

private:
	ULONG m_Length;
	int m_CurrentPos;
	unsigned char* m_pRegister;
};
