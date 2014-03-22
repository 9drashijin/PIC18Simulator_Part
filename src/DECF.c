#include <stdio.h>
#include "Bytecode.h"
#include "DECF.h"
#include "CException.h"

char FSR[0x1000]; 
//WREG 	= 0xFE8

/**	
  *	Name	: Decrement f
  * Input 	: f{,d{,a}}
  *	Output 	: d = 0, STORED in WREG
  *			  d = 1, STORED in fileReg
  *
*/

//Decrement f (affected bit[4:0] [N,OV,Z,x,x])
void decf(Bytecode *code) {
	if (code->operand2 == -1){code->operand2 = F;}		//default if no value input (empty = -1)
	if (code->operand3 == -1){code->operand3 = ACCESS;}	//default if no value input
	if(code->operand1 > 0xff || code->operand1 < 0x00){Throw(INVALID_RANGE);}			// error range of input
	else{
		int temp1 = FSR[code->operand1];
		int temp2 = FSR[code->operand1+(0x0F00)];
		if	(code->operand2 == 1 || code->operand2 == F ){
			if(code->operand1 < 0x80){
			FSR[code->operand1] = (FSR[code->operand1])-1;
				if(FSR[code->operand1] <= -1)			 {FSR[STATUS] = 0b00010000;} // 0 0 0 0 0  0 0  0
				else if(FSR[code->operand1] == ~(temp1)) {FSR[STATUS] = 0b00001000;} // - - - N OV Z DC C
				else if(FSR[code->operand1] == 0)		 {FSR[STATUS] = 0b00000100;}
			}
			else if(code->operand1 >= 0x80){
			FSR[code->operand1+(0x0F00)] = (FSR[code->operand1+(0x0F00)])-1;
				if(FSR[code->operand1+(0x0F00)] <= -1)			 {FSR[STATUS] = 0b00010000;}
				else if(FSR[code->operand1+(0x0F00)] == ~(temp2)){FSR[STATUS] = 0b00001000;} //overflow occurs when (+A)+(+B)=−C or (−A)+(−B)=+C
				else if(FSR[code->operand1+(0x0F00)] == 0)		 {FSR[STATUS] = 0b00000100;} 	
			}
		}
		else if (code->operand2 == 0 || code->operand2 == W){
			if(code->operand1 < 0x80){
			FSR[WREG] = (FSR[code->operand1])-1;
				if(FSR[WREG] <= -1)				{FSR[STATUS] = 0b00010000;} // - - - N OV Z DC C
				else if(FSR[WREG] == ~(temp1))	{FSR[STATUS] = 0b00001000;}
				else if(FSR[WREG] == 0)			{FSR[STATUS] = 0b00000100;}
			}
			else if(code->operand1 >= 0x80){
			FSR[WREG+(0x0F00)] = ((FSR[code->operand1+(0x0F00)])-1);
				if(FSR[WREG+(0x0F00)] <= -1)			{FSR[STATUS] = 0b00010000;}
				else if(FSR[WREG+(0x0F00)] == ~(temp2))	{FSR[STATUS] = 0b00001000;}
				else if(FSR[WREG+(0x0F00)] == 0)		{FSR[STATUS] = 0b00000100;}
			}
		}//(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)
		else if (code->operand2 == BANKED || code->operand2 == ACCESS ){Throw(INVALID_OPERAND);}		// operand 2 with ACCESS or BANKED
		else if (code->operand3 == W || code->operand3 == F){Throw(INVALID_OPERAND);}					// operand 3 with WREG or FileReg
		else if (code->operand2 <-5 || code->operand2 >1){Throw(INVALID_OPERAND);}						// operand 2 more than -5 or 1
		else if (code->operand3 <-5 || code->operand3 >1){Throw(INVALID_OPERAND);}						// operand 3 more than -5 or 1
		
		if (code->operand3 == 1 || code->operand3 == BANKED){
			if(FSR[BSR] > 15){Throw(INVALID_BSR);}
			if(code->operand1 < 0x80){FSR[BSR] = 0x00;}
			else if(code->operand1 >= 0x80){FSR[BSR] = 0x0F;}
			FSR[code->operand1 + (FSR[BSR]*256)]; ///(FSR[BSR]*256) same as shift << 8 bit to left, 2^8 is 256.
		} 
	}
}
