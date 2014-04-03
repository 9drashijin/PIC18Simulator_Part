#ifndef TSTFSZ_H
#define TSTFSZ_H

#define 	WREG 	0xFE8
#define		BSR 	0xFE0

extern char FSR[];

int tstfsz(Bytecode *code);

#endif // TSTFSZ_H
