#include <stdio.h>
#include "Bytecode.h"
#include "ADDWF.h"

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

//Move Literal to WREG
void addwf(Bytecode *code) {

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
}