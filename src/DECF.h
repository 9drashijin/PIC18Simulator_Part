#ifndef	__DECF_H__
#define	__DECF_H__

#define WREG 0xFE8

extern char FSR[];

void decf(Bytecode *code);

#endif	// __DECF_H__