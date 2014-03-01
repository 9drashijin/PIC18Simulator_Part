#include "unity.h"
#include "Bytecode.h"
#include "ADDWF.h"
#include <stdio.h>

void setUp() {}
void tearDown() {}

void test_the_fucntion_of_ADDWF_should_Add_WREG_and_FileReg_STORE_in_WREG() {
  // Test fixture
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// Add WREG to File register. W to "f".	
                    .operand2 =	0, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
	
  //Test ADDWF should store data in WREG
  FSR[code.operand1] = 0x17;
  FSR[WREG]			 = 0xC2;
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  addwf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0xD9, FSR[WREG]);
  
  // 2nd test value
  FSR[code.operand1] = 0b01;
  FSR[WREG]			 = 0b10;
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  addwf(&code);
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL(0b11, FSR[WREG]);
  TEST_ASSERT_EQUAL_STRING("addwf",inst.name);
  
}

void test_the_fucntion_of_ADDWF_should_Add_WREG_and_FileReg_STORE_in_FileREG() {
  // Test fixture
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5A,	// Add WREG to File register. W to "f".	
                    .operand2 =	1, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 0, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
	
  // Test ADDWF should store data in FileREG
  FSR[code.operand1] = 0x17;
  FSR[WREG]			 = 0xC2;
  //printf("\nFSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  addwf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(0xD9, FSR[code.operand1]);
  
  // 2nd test value
  FSR[code.operand1] = 10;
  FSR[WREG]			 = 20;
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  addwf(&code);	
  //printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  TEST_ASSERT_EQUAL_HEX8(30, FSR[code.operand1]);
  
  TEST_ASSERT_EQUAL_STRING("addwf",inst.name);
  
}