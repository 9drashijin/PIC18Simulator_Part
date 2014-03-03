#ifndef	__ADDWF_H__
#define	__ADDWF_H__

#define 	WREG 	0xFE8
#define		BSR 	0xFE0

extern char FSR[];

void addwf(Bytecode *code);

#endif	// __ADDWF_H__