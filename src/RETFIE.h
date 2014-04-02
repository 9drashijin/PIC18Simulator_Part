#ifndef RETFIE_H
#define RETFIE_H

#define 	WREG 	0xFE8
#define		BSR 	0xFE0
#define 	STATUS  0xFD8 //bit[4:0] [N,OV,Z,DC,C]

#define 	WREGS 	 0xF88 // Shadow Register for W, STATUS, BSR
#define		BSRS 	 0xF87 // Address of 0xF88 ~ 0xF86 are unimplemented 
#define 	STATUSS  0xF86 // (temporary address) for Shadow Register

#define		PCLATU	0xFFB // both PCLATH PCLATU unchanged
#define		PCLATH	0xFFA

#define		TOSU	0xFFF
#define		TOSH	0xFFE
#define		TOSL	0xFFD
#define		STKPTR	0xFFC

#define		INTCON	0xFF2 //[7:6]GIE/GIEH PEIE/GIEL 0 0  0 0 0 0

extern char FSR[];
extern int PC;
extern int PIC18Stack[32];

void retfie(Bytecode *code);

#endif // RETFIE_H
