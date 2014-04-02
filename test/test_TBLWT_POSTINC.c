#include "unity.h"
#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_TBLWT_POSTINCzxc(){
	Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = -1,
					 .operand3 = -1,
					};
	FSR[TABLAT] = 0x55;
	TABLE[TBLPTRU] = 0x00;
	TABLE[TBLPTRH] = 0xA3;
	TABLE[TBLPTRL] = 0x56;
	TABLE[HOLD] = 0xFF;
	
	//printf("tabptrR: %x" , TABLE[TBLPTR]);
	
	tblwt_postinc(&code);
	
	//printf("tabptrR: %x\n" , TABLE[TBLPTR]);
	
	TEST_ASSERT_EQUAL(0x55,FSR[TABLAT]);
	TEST_ASSERT_EQUAL(0x00A357,TABLE[TBLPTR]);
	TEST_ASSERT_EQUAL(0x55,TABLE[HOLD]);
	TABLE[TABLAT] = 0;
}

void test_TBLWT_POSTINC(){
	Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 50,
					 .operand2 = -1,
					 .operand3 = -1,
					};
					
	FSR[TABLAT] = 100;
	TABLE[TBLPTRU] = 0x00;
	TABLE[TBLPTRH] = 0x00;
	TABLE[TBLPTRL] = 0x80;
	TABLE[HOLD] = 150;
	
	tblwt_postinc(&code);
	
	TEST_ASSERT_EQUAL(100,FSR[TABLAT]);
	TEST_ASSERT_EQUAL(0x81,TABLE[TBLPTR]);
	TEST_ASSERT_EQUAL(100,TABLE[HOLD]);
}
