#include "unity.h"
#include "Bytecode.h"
#include "RETFIE.h"
#include <stdio.h>
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_RETFIE_given_0_should_set_0_to_GIE_and_other_register_are_not_affected(){
	Instruction inst = {.mnemonic = RETFIE,.name = "retfie"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = 0,		//selected 0
					 .operand3 = -1,	//empty
					};
	FSR[WREG] 	= 100;	//hex	 0x64
	FSR[STATUS] = 16;	//binary 00010000
	FSR[BSR]	= 5;				
	retfie(&code);
	TEST_ASSERT_EQUAL(100,FSR[WREG]);
	TEST_ASSERT_EQUAL(16,FSR[STATUS]);
	TEST_ASSERT_EQUAL(5,FSR[BSR]);
	TEST_ASSERT_EQUAL(0,FSR[INTCON]);	// GIE disabled
}
void test_RETFIE_given_1_should_set_1_to_GIE_and_other_register_are_replaced_with_shadow_register(){
	Instruction inst = {.mnemonic = RETFIE,.name = "retfie"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = -1,	//empty
					 .operand3 = 1,		//selected 1
					};
	FSR[WREGS] 	= 0x5A;	//hex	 0x64
	FSR[STATUSS] = 16;	//binary 00010000
	FSR[BSRS]	= 5;				
	retfie(&code);
	TEST_ASSERT_EQUAL(0x5A,FSR[WREG]);	//shadow register loaded to WREG
	TEST_ASSERT_EQUAL(16,FSR[STATUS]);	//shadow register loaded to STATUS
	TEST_ASSERT_EQUAL(5,FSR[BSR]);		//shadow register loaded to BSR
	TEST_ASSERT_EQUAL(-128,FSR[INTCON]);	// GIE enabled //0b10000000 exceeded 127 and turn to - 128. Overflow occur
}
void test_RETFIE_given_both_operand1_and_2_is_empty_should_throw_error(){
	Instruction inst = {.mnemonic = RETFIE,.name = "retfie"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = -1,	//empty
					 .operand3 = -1,	//empty
					};
	FSR[WREGS] 	= 0x5A;	//hex	 0x64
	FSR[STATUSS] = 16;	//binary 00010000
	FSR[BSRS]	= 5;	
	CException errorRange;
	Try{
		retfie(&code);
		TEST_ASSERT_EQUAL(0x5A,FSR[WREG]);
		TEST_ASSERT_EQUAL(16,FSR[STATUS]);
		TEST_ASSERT_EQUAL(5,FSR[BSR]);
		TEST_ASSERT_EQUAL(-128,FSR[INTCON]);	// GIE enabled //0b10000000 exceeded 127 and turn to - 128. Overflow occur
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
	}
}
void test_RETFIE_given_both_operand1_and_2_have_value_and_should_throw_error(){
	Instruction inst = {.mnemonic = RETFIE,.name = "retfie"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xA5,
					 .operand2 = 100,	//2 value
					 .operand3 = 100,	
					};
	FSR[WREG] 	= 100;	//hex	 0x64
	FSR[STATUS] = 16;	//binary 00010000
	FSR[BSR]	= 5;	
	CException errorRange;
	Try{
		retfie(&code);
		TEST_ASSERT_EQUAL(100,FSR[WREG]);
		TEST_ASSERT_EQUAL(16,FSR[STATUS]);
		TEST_ASSERT_EQUAL(5,FSR[BSR]);
		TEST_ASSERT_EQUAL(0,FSR[INTCON]);	// GIE disabled
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
	}
}
void test_RETFIE_given_both_operand1_exceeded_the_valid_range_of_0xFF_and_should_throw_error(){
	Instruction inst = {.mnemonic = RETFIE,.name = "retfie"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xFFFF,
					 .operand2 = 0,	//2 value
					 .operand3 = -1,	
					};
	FSR[WREG] 	= 100;	//hex	 0x64
	FSR[STATUS] = 16;	//binary 00010000
	FSR[BSR]	= 5;	
	CException errorRange;
	Try{
		retfie(&code);
		TEST_ASSERT_EQUAL(100,FSR[WREG]);
		TEST_ASSERT_EQUAL(16,FSR[STATUS]);
		TEST_ASSERT_EQUAL(5,FSR[BSR]);
		TEST_ASSERT_EQUAL(0,FSR[INTCON]);	// GIE disabled
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
	}
}