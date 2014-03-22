#include "unity.h"
#include "Bytecode.h"
#include "ADDWF.h"
#include "CException.h"
#include <stdio.h>

void setUp() {}
void tearDown() {}

void test_ADDWF_should_add_the_value_in_WREG_with_FileReg_and_STORE_in_WREG() {
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

void test_ADDWF_should_add_the_value_in_WREG_with_FileReg_and_STORE_in_FileREG() {
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

void test_ADDWF_given_the_operand3_set_to_1_and_should_add_the_value_in_WREG_with_FileReg_and_STORE_in_WREG_with_the_BSR_address(){
  
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,	// Add WREG to File register. W to "f".	
                    .operand2 =	0, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).
                  };

  FSR[code.operand1] = 10;
  FSR[WREG]			 = 20;
  FSR[BSR]			 = 1;	//SELECTED BANK 1 = 0x01
  addwf(&code);
  
  //TESTing value 
  // printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  // printf("FSR[BSR] :%x	FSR[code.operand1] :%#x\n",FSR[BSR],FSR[WREG]);
  // printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  TEST_ASSERT_EQUAL_HEX8(10,FSR[code.operand1]);					//The Added value is 30 but store in WREG not in FileReg, thus the value in here still 10
  TEST_ASSERT_EQUAL_HEX8(30,FSR[WREG]);								//The Added value is 30 and the value store in WREG, with the operand 1 set to 0
  TEST_ASSERT_EQUAL_HEX8(0x101,code.operand1);		//The selected BSR is bank 1 which start from 0x01 followed by the Opcode Address 5A
}
void test_ADDWF_given_the_operand3_set_to_1_and_should_add_the_value_in_WREG_with_FileReg_and_STORE_in_FileReg_with_the_BSR_address(){
  
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFC,	// Add WREG to File register. W to "f".	
                    .operand2 =	1, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).
                  };

  FSR[code.operand1+(0x0F00)] = 20;
  FSR[WREG]			 = 30;
  FSR[BSR]			 = 15;	//SELECTED BANK 15 = 0x0F (last bank)
  addwf(&code);
  
  //TESTing value 
  // printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  // printf("FSR[BSR] :%x	FSR[code.operand1] :%#x\n",FSR[BSR],FSR[code.operand1]);
  // printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  TEST_ASSERT_EQUAL_HEX8(50,FSR[code.operand1+(0x0F00)]);					//The Added value is 50 and the value store in FileReg, with the operand 1 set to 1
  TEST_ASSERT_EQUAL_HEX8(30,FSR[WREG]);								//The Added value is 30 but store in FileReg not in WREG, thus the value in here still 30
  TEST_ASSERT_EQUAL_HEX8(0xFFC,code.operand1);		//The selected BSR is bank 15 last bank which start from 0x0F followed by the Opcode Address FC
}
void test_ADDWF_invalid_range() {
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFFFF,
                    .operand2 =	0, 
                    .operand3 = 0, 
                  };
  CException errorRange;
  Try{
	addwf(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
  }
}
void test_ADDWF_invalid_BSR() {
  Instruction inst = {
                      .mnemonic = ADDWF,
                      .name = "addwf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFF,
                    .operand2 =	1, 
                    .operand3 = 1, 
                  };
  FSR[BSR] = 20;
  CException errorBSR;
  Try{
	addwf(&code);
  }
  Catch(errorBSR){
	TEST_ASSERT_EQUAL(INVALID_BSR,errorBSR);
  }
}
void test_ADDWF_given_the_operand1_value_more_than_0x80_store_in_FileReg_also_with_possibility_input(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xE1, //more than 0x79
                    .operand2 =	-1,   //-1 is empty :default FileReg		
                    .operand3 = -1,   //default ACCESS	
                  };
  FSR[code.operand1+(0x0F00)] = 10;
  FSR[WREG] = 30;
  addwf(&code);
  TEST_ASSERT_EQUAL(40,FSR[code.operand1+(0x0F00)]);
  TEST_ASSERT_EQUAL(40,FSR[0xFE1]);
}
void test_ADDWF_given_the_operand1_value_less_than_0x80_store_in_FileReg_also_with_possibility_input(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01, 	// less than 0x80
                    .operand2 =	-3, 		
                    .operand3 = ACCESS, //(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)	
                  };
  FSR[code.operand1] = 10;
  FSR[WREG] = 30;
  addwf(&code);
  TEST_ASSERT_EQUAL(40,FSR[code.operand1]);
  TEST_ASSERT_EQUAL(40,FSR[0x001]);
}
void test_ADDWF_given_the_operand1_value_more_than_0x80_store_in_WREG_also_with_possibility_input(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xE1, 	//more than 0x79
                    .operand2 =	0, 		
                    .operand3 = -5, 	//(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)
                  };
  FSR[code.operand1+(0x0F00)] = 10;
  FSR[WREG] = 30;
  addwf(&code);
  TEST_ASSERT_EQUAL(40,FSR[WREG+(0x0F00)]);
}
void test_ADDF_given_the_operand1_value_less_than_0x80_store_in_WREG_also_with_possibility_input(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01, // less than 0x80
                    .operand2 =	W, 	  // W = -2, valid if with -2
                    .operand3 = -1,   //default set to ACCESS if is empty	
                  };
  FSR[code.operand1] = 10;
  FSR[WREG] = 30;
  addwf(&code);
  TEST_ASSERT_EQUAL(40,FSR[WREG]);
}
void test_ADDWF_given_the_operand2_and_operand3_with_invalid_input_should_catch_error(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	BANKED, 	// invalid with BANKED in operand2
                    .operand3 = W, 			// invalid with WREG in operand3
                  };
  CException errorRange;
  FSR[code.operand1] = 10;
  FSR[WREG] = 30;
  Try{
	addwf(&code);
	TEST_ASSERT_EQUAL(40,FSR[WREG]);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_ADDWF_given_the_operand2_and_operand3_with_invalid_input_should_catch_error2(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	5431, 	// invalid input in operand2
                    .operand3 = -3210, // invalid input in operand3
                  };
  CException errorRange;
  FSR[code.operand1] = 10;
  FSR[WREG] = 30;
  Try{
	addwf(&code);
	TEST_ASSERT_EQUAL(40,FSR[WREG]);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_ADDWF_for_the_affected_status_negative_flag(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	W,
                    .operand3 = ACCESS,
                  };
  FSR[code.operand1] = -1;
  FSR[WREG] = -1;
  addwf(&code);
  TEST_ASSERT_EQUAL(-2,FSR[WREG]);
  TEST_ASSERT_EQUAL(0b00010000,FSR[STATUS]);// - - - N OV Z DC C
}
void test_ADDWF_for_the_affected_status_overflow_flag(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	F,
                    .operand3 = ACCESS,
                  };
  FSR[code.operand1] = -128;
  FSR[WREG] = -1;
  addwf(&code);
  TEST_ASSERT_EQUAL(127,FSR[code.operand1]);
  TEST_ASSERT_EQUAL(0b00001000,FSR[STATUS]);// - - - N OV Z DC C
}
void test_ADDWF_for_the_affected_status_zero_flag(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	F,
                    .operand3 = -1,
                  };
  FSR[code.operand1] = 0;
  FSR[WREG] = 0;
  addwf(&code);
  TEST_ASSERT_EQUAL(0,FSR[code.operand1]);
  TEST_ASSERT_EQUAL(0b00000100,FSR[STATUS]);// - - - N OV Z DC C
}
void test_ADDWF_for_the_affected_status_digitCarry_flag(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	-2,
                    .operand3 = -5,
                  };
  FSR[code.operand1] = 15;
  FSR[WREG] = 15;
  addwf(&code);
  TEST_ASSERT_EQUAL(30,FSR[WREG]);
  TEST_ASSERT_EQUAL(0b00000010,FSR[STATUS]);// - - - N OV Z DC C
}
void test_ADDWF_for_the_affected_status_Carry_flag(){
  Instruction inst = {.mnemonic = ADDWF,.name = "addwf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	-3,
                    .operand3 = 0,
                  };
  FSR[code.operand1] = 255;
  FSR[WREG] = 1;
  addwf(&code);
  TEST_ASSERT_EQUAL(0,FSR[code.operand1]);
  //TEST_ASSERT_EQUAL(0b00000001,FSR[STATUS]);// over 0xFF > become 0
}
