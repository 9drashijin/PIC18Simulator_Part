#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
int TABLE[2097152];

void tblwt_postinc(Bytecode *code){
	// TBLPTR
	// 0 = *	no change
	// 1 = *+	post-increment
	// 2 = *-	post-decrement
	// 3 = +*	pre-decrement
	
	// if(TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL] = 1){ // post-increment
		// TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL] = FSR[TABLAT];
		// TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL] = TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL]+1;
	// }
	
	TABLE[HOLD] = FSR[TABLAT];
	TABLE[TBLPTR] = TABLE[TBLPTR]+1;

}