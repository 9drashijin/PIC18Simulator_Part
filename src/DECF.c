#include <stdio.h>
#include "Bytecode.h"
#include "DECF.h"

char FSR[0x1000]; 
//FSR0H = FEAh 4074d
//FSR0L = FE9h 4073d
//FSR1H = FE2h 4066d
//FSR1L = FE1h 4065d

//WREG 	= 0xFE8

/**	
  *	Name	: Decrement f
  * Input 	: f{,d{,a}}
  *	Output 	: d = 0, STORED in WREG
  *			  d = 1, STORED in fileReg
  *
*/

//Decrement f
void decf(Bytecode *code) {

	if		(code->operand2 == 1){
		FSR[code->operand1] = (FSR[code->operand1])-1;
	}
	else if (code->operand2 == 0){
		FSR[WREG] = (FSR[code->operand1])-1;
	}
	else{
		FSR[WREG] = FSR[WREG];
		FSR[code->operand1] = FSR[code->operand1];
	}
	if (code->operand3 == 1){
		FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
			switch(FSR[BSR]){
			case 0: FSR[BSR] = 0x00; break;
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
			case 15: FSR[BSR] = 0x0F; break;
				default: FSR[BSR] = 0x00; break;
			}
		}
}