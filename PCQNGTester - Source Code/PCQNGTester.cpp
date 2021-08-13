// PCQNGTester.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "winsock.h"
#include "math.h"

// #import directive using full path to "PCQWQNG.dll"
// "no_namespace" avoids the need to use namespace "QWPCQNG"
#import "C:\Documents and Settings\pawilber\My Documents\Projects\QWPCQNG\Release\QWPCQNG.dll" no_namespace named_guids

#include "stdio.h"
#include "stdlib.h"
#include "conio.h"

unsigned long ran2(long *idum);

#define IM1 2147483647
#define IM2 2147483629
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.86e-9
#define RNMX (1.0-EPS)

#include "MT19937.h"
	CMT19937 MT19937;

long seed;

int main()
{


//	seed = -7531;

//	MT19937.SGenRand(421317);
//	FILE* pFile;
//	pFile = fopen("Raw1700.txt", "w+");

    // Declare a smart pointer to QNG control
    IPCQNGPtr pPCQNG = 0;

    // Create instance of QNG control
    CoInitialize(NULL);
    pPCQNG.CreateInstance(CLSID_PCQNG);

	pPCQNG->Open();
	pPCQNG->Clear();
	pPCQNG->SetMode(-1);

	int sockfeed;
	struct sockaddr_in address;
	
/*	// Windows needs this to load socket dll
	WSADATA wsdata;
	WSAStartup(0x22, &wsdata);

	// Create socket
	sockfeed = (int)socket(AF_INET, SOCK_STREAM, 0);
		// 127.0.0.1 local loopback address
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_family = AF_INET;
		// port: 21021
	address.sin_port = htons(21023);
	
	// Connect to server
	if (connect(sockfeed,  (struct sockaddr*)&address, sizeof(address))==-1)
		return -1;	// error
*/
	unsigned long buffer[32768];

	int rawcnt = 0;

//	pPCQNG->Clear();
	unsigned long extracount = 1;
	unsigned long countt = 1;

	unsigned char lastbyte = 0;
	unsigned char thisbyte = 0;
	double bytecounter = 0.;
	double hitcounter = 0.;
	while (true)
	{
		for (int i=0; i<512; i++)
		{
			pPCQNG->get_RandInt32((long*)&buffer[i]);
/*			for (int o=3; o>=0; o--)
			{
				thisbyte = (unsigned char)(buffer[i]>>(o*8));
				bytecounter++;
				if (lastbyte == thisbyte)
				{
					hitcounter++;
					printf("Bytes:%f  Doubles:%f  Ratio:%f\n", bytecounter, hitcounter, hitcounter/bytecounter);
				}
				lastbyte = thisbyte;
			}*/

//			buffer[i] = ran2(&seed)&0xffff;
//			buffer[i] <<= 16;
//			buffer[i] |= ran2(&seed)&0xffff;
//			buffer[i] = MT19937.GenRand();
//			rawcnt++;
//			if (rawcnt<327680)
//				fprintf(pFile, "%u\n", buffer[i]);

//			if (buffer[i]!=countt)
//			{
//				MessageBox(NULL, "BAD", "BAD", MB_OK);
//			}
//			countt++;
//			buffer[i] = countt;
		}

//		extracount++;
		// Write buffer to RNGmeter
		printf("%x\n", buffer[0]);
//		send(sockfeed, (const char*)buffer, 512*4, 0);

//		if (rawcnt>=327680)
//			break;
	}
//			fclose(pFile);
	return 0;
}


/****************************************************************************/
/*                                                                          */
/* TITLE: Uniform Random Number Generator                                   */
/* AUTHOR: Numerical Recipes In C                                           */
/* DATE: March 17, 2003                                                     */
/*                                                                          */
/* ABSTRACT: This code is the ran2 random number generator function from    */
/* "Numerical Recipes In C" presented on page 282 of the second edition.    */
/*                                                                          */
/* To set the seed for ran2.c give a negative value to the long integer     */
/* variable whose address is passed to the ran2 function.                   */
/*                                                                          */
/****************************************************************************/




/* ============================  RAN2 FUNCTION  =========================== */

unsigned long ran2(long *idum)
{
  int j;
  long k;
  static long idum2 = 123456789;
  static long iy = 0;
  static long iv[NTAB];
  double temp;

  if (*idum <= 0)
  {
    if (-(*idum) < 1) *idum = 1;
    else *idum = -(*idum);
    idum2 = (*idum);
    for (j = NTAB + 7 ; j >= 0 ; j--)
    {
      k = (*idum) / IQ1;
      *idum = IA1 * (*idum - k*IQ1) - k*IR1;
      if (*idum < 0) *idum += IM1;
      if (j < NTAB) iv[j] = *idum;
    }
    iy = iv[0];
  }

  k = (*idum) / IQ1;
  *idum = IA1 * (*idum - k*IQ1) - k*IR1;
  if (*idum < 0) *idum += IM1;
  k = idum2 / IQ2;
  idum2 = IA2 * (idum2 - k*IQ2) - k*IR2;
  if (idum2 < 0) idum += IM2;
  j = iy / NDIV;
  iy = iv[j] - idum2;
  iv[j] = *idum;
  if (iy < 1) iy += IMM1;

//  unsigned long kk = MT19937.GenRand();
//  iy = (kk%(IM1-1));
//  iy += 1;


  if ((temp = AM * iy) > RNMX)
	  temp = RNMX;
 
  temp = (temp*10)-floor(temp*10);
//  return temp;
  return (unsigned long)(temp*65536);
}

