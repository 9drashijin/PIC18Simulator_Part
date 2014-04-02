#include "Bytecode.h"
#include "RETFIE.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
int PC;
/**
*	(TOS) → PC,
*	1 → GIE/GIEH or PEIE/GIEL;
*	if s = 1,
*	(WS) → W,
*	(STATUSS) → STATUS,
*	(BSRS) → BSR,
*	PCLATU, PCLATH are unchanged
**/

void retfie(Bytecode *code){	//check for error first, if occur straight throw exception

if(code->operand1 < 0x00 || code->operand1 > 0xff){Throw(INVALID_RANGE);}
else if (code->operand2 != -1 && code->operand3 == -1){code->operand2  = code->operand2;}
else if (code->operand2 == -1 && code->operand3 != -1){code->operand2 = code->operand3;}
else {Throw(INVALID_OPERAND);}
	
	TOSU == PIC18Stack[TOSU];
	TOSH == PIC18Stack[TOSH];
	TOSL == PIC18Stack[TOSL];
	PC = (TOSU*256)  + (TOSH*256) + TOSL;//	printf("PC: %d\n",PC);
	if(code->operand2 == 1){
		
		FSR[WREG] 	= FSR[WREGS];	// Content of shadow register(WREGS) are loaded to WREG
		FSR[STATUS] = FSR[STATUSS];	// Content of shadow register(STATUSS) are loaded to STATUS
		FSR[BSR]	= FSR[BSRS];	// Content of shadow register(BSRS) are loaded to BSR
		FSR[INTCON] = 0b10000000;	// GIE enabled bit<7>	//decimal = 128 //0b10000000 exceeded 127 and turn to - 128. Overflow occur
	}
	else if (code->operand2 == 0){  // if 's' = 0 , All register no update (default).
		FSR[WREG] 	= FSR[WREG];
		FSR[STATUS] = FSR[STATUS];
		FSR[BSR]	= FSR[BSR];
		FSR[INTCON] = 0; 			// GIE disabled
	}
	else {Throw(INVALID_OPERAND);}
	
}