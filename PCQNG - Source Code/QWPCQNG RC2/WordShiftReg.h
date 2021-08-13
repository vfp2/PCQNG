#pragma once

class CWordShiftReg
{
public:
	CWordShiftReg(void);
	~CWordShiftReg(void);

	// Sets total length of shift register
	BOOL SetLength(ULONG Length);
	// Feeds 32-bit word into register
	void Feed(BYTE InWord8);
	// Reads a 32-bit word from shift reg at index
	BYTE Read(ULONG Index);

private:
	ULONG m_Length;
	int m_CurrentPos;
	BYTE* m_pRegister;
};
