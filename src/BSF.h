#ifndef	__BSF_H__
#define	__BSF_H__

#define 	WREG 	0xFE8
#define		BSR 	0xFE0

extern char FSR[];
//extern int PIC18Stack[32];

int bsf(Bytecode *code);

#endif	// __BSF_H__