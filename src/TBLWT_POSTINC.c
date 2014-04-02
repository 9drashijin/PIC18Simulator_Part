#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

char FSR[0x1000];
int TABLE[0x200000];

void tblwt_postinc(Bytecode *code){
	// TBLPTR
	// 0 = *	no change
	// 1 = *+	post-increment
	// 2 = *-	post-decrement
	// 3 = +*	pre-decrement
	
	TABLE[TBLPTR] = ((TABLE[TBLPTRU]<<16) + (TABLE[TBLPTRH] <<8) + (TABLE[TBLPTRL]));
	TABLE[HOLD] = FSR[TABLAT];
	TABLE[TBLPTR] = TABLE[TBLPTR]+1;
	
	//printf("tabptr1st: %x\n" , TABLE[TBLPTR]);

}