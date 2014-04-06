#include "unity.h"
#include "Bytecode.h"
#include "TBLWT_POSTINC.h"
#include <stdio.h>
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_TBLWT_POSTINC_pretest(){
	Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					};
	FSR[TABLAT] = 0x55;
	TABLE[TBLPTRU] = 0x00;
	TABLE[TBLPTRH] = 0xA3;
	TABLE[TBLPTRL] = 0x56;
	TABLE[0xAA] = 0xFF;
	
	tblwt_postinc(&code);
	
	TEST_ASSERT_EQUAL(0x55,FSR[TABLAT]);
	TEST_ASSERT_EQUAL(0x55,TABLE[((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))]);
	TEST_ASSERT_EQUAL(1,code.absoluteAddress);
}

void test_TBLWT_POSTINC(){

	Instruction inst = {.mnemonic = TBLWT_POSTINC,.name = "tblwt_postinc"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = -1,
					 .operand2 = -1,
					 .operand3 = -1,
					 .absoluteAddress = 100
					};				
	FSR[TABLAT] = 100;
	FSR[TBLPTRU] = 0x00;
	FSR[TBLPTRH] = 0xA3;
	FSR[TBLPTRL] = 0x56;
	TABLE[0x80] = 150;
	
	tblwt_postinc(&code);
	
	TEST_ASSERT_EQUAL(100,FSR[TABLAT]);
	TEST_ASSERT_EQUAL_HEX32(0x00A357,((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL])));
	TEST_ASSERT_EQUAL(100,TABLE[((FSR[TBLPTRU]<<16) + (FSR[TBLPTRH] <<8) + (FSR[TBLPTRL]))]);

	//printf("absoluteAddress: %d",code.absoluteAddress);
	TEST_ASSERT_EQUAL(101,code.absoluteAddress);

}
