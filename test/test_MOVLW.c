#include "unity.h"
#include "Bytecode.h"
#include "MOVLW.h"

void setUp() {}
void tearDown() {}

void test_the_fucntion_of_MOVLW_should_Move_Literal_to_WREG() {
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
