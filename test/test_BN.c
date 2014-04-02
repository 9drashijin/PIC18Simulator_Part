#include "unity.h"
#include "Bytecode.h"
#include "BN.h"
#include <stdio.h>
#include "CException.h"

void setUp(void){}
void tearDown(void){}

void test_BN_given_STATUS_is_zero_and_should_not_branch_but_skip_the_next_instruction(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 15,
					 .operand2 = 100,	//then replace, operand2 = absoluteAddress
					 .operand3 = -1,	// empty
					};
	FSR[STATUS] = 0;
	//printf("absoluteAddress: %d\n",code.absoluteAddress);
	bn(&code);		
	//printf("absoluteAddress: %d",code.absoluteAddress);
	
	TEST_ASSERT_EQUAL(2,code.absoluteAddress);
}
void test_BN_given_STATUS_is_one_and_should_branch(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 15,
					 .operand2 = -1,	// empty
					 .operand3 = 100,	//then replace, operand3 = absoluteAddress
					};
	FSR[STATUS] = 16;
//	printf("absoluteAddress: %d\n",code.absoluteAddress);
	bn(&code);		
//	printf("absoluteAddress: %d",code.absoluteAddress);
	
	TEST_ASSERT_EQUAL(100,code.absoluteAddress);
}
void test_BN_given_both_operand1_and_2_is_empty_should_throw_error(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 15,
					 .operand2 = -1,	//both empty don't know branch where
					 .operand3 = -1,
					};
	FSR[STATUS] = 16;
	CException errorRange;
	Try{
		bn(&code);		
		TEST_ASSERT_EQUAL(100,code.absoluteAddress);
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
	}
}
void test_BN_given_both_operand1_and_2_have_value_and_should_throw_error(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 15,
					 .operand2 = 100,	//2 value
					 .operand3 = 100,
					};
	FSR[STATUS] = 16;
	CException errorRange;
	Try{
		bn(&code);		
		TEST_ASSERT_EQUAL(100,code.absoluteAddress);
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
	}
}
void test_BN_given_both_operand1_and_2_exceeded_the_valid_range_of_negative_128_to_127_and_should_throw_error(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 15,
					 .operand2 = -1,
					 .operand3 = 128,	//exceeded 127 (valid range : )
					};
	FSR[STATUS] = 16;
	CException errorRange;
	Try{
		bn(&code);		
		TEST_ASSERT_EQUAL(100,code.absoluteAddress);
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
	}
}
void test_BN_given_both_operand1_exceeded_the_valid_range_of_0xFF_and_should_throw_error(){
	Instruction inst = {.mnemonic = BN,.name = "bn"};	
	Bytecode code = {.instruction = &inst,
					 .operand1 = 0xFFF,	//exceeded 0xFF
					 .operand2 = -1,
					 .operand3 = 100,
					};
	FSR[STATUS] = 16;
	CException errorRange;
	Try{
		bn(&code);		
		TEST_ASSERT_EQUAL(100,code.absoluteAddress);
	}
	Catch(errorRange){
		TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
	}
}
