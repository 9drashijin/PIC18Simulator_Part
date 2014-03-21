#include <stdio.h>
#include "Bytecode.h"
#include "DECF.h"
#include "CException.h"

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

//Decrement f (affected Z)
void decf(Bytecode *code) {
	if (code->operand2 == -1 && code->operand3== -1){code->operand2 = 1; code->operand3 = 0;} // default
	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}			// error range of input
	else{
		if		(code->operand2 == 1 || code->operand2 == F ){
			if(code->operand1 < 0x80){
			FSR[code->operand1] = (FSR[code->operand1])-1;
			}
			else if(code->operand1 >= 0x80){
			FSR[code->operand1+(0x0F00)] = (FSR[code->operand1+(0x0F00)])-1;
			}
		}
		else if (code->operand2 == 0 || code->operand2 == W){
			if(code->operand1 < 0x80){
			FSR[WREG] = (FSR[code->operand1])-1;
			}
			else if(code->operand1 >= 0x80){
			FSR[WREG+(0x0F00)] = ((FSR[code->operand1+(0x0F00)])-1);
			}
			
		}//(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)
		else if (code->operand2 == BANKED || code->operand2 == ACCESS ){Throw(INVALID_OPERAND);}		// operand 2 with ACCESS or BANKED
		else if (code->operand3 == W || code->operand3 == F){Throw(INVALID_OPERAND);}					// operand 3 with WREG or FileReg
		else if ((code->operand2 && code->operand3) >= -6){Throw(INVALID_OPERAND);}						// more than 1 or more than -5
		
		if (code->operand3 == 1 || code->operand3 == BANKED){
			if(FSR[BSR] > 15){Throw(INVALID_BSR);}
			FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
				switch(FSR[BSR]){
			//	case 0: FSR[BSR] = 0x00; break;
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
			//	case 15: FSR[BSR] = 0x0F; break;
					default: 
						if(code->operand1 < 0x80){FSR[BSR] = 0x00;}
						else if(code->operand1 >= 0x80){FSR[BSR] = 0x0F;}
					break;
				}
			}
	}
}
