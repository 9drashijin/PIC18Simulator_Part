#include "unity.h"
#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void xtest_TBLWT_POSTINC(){
	// Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	// Bytecode code = {.instruction = &inst,
					 // .operand1 = 0xA5,
					 // .operand2 = -1,
					 // .operand3 = -1,
					// };
	// FSR[TABLAT] = 0x55;
	// TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL]= 0x00A356;;
	// TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL] = 0xFF;
	
	// tblwt_postinc(&code);
	
	// TEST_ASSERT_EQUAL(0x55,FSR[TABLAT]);
	// TEST_ASSERT_EQUAL(0x00A357,TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL]);
	// TEST_ASSERT_EQUAL(0x55,TABLE[(TBLPTRU<<8)+(TBLPTRH<<8)+TBLPTRL]);
}
void test_TBLWT_POSTINC(){
	Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					};
	FSR[TABLAT] = 0x55;
	TABLE[TBLPTR]= 0x00A356;;
	TABLE[HOLD] = 0xFF;
	
	tblwt_postinc(&code);
	
	TEST_ASSERT_EQUAL(0x55,FSR[TABLAT]);
	TEST_ASSERT_EQUAL(0x00A357,TABLE[TBLPTR]);
	TEST_ASSERT_EQUAL(0x55,TABLE[HOLD]);
}
