#ifndef	__ADDWF_H__
#define	__ADDWF_H__

#define WREG 0xFE8

extern char FSR[];

void addwf(Bytecode *code);

#endif	// __ADDWF_H__