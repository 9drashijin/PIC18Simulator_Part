#ifndef	__DECF_H__
#define	__DECF_H__

#define 	WREG 	0xFE8
#define		BSR 	0xFE0
#define 	STATUS  0xFD8 //bit[4:0] [N,OV,Z,DC,C]

extern char FSR[];

int decf(Bytecode *code);

#endif	// __DECF_H__