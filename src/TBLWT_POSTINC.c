#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
int TABLE[0x200000];

/**	
  *	Name		: Table Write post-increment
  * Input 		: tblwt_postinc
  *	Output 		: store in holding register then table pointer +1
  * Operation	: if TBLWT*+,
  *  			  (TABLAT) → Holding Register,
  *				  (TBLPTR) + 1 → TBLPTR;
*/


int tblwt_postinc(Bytecode *code){
	// TBLPTR
	// 0 = *	no change
	// 1 = *+	post-increment
	// 2 = *-	post-decrement
	// 3 = +*	pre-decrement
	FSR[TBLPTRU] = (((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))+1&0x010000)>>16;
	FSR[TBLPTRH] = (((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))+1&0xFF00)>>8;
	FSR[TBLPTRL] = (((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))+1&0xFF);
	
	TABLE[((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))] = FSR[TABLAT];
	
	return code->absoluteAddress += 1;
}