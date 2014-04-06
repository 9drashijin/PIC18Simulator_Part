#include "Bytecode.h"
#include "RETFIE.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
/**
*	(TOS) → PC,
*	1 → GIE/GIEH or PEIE/GIEL;
*	if s = 1,
*	(WS) → W,
*	(STATUSS) → STATUS,
*	(BSRS) → BSR,
*	PCLATU, PCLATH are unchanged
**/

int retfie(Bytecode *code){	//check for error first, if occur straight throw exception

if(code->operand1 < 0x00 || code->operand1 > 0xfff){Throw(INVALID_RANGE);}
else if (code->operand2 != -1 && code->operand3 == -1){code->operand2  = code->operand2;}
else if (code->operand2 == -1 && code->operand3 != -1){code->operand2 = code->operand3;}
else {Throw(INVALID_OPERAND);}
	
	FSR[TOSU] == PIC18Stack[TOSU]; 
	FSR[TOSH] == PIC18Stack[TOSH];
	FSR[TOSL] == PIC18Stack[TOSL];
	((FSR[TOSU]<<16) + (FSR[TOSH]<<8) + FSR[TOSL]);
	if(code->operand2 == 1){
		
		FSR[WREG] 	= FSR[WREGS];	// Content of shadow register(WREGS) are loaded to WREG
		FSR[STATUS] = FSR[STATUSS];	// Content of shadow register(STATUSS) are loaded to STATUS
		FSR[BSR]	= FSR[BSRS];	// Content of shadow register(BSRS) are loaded to BSR
		FSR[INTCON] = 0b10000000;	// GIE enabled bit<7>	//decimal = 128 //0b10000000 exceeded 127 and turn to - 128. Overflow occur
		return (FSR[TOSU]<<16)+(FSR[TOSH]<<8)+FSR[TOSL];
	}
	else if (code->operand2 == 0){  // if 's' = 0 , All register no update (default).
		FSR[WREG] 	= FSR[WREG];
		FSR[STATUS] = FSR[STATUS];
		FSR[BSR]	= FSR[BSR];
		FSR[INTCON] = 0; 			// GIE disabled
		return (FSR[TOSU]<<16)+(FSR[TOSH]<<8)+FSR[TOSL];
	}
	else {Throw(INVALID_OPERAND);}
	
	
	
}