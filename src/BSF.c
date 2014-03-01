#include <stdio.h>
#include "Bytecode.h"
#include "BSF.h"

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
void bsf(Bytecode *code) {
	switch (code->operand2 ){
	case 0: FSR[code->operand2] = 0b00000001; break;
	case 1: FSR[code->operand2] = 0b00000010; break;
	case 2: FSR[code->operand2] = 0b00000100; break;
	case 3: FSR[code->operand2] = 0b00001000; break;
	case 4: FSR[code->operand2] = 0b00010000; break;
	case 5: FSR[code->operand2] = 0b00100000; break;
	case 6: FSR[code->operand2] = 0b01000000; break;
	case 7: FSR[code->operand2] = 0b10000000; break;	//
		default: FSR[code->operand1] = 0b00000000;  break;
	}
}