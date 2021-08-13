// RawData.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "PCQNG.h"
#include "Winsock2.h"
#include "stdio.h"

void SendWord(unsigned long* InWord);
unsigned long MakeWord(void);

int counter;

CPCQNG PCQNG;
SOCKET SocketClient;

int _tmain(int argc, _TCHAR* argv[])
{
	counter = 0;
	// load socket dll
	WSADATA WSAData;
	WSAStartup(0x0202, &WSAData);

	char sAddress[20];
	strcpy(sAddress, "192.168.0.1");	// Local loopback

	// resolve address
	hostent* hp;
	unsigned int addr;
	if (isalpha(sAddress[0])) {   /* server address is a name */
		hp = gethostbyname(sAddress);
	}
	else  { /* Convert nnn.nnn address to a usable one */
		addr = inet_addr(sAddress);
		hp = gethostbyaddr((char *)&addr,4,AF_INET);
	}

	// fill in server address details
	sockaddr_in server;
	memset(&server,0,sizeof(server));
	memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(21021);

	// connect TCP client
	SocketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(SocketClient, (struct sockaddr *)&server, sizeof(server));

//	FILE* pFile;
	int Points = 100000;
	unsigned long Buffer[100000];


	PCQNG.Open();
//	PCQNG.SetMode(0x1000af35); // mode f = 512 
	PCQNG.SetMode(0x1000a835); // 8 = 8192
	PCQNG.StartBurst();
	while(true)
	{
		Buffer[counter] = MakeWord() ^ MakeWord() ^ MakeWord() ^ MakeWord();
		counter++;
		counter %= 1024;
		if (counter==0)
			SendWord(Buffer);
	}
/*	for (int i=0; i<Points; i++)
		PCQNG.Read(&Buffer[i]);*/
	PCQNG.Close();

/*	pFile = fopen("A:\\Data64Hz.txt", "w+");
	for (int j=0; j<Points; j++)
		fprintf(pFile, "%u\n", Buffer[j]);
	fclose(pFile);*/

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
//
// MiniPCQNG.c - Mini PCQNG implementation for Linux
//
// Copyright © 2001-2003 The Quantum World Corporation. All rights reserved
//
// Confidential
//

// Version History
// PAW		2003-03-10		Creation

// Win32 if run on Windows, else Lin32 for Linux
#define Win32
// #define Lin32

unsigned long MakeWord(void)
{
// Define vars ///////////////////////////////////////////////////////////////
	// To return 32 bit random result
	unsigned long RetVal = 0;

	// To store timestamp counter word, low word only 
	unsigned long TSCWord = 0;

	// Used for intermediate result
	double CalcDouble = 0.;

#ifdef Win32
	// 64 bit word used for processing
	__int64 CalcWord64 = 0;
#endif
#ifdef Lin32
	// Linux, I think that "long long" = 64 bit, also try "u64"
	long long CalcWord64 = 0;
#endif
//////////////////////////////////////////////////////////////////////////////

// Each interrupt produces a 32 bit word
// XOR 4 32-bit results from interrupts to get result near Entropy=1
for (int i=0; i<1; i++)
{

// Wait for interrupt ////////////////////////////////////////////////////////
#ifdef Win32
	// This Sleep is intended to simulate an interrupt ~64Hz Windows
	// Wait on interrupt in Linux code in Lin32 #ifdef following
	//Sleep(15);
#endif
#ifdef Lin32
	// Wait for interrupt here 
#endif
//////////////////////////////////////////////////////////////////////////////


// Read TSC //////////////////////////////////////////////////////////////////
#ifdef Win32
	// Windows inline asm for TSC 32 LSBits (eax) -> TSCWord
//	__asm
//	{
//		rdtsc
//		mov dword ptr [TSCWord], eax
//	}
	PCQNG.Read(&TSCWord);
#endif
#ifdef Lin32
	// Inline asm for Linux TSC here, only need 32 LSBits (eax)
#endif
//////////////////////////////////////////////////////////////////////////////


// Special randomizing processing ////////////////////////////////////////////
	CalcWord64 = TSCWord;

	// CalcWord64 = Mod(CalcWord64^2, 3719549303) * Mod(CalcWord64^2, 4959399113)
	CalcWord64 *= CalcWord64;
	CalcWord64 = (CalcWord64 % 3719549303) * (CalcWord64 % 4959399113);

	// CalcDouble = 2^32 * (Mod(CalcWord64, 12884901893) / 12884901893)
	CalcDouble = ((double)(CalcWord64 % 12884901893))/12884901893.;
	CalcDouble *= 4294967296.;

	// RetVal = Retval XOR Floor(CalcDouble)
	RetVal ^= (unsigned long)CalcDouble;

//////////////////////////////////////////////////////////////////////////////

}

	return RetVal;
}

void SendWord(unsigned long* InWord)
{
	send(SocketClient, (const char*)InWord, (1024*4), 0);
	printf(".");
}