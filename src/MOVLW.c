#include <stdio.h>
#include "Bytecode.h"
#include "MOVLW.h"
#include "CException.h"

char FSR[0x1000]; 
//WREG 	= 0xFE8

/**	
  *	Name	: Move Literal to WREG
  * Input 	: k ( operand1 )
  *	Output 	: The 8-bit literal k is loaded into WREG
  *
*/

//Move Literal to WREG
void movlw(Bytecode *code) {
	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}			// invalid range of input
	else if(code->operand2 != -1 && code->operand3 == -1){Throw(INVALID_OPERAND);}		// operand2 has valid value, but operand3 is -1
	else if(code->operand3 != -1 && code->operand2 == -1){Throw(INVALID_OPERAND);}		// operand3 has valid value, but operand2 is -1
	else if(code->operand2 == -1 && code->operand3 == -1){FSR[WREG] = code->operand1;}	// both operand2 and operand3 are -1
	else if(code->operand2 != -1 && code->operand3 != -1){Throw(INVALID_OPERAND);}		// both operand2 and operand3 have valid values
}