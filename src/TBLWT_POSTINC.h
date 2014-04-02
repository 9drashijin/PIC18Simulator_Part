#ifndef TBLWT_POSTINC_H
#define TBLWT_POSTINC_H

#define 	WREG 	0xFE8
#define		BSR 	0xFE0
#define 	STATUS  0xFD8 //bit[4:0] [N,OV,Z,DC,C]

#define		TBLPTRU	0xFF8
#define		TBLPTRH	0xFF7
#define		TBLPTRL	0xFF6
#define		TABLAT	0xFF5

#define		TBLPTR	0xF85
#define		HOLD	0xF9C

extern char FSR[];
extern int PIC18Stack[32];
extern int TABLE[2097152];

void tblwt_postinc(Bytecode *code);

#endif // TBLWT_POSTINC_H
