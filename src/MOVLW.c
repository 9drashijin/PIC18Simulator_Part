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
	FSR[WREG] = code->operand1 ;
	code->operand1 = -1;	//not using
	code->operand1 = -1;	//not using
}