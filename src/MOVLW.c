#include <stdio.h>
#include "Bytecode.h"
#include "MOVLW.h"

char FSR[0x1000]; 
//FSR0H = FEAh 4074d
//FSR0L = FE9h 4073d
//FSR1H = FE2h 4066d
//FSR1L = FE1h 4065d

//WREG 	= 0xFE8

/**	
  *	Name	: Move Literal to WREG
  * Input 	: k ( operand1 )
  *	Output 	: The 8-bit literal k is loaded into WREG
  *
*/

//Move Literal to WREG
void movlw(Bytecode *code) {
	if(code->operand2 != -1 && code->operand3 == -1){FSR[WREG] = 1;}		// operand2 has valid value, but operand3 is -1
	else if(code->operand3 != -1 && code->operand2 == -1){FSR[WREG] = 2;}	// operand3 has valid value, but operand2 is -1
	else if(code->operand2 == -1 && code->operand3 == -1){FSR[WREG] = code->operand1;}	// both operand2 and operand3 are -1
	else if(code->operand2 != -1 && code->operand3 != -1){FSR[WREG] = 4;}	// both operand2 and operand3 have valid values
}