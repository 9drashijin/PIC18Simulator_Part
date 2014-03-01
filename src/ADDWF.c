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

//Add WREG to FileReg
void addwf(Bytecode *code) {

	if		(code->operand2 == 1){
		FSR[code->operand1] = FSR[code->operand1] + FSR[WREG];
		// if (code->operand3 == 1){
			// case(GPRs)
			// 0000: Bank0;
			// 0001: Bank1;
			// 0010: Bank2;
			// 0011: Bank3;
			// 0100: Bank4;
			// 0101: Bank5;
			// 0110: Bank6;
			// 0111: Bank7;
			// 1000: Bank8;
			// 1001: Bank9;
			// 1010: Bank10;
			// 1011: Bank11;
			// 1100: Bank12;
			// 1101: Bank13;
			// 1110: Bank14;
			// 1111: Bank15;
		// }
	}
	else if (code->operand2 == 0){
		FSR[WREG] = FSR[WREG] + FSR[code->operand1];
		// if (code->operand3 == 1){
			// case(GPRs)
			// 0000: Bank0;
			// 0001: Bank1;
			// 0010: Bank2;
			// 0011: Bank3;
			// 0100: Bank4;
			// 0101: Bank5;
			// 0110: Bank6;
			// 0111: Bank7;
			// 1000: Bank8;
			// 1001: Bank9;
			// 1010: Bank10;
			// 1011: Bank11;
			// 1100: Bank12;
			// 1101: Bank13;
			// 1110: Bank14;
			// 1111: Bank15;
		// }
	}
	else{
		FSR[WREG] = FSR[WREG];
		FSR[code->operand1] = FSR[code->operand1];
	}
}