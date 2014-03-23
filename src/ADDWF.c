#include <stdio.h>
#include "Bytecode.h"
#include "ADDWF.h"
#include "CException.h"

char FSR[0x1000]; 
//WREG 	= 0xFE8

/**	
  *	Name	: Add WREG to f
  * Input 	: f{,d{,a}}
  *	Output 	: d = 0, STORED in WREG
  *			  d = 1, STORED in fileReg
  *
*/
/**
*	BSR <3:0>
*				 00h ___ 000h
*	0000: Bank0;	|___|0FFh	GOR	(half)
*	0001: Bank1;	|___|1FFh	GPR
*	0010: Bank2;	|___|2FFh	GPR
*	0011: Bank3;	|___|3FFh	GPR
*	0100: Bank4;	|___|4FFh	GPR
*	0101: Bank5;	|___|5FFh	Access Bank
*	0110: Bank6;	|U	|6FFh	 ___
*	0111: Bank7;    |N	|7FFh	|___|00h ~ 7Fh Low
*	1000: Bank8;    |U	|8FFh	|___|80h ~ FFh High (SFRs) 
*	1001: Bank9;	|S	|9FFh
*	1010: Bank10;	|E	|AFFh
*	1011: Bank11;	|D	|BFFh
*	1100: Bank12;	|Rd |CFFh
*	1101: Bank13;	|00h|DFFh
*	1110: Bank14;	|___|EFFh
*	1111: Bank15;FFh|___|FFFh
*/
//Add WREG to FileReg (affected bit[4:0] [N,OV,Z,DC,C])
void addwf(Bytecode *code) {
	if (code->operand2 == -1){code->operand2 = F;}		//default if no value input (empty = -1)
	if (code->operand3 == -1){code->operand3 = ACCESS;}	//default if no value input
	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}
	else{
		int temp1 = FSR[code->operand1];
		int temp2 = FSR[code->operand1+(0x0F00)];
		if	(code->operand2 == 1 || code->operand2 == F ){
			if(code->operand1 < 0x80){
			FSR[code->operand1] = FSR[code->operand1] + FSR[WREG];
			if(FSR[code->operand1] <= -1)			{FSR[STATUS] = 0b00010000;} // 0 0 0 0 0  0 0  0
			else if(FSR[code->operand1] == ~(temp1)){FSR[STATUS] = 0b00001000;} // - - - N OV Z DC C
			else if(FSR[code->operand1] == 0)		{FSR[STATUS] = 0b00000100;}
			else if(FSR[code->operand1] > 0x0F)		{FSR[STATUS] = 0b00000010;}
			else if(FSR[code->operand1] > 0xFF)		{FSR[STATUS] = 0b00000001;}
			}
			else if(code->operand1 >= 0x80){
			FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] + FSR[WREG];
			if(FSR[code->operand1+(0x0F00)] <= -1)				{FSR[STATUS] = 0b00010000;} // 0 0 0 0 0  0 0  0
			else if(FSR[code->operand1+(0x0F00)] == ~(temp2))	{FSR[STATUS] = 0b00001000;} // - - - N OV Z DC C
			else if(FSR[code->operand1+(0x0F00)] == 0)			{FSR[STATUS] = 0b00000100;}
			else if(FSR[code->operand1+(0x0F00)] > 0x0F)		{FSR[STATUS] = 0b00000010;}
			else if(FSR[code->operand1+(0x0F00)] > 0xFF)		{FSR[STATUS] = 0b00000001;}
			}
		}
		else if (code->operand2 == 0 || code->operand2 == W){
			if(code->operand1 < 0x80){
			FSR[WREG] = FSR[WREG] + FSR[code->operand1];
			if(FSR[code->operand1] <= -1)	{FSR[STATUS] = 0b00010000;} // 0 0 0 0 0  0 0  0
			else if(FSR[WREG] == ~(temp1))	{FSR[STATUS] = 0b00001000;} //overflow occurs when (+A)+(+B)=−C or (−A)+(−B)=+C
			else if(FSR[WREG] == 0)			{FSR[STATUS] = 0b00000100;}
			else if(FSR[WREG] > 0x0F)		{FSR[STATUS] = 0b00000010;}
			else if(FSR[WREG] > 0xFF)		{FSR[STATUS] = 0b00000001;}
			}
			else if(code->operand1 >= 0x80){
			FSR[WREG+(0x0F00)] = FSR[code->operand1+(0x0F00)] + FSR[WREG];
			if(FSR[code->operand1] <= -1)	{FSR[STATUS] = 0b00010000;} // 0 0 0 0 0  0 0  0
			else if(FSR[WREG] == ~(temp2))	{FSR[STATUS] = 0b00001000;} // - - - N OV Z DC C
			else if(FSR[WREG] == 0)			{FSR[STATUS] = 0b00000100;}
			else if(FSR[WREG] > 0x0F)		{FSR[STATUS] = 0b00000010;}
			else if(FSR[WREG] > 0xFF)		{FSR[STATUS] = 0b00000001;}
			}
		}
		else if (code->operand2 == BANKED || code->operand2 == ACCESS ){Throw(INVALID_OPERAND);}		// operand 2 with ACCESS or BANKED
		else if (code->operand3 == W || code->operand3 == F){Throw(INVALID_OPERAND);}					// operand 3 with WREG or FileReg
		else if (code->operand2 <-5 || code->operand2 >1){Throw(INVALID_OPERAND);}						// operand 2 more than -5 or 1
		else if (code->operand3 <-5 || code->operand3 >1){Throw(INVALID_OPERAND);}						// operand 3 more than -5 or 1
			
		if (code->operand3 == 1 || code->operand3 == BANKED){
			if(FSR[BSR] > 15 || FSR[BSR]<0){FSR[BSR] = 0;Throw(INVALID_BSR);} // more than 15 or less than 0, clear BSR to 0
			if(code->operand1 < 0x80){FSR[BSR] = 0x00;}
			else if(code->operand1 >= 0x80){FSR[BSR] = 0x0F;}
			FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
		}
	}
}






















