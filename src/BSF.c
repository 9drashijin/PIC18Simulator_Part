#include <stdio.h>
#include "Bytecode.h"
#include "BSF.h"
#include "CException.h"

char FSR[0x1000]; 
//FSR0H = FEAh 4074d
//FSR0L = FE9h 4073d
//FSR1H = FE2h 4066d
//FSR1L = FE1h 4065d

//WREG 	= 0xFE8

/**	
  *	Name	: Bit Set f
  * Input 	: f{,d{,a}}
  *	Output 	: d = (0~7), Set bit 0 to 7
  *
*/

//Bit Set FileReg
int bsf(Bytecode *code) {
	if (code->operand3 == -1){code->operand3 = ACCESS;}	//default if no value input
	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}
	
	if(code->operand1 < 0x80){
		switch (code->operand2 ){
		case 0: FSR[code->operand1] = FSR[code->operand1] | 0b00000001; break;	// 1
		case 1: FSR[code->operand1] = FSR[code->operand1] | 0b00000010; break;	// 2
		case 2: FSR[code->operand1] = FSR[code->operand1] | 0b00000100; break;	// 4
		case 3: FSR[code->operand1] = FSR[code->operand1] | 0b00001000; break;	// 8
		case 4: FSR[code->operand1] = FSR[code->operand1] | 0b00010000; break;	// 16
		case 5: FSR[code->operand1] = FSR[code->operand1] | 0b00100000; break;	// 32
		case 6: FSR[code->operand1] = FSR[code->operand1] | 0b01000000; break;	// 64
		case 7: FSR[code->operand1] = FSR[code->operand1] | 0b10000000; break;	// 128
			default: FSR[code->operand1] = 0b00000000;  break;
		}
	}
	else if(code->operand1 >= 0x80){
		switch (code->operand2 ){
		case 0: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00000001; break;	// 1
		case 1: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00000010; break;	// 2
		case 2: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00000100; break;	// 4
		case 3: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00001000; break;	// 8
		case 4: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00010000; break;	// 16
		case 5: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b00100000; break;	// 32
		case 6: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b01000000; break;	// 64
		case 7: FSR[code->operand1+(0x0F00)] = FSR[code->operand1+(0x0F00)] | 0b10000000; break;	// 128
			default: FSR[code->operand1+(0x0F00)] = 0b00000000;  break;
		}
	}
	if (code->operand3 == W || code->operand3 == F){Throw(INVALID_OPERAND);}					// operand 3 with WREG or FileReg
	else if (code->operand3 <-5 || code->operand3 >1){Throw(INVALID_OPERAND);}
	else if (code->operand2 <0 || code->operand2 >7){Throw(INVALID_OPERAND);}
	
	if (code->operand3 == 1 || code->operand3 == BANKED){
			if(FSR[BSR] > 15 || FSR[BSR]<0){FSR[BSR] = 0;Throw(INVALID_BSR);} // more than 15 or less than 0, clear BSR to 0
			if(code->operand1 < 0x80){FSR[BSR] = 0x00;}
			else if(code->operand1 >= 0x80){FSR[BSR] = 0x0F;}
			FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
		}
	return 0;
}