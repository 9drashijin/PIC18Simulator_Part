#include "unity.h"
#include "Bytecode.h"
#include "DECF.h"
#include <stdio.h>

void setUp() {}
void tearDown() {}

void test_the_fucntion_of_DECF_should_Decrement_FileReg_and_STORE_in_WREG() {
  // Test fixture
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// ADDRESS of fileReg
                    .operand2 =	0, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
	
  //Test DECF should store data in WREG
  FSR[code.operand1] = 0x17;
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  decf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0x16, FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0x17, FSR[code.operand1]);
  
  // 2nd test value
  FSR[code.operand1] = 0b11;
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  decf(&code);
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0b10, FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0b11, FSR[code.operand1]);
  FSR[WREG] = 0; 	//clear the WREG to 0
  
}

void test_the_fucntion_of_DECF_should_Decrement_FileReg_and_STORE_in_FileREG() {
  // Test fixture
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// ADDRESS of fileReg	
                    .operand2 =	1, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
	
  // Test DECF should store data in FileREG
  FSR[code.operand1] = 0x50;
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  decf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0x4F, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0, FSR[WREG]);
  
  // 2nd test value
  FSR[code.operand1] = 10;
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  decf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(9, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0, FSR[WREG]);
  
}