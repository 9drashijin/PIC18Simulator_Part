#include "unity.h"
#include "Bytecode.h"
#include "MOVLW.h"

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
void test_MOVLW_given_operand2_with_value_and_operand3_with_negative_1_should_return_with_value_1() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	0, 
                    .operand3 = -1					
                  };
  movlw(&code);
  TEST_ASSERT_EQUAL_HEX8(1, FSR[WREG]);
}
void test_MOVLW_given_operand3_with_value_and_operand2_with_negative_1_should_return_with_value_2() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	-1, 
                    .operand3 = 0					
                  };
  movlw(&code);
  TEST_ASSERT_EQUAL_HEX8(2, FSR[WREG]);
}
void test_MOVLW_given_operand2_and_3_with_value_should_return_with_value_4() {
  Instruction inst = {
                      .mnemonic = MOVLW,
                      .name = "movlw"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A, 
                    .operand2 =	0, 
                    .operand3 = 0					
                  };
  movlw(&code);
  TEST_ASSERT_EQUAL_HEX8(4, FSR[WREG]);
}