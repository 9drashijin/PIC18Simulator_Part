#include "unity.h"
#include "Bytecode.h"
#include "BSF.h"
#include <stdio.h>

void setUp() {}
void tearDown() {}

void test_the_BSF_should_set_the_first_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	0, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00000001, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_second_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	1, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00000010, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_Third_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	2, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00000100, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_fourth_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	3, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00001000, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_fifth_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	4, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00010000, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
  
}
void test_the_BSF_should_set_the_sixth_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	5, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b00100000, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_seventh_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	6, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01000000, FSR[code.operand2]);
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}
void test_the_BSF_should_set_the_last_bit_to_1(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// address of FileReg	
                    .operand2 =	7, 		// (0~7), Set bit 0 to 7
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(-(0b10000000), FSR[code.operand2]); //error become negative
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
}