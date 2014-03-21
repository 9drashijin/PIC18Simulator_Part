#ifndef	__ADDWF_H__
#define	__ADDWF_H__

#define 	WREG 	0xFE8
#define		BSR 	0xFE0
#define 	STATUS  0xFD8 //bit[4:0] [N,OV,Z,DC,C]

extern char FSR[];
//extern int PIC18Stack[32];

void addwf(Bytecode *code);

#endif	// __ADDWF_H__