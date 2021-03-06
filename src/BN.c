#include "Bytecode.h"
#include "BN.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
int PC;

/**	
  *	Name		: Branch if Negative
  * Input 		: -128 < n < 127
  *	Output 		: branch to absoluteAddress
  * Operation	: if Carry bit is ‘1’,
  *				  (PC) + 2 + 2n → PC
  *
*/

/**	10	 
*	15	here	bn  there
*	20	there
*/	

// if Negative bit is ‘1’, (PC) + 2 + 2n → PC
// Let absoluteAddress as PC (Program Counter)
int bn(Bytecode *code){	//check for error first, if occur straight throw exception

if(code->operand1 < 0x00 || code->operand1 > 0xfff){Throw(INVALID_RANGE);}
else if(code->operand2 < -128 || code->operand2 > 127){Throw(INVALID_RANGE);}
else if(code->operand3 < -128 || code->operand3 > 127){Throw(INVALID_RANGE);}
else if (code->operand2 != -1 && code->operand3 == -1){code->absoluteAddress = code->operand2;}
//else if (code->operand2 == -1 && code->operand3 != -1){code->absoluteAddress = code->operand3;}
else {Throw(INVALID_OPERAND);}
	
	if(FSR[STATUS] == 0b00010000){
		return code->absoluteAddress;	//direct address for Branch instruction
	}
	else{
		int tempAddress = code->absoluteAddress;
		code->absoluteAddress = ~(code->absoluteAddress)+1;	// 2's complement of absoluteAddress
		code->absoluteAddress = code->absoluteAddress + tempAddress; //then add with original absoluteAddress (eg: -10 + 10 = 0)
		code->absoluteAddress += 2;
		return code->absoluteAddress;
	}
}