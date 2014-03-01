#include "unity.h"
#include "Bytecode.h"
#include "MOVLW.h"

void setUp() {}
void tearDown() {}

void test_meedling_around_with_some_text_ficture() {
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
  TEST_ASSERT_EQUAL(0x5A, FSR[WREG]);		
  TEST_ASSERT_EQUAL_HEX8(0x5A, FSR[WREG]);	
  
  TEST_ASSERT_EQUAL(-1, code.operand2);
  TEST_ASSERT_EQUAL(-1, code.operand3);
  
  TEST_ASSERT_EQUAL_STRING("movlw",inst.name);
  
}
