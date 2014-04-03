#ifndef	__MOVLW_H__
#define	__MOVLW_H__

#define WREG 0xFE8

extern char FSR[];

int movlw(Bytecode *code);

#endif	// __MOVLW_H__