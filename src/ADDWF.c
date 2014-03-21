#include <stdio.h>
#include "Bytecode.h"
#include "ADDWF.h"
#include "CException.h"

char FSR[0x1000]; 
//FSR0H = FEAh 4074d
//FSR0L = FE9h 4073d
//FSR1H = FE2h 4066d
//FSR1L = FE1h 4065d

//WREG 	= 0xFE8

/**	
  *	Name	: Add WREG to f
  * Input 	: f{,d{,a}}
  *	Output 	: d = 0, STORED in WREG
  *			  d = 1, STORED in fileReg
  *
*/
/**
*	Test Ficture
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
*
*/
//Add WREG to FileReg (affected C,DC,Z)
void addwf(Bytecode *code) {

	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}
	if		(code->operand2 == 1){
		FSR[code->operand1] = FSR[code->operand1] + FSR[WREG];
	}
	else if (code->operand2 == 0){
		FSR[WREG] = FSR[WREG] + FSR[code->operand1];
	}
	else{
		FSR[WREG] = FSR[WREG];
		FSR[code->operand1] = FSR[code->operand1];
	}
	if (code->operand3 == 1){
		FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
		
		if(FSR[BSR] = 0 && FSR[code->operand1] <= 80){FSR[BSR] = 0x00;}
		else if(FSR[BSR] = 15 && FSR[code->operand1] >= 80){FSR[BSR] = 0x0F;}
		
			switch(FSR[BSR]){
			if (FSR[BSR] > 15){Throw(INVALID_BSR);}
			//case 0: FSR[BSR] = 0x00; break;
			case 1: FSR[BSR] = 0x01; break;
			case 2: FSR[BSR] = 0x02; break;
			case 3: FSR[BSR] = 0x03; break;
			case 4: FSR[BSR] = 0x04; break;
			case 5: FSR[BSR] = 0x05; break;
			case 6: FSR[BSR] = 0x06; break;
			case 7: FSR[BSR] = 0x07; break;
			case 8: FSR[BSR] = 0x08; break;
			case 9: FSR[BSR] = 0x09; break;
			case 10: FSR[BSR] = 0x0A; break;
			case 11: FSR[BSR] = 0x0B; break;
			case 12: FSR[BSR] = 0x0C; break;
			case 13: FSR[BSR] = 0x0D; break;
			case 14: FSR[BSR] = 0x0E; break;
			//case 15: FSR[BSR] = 0x0F; break;
			}
		}
}