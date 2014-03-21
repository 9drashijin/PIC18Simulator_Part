#include "unity.h"
#include "Bytecode.h"
#include "MOVLW.h"
#include "CException.h"

void setUp() {}
void tearDown() {}

void test_MOVLW_given_operand2_and_3_with_negative_1_should_move_literal_to_WREG() {
  // Test fixture
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	-1, 
                    .operand3 = -1					
                  };
	
  // Test MOVLW of the Bytecode
  movlw(&code);

  // Unit test
  TEST_ASSERT_EQUAL_HEX8(0x5A, FSR[WREG]);		//Address of operand1 is moved to WREG with the same address 0x5A
  
  TEST_ASSERT_EQUAL(-1, code.operand2);
  TEST_ASSERT_EQUAL(-1, code.operand3);
  
  TEST_ASSERT_EQUAL_STRING("movlw",inst.name);
  
}
void test_MOVLW_invalid_range_with_operand1_set_to_0xffff_should_catch_error_invalid_range() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFFFF,
                    .operand2 =	0, 
                    .operand3 = 0, 
                  };
  CException errorRange;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
  }
}
void test_MOVLW_given_operand2_with_value_and_operand3_with_negative_1_should_catch_error_invalid_operand() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	0, 
                    .operand3 = -1					
                  };
  CException errorRange;
  FSR[WREG] = 0x00;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_MOVLW_given_operand3_with_value_and_operand2_with_negative_1_should_catch_error_invalid_operand() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	-1, 
                    .operand3 = 0					
                  };
  CException errorRange;
  FSR[WREG] = 0x00;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_MOVLW_given_operand2_and_3_with_value_should_catch_error_invalid_operand() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	0, 
                    .operand3 = 0					
                  };
  CException errorRange;
  FSR[WREG] = 0x00;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_MOVLW_given_operand2_and_3_with_W_and_ACCESS_should_catch_error_invalid_operand() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	W, 
                    .operand3 = ACCESS
                  };
  CException errorRange;
  FSR[WREG] = 0x00;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
  TEST_ASSERT_EQUAL(-5,ACCESS);
  TEST_ASSERT_EQUAL(-2,W);
}
void test_MOVLW_given_operand2_and_3_with_F_and_BANKED_should_catch_error_invalid_operand() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	F, 
                    .operand3 = BANKED
                  };
  CException errorRange;
  FSR[WREG] = 0x00;
  Try{
	movlw(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
  TEST_ASSERT_EQUAL(-4,BANKED);
  TEST_ASSERT_EQUAL(-3,F);
}