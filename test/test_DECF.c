#include "unity.h"
#include "Bytecode.h"
#include "DECF.h"
#include <stdio.h>
#include "CException.h"

void setUp() {}
void tearDown() {}

void test_DECF_should_decrement_the_value_in_FileReg_and_STORE_in_WREG() {
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

void test_DECF_should_decrement_the_value_in_FileReg_and_STORE_in_FileREG() {
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

void test_DECF_given_the_operand3_set_to_1_and_should_decrement_the_value_in_FileReg_and_STORE_in_WREG_with_the_BSR_address(){
  
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x5F,	// Add WREG to File register. W to "f".	
                    .operand2 =	0, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).
                  };

  FSR[code.operand1+(0x0F00)] = 88;
  FSR[BSR]			 = 10;	//SELECTED BANK 10 = 0x0A
  decf(&code);
  
  //TESTing value 
  // printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  // printf("FSR[BSR] :%x	FSR[code.operand1] :%#x\n",FSR[BSR],FSR[WREG]);
  // printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  TEST_ASSERT_EQUAL_HEX8(88,FSR[code.operand1+(0x0F00)]);					//The Decremented value is 87 but store in WREG not in FileReg, thus the value in here still 88
//  TEST_ASSERT_EQUAL(87,FSR[WREG]);								//The Decremented value is 87 and the value store in WREG, with the operand 1 set to 0
  TEST_ASSERT_EQUAL_HEX8(0x5F,code.operand1);						//The Address of FileReg Operand1 is 5F = 95 in decimal
  TEST_ASSERT_EQUAL_HEX8(0x0A,FSR[BSR]);							//The selected BSR is bank 10 and the Opcode should start form here.
  TEST_ASSERT_EQUAL_HEX8(0xA5F,code.operand1 + (FSR[BSR]<<8));		//The selected BSR is bank 10 which start from 0x0A followed by the Opcode Address 5F
  FSR[WREG] = 0; 	//clear the WREG to 0
}

void test_DECF_given_the_operand3_set_to_1_and_should_decrement_the_value_in_FileReg_and_STORE_in_FileReg_with_the_BSR_address(){
  
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xE1,	// Add WREG to File register. W to "f".	
                    .operand2 =	1, 		// 0 = stored in WREG , 1 = stored back in register "f".
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).
                  };

  FSR[code.operand1+(0x0F00)] = 0b1111;
  FSR[BSR]			 = 13;	//SELECTED BANK 13 = 0x0D
  decf(&code);
  
  //TESTing value 
  // printf("FSR[code.operand1] :%d	FSR[WREG] :%d\n",FSR[code.operand1],FSR[WREG]);
  // printf("FSR[BSR] :%x	FSR[code.operand1] :%#x\n",FSR[BSR],FSR[code.operand1]);
  // printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  //THE WREG IS CLEARED to 0 and operand1 is set to 1, the result is stored in FileREG not WREG thus the result should be 0
  TEST_ASSERT_EQUAL(0b1110,FSR[code.operand1+(0x0F00)]);				//The Decremented value is 1110 and the value store in FileReg, with the operand 1 set to 1
  TEST_ASSERT_EQUAL(0,FSR[WREG]);									//The Decremented value is 1110 but store in FileReg not in WREG, thus the value in here still 0
  TEST_ASSERT_EQUAL_HEX8(0xE1,code.operand1);						//The Address of FileReg Operand1 is E1 = 225 in decimal
  TEST_ASSERT_EQUAL_HEX8(0x0D,FSR[BSR]);							//The selected BSR is bank 13 last bank and the Opcode should start form here.
  TEST_ASSERT_EQUAL_HEX8(0xDE1,code.operand1 + (FSR[BSR]<<8));		//The selected BSR is bank 13 last bank which start from 0x0D followed by the Opcode Address E1
}
void test_DECF_invalid_range() {
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFFFF, //invalid address
                    .operand2 =	0, 
                    .operand3 = 0, 
                  };
  CException errorRange;
  Try{
	decf(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
  }
}
void test_DECF_invalid_BSR() {
  Instruction inst = {
                      .mnemonic = DECF,
                      .name = "decf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFF,
                    .operand2 =	1, 
                    .operand3 = 1, 
                  };
  FSR[BSR] = 20;	// over bank 15	  
  CException errorRange;
  Try{
	decf(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_BSR,errorRange);
  }
}
void test_DECF_given_the_operand1_value_more_than_0x80_store_in_FileReg_also_with_possibility_input(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xE1, //more than 0x79
                    .operand2 =	1, 		
                    .operand3 = 0, 		
                  };
  FSR[code.operand1+(0x0F00)] = 10;
  decf(&code);
  TEST_ASSERT_EQUAL(9,FSR[code.operand1+(0x0F00)]);
  TEST_ASSERT_EQUAL(9,FSR[0xFE1]);
}
void test_DECF_given_the_operand1_value_less_than_0x80_store_in_FileReg_also_with_possibility_input(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01, 	// less than 0x80
                    .operand2 =	F, 		
                    .operand3 = ACCESS, //(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)	
                  };
  FSR[code.operand1] = 10;
  decf(&code);
  TEST_ASSERT_EQUAL(9,FSR[code.operand1]);
  TEST_ASSERT_EQUAL(9,FSR[0x001]);
}
void test_DECF_given_the_operand1_value_more_than_0x80_store_in_WREG_also_with_possibility_input(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xE1, 	//more than 0x79
                    .operand2 =	0, 		
                    .operand3 = -5, 	//(ACCESS=-5,BANKED=-4,F=-3,W=-2,empty=-1)
                  };
  FSR[code.operand1+(0x0F00)] = 10;
  decf(&code);
  TEST_ASSERT_EQUAL(9,FSR[WREG+(0x0F00)]);
}
void test_DECF_given_the_operand1_value_less_than_0x80_store_in_WREG_also_with_possibility_input(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01, // less than 0x80
                    .operand2 =	W, 	  // W = -2, valid if with -2
                    .operand3 = -1,   //default set to ACCESS if is empty	
                  };
  FSR[code.operand1] = 10;
  decf(&code);
  TEST_ASSERT_EQUAL(9,FSR[WREG]);
}
void test_DECF_given_the_operand2_and_operand3_with_invalid_input_should_catch_error(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	BANKED, 	// invalid with BANKED in operand2
                    .operand3 = W, 			// invalid with WREG in operand3
                  };
  CException errorRange;
  FSR[code.operand1] = 10;
  Try{
	decf(&code);
	TEST_ASSERT_EQUAL(9,FSR[WREG]);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}
void test_DECF_given_the_operand2_and_operand3_with_invalid_input_should_catch_error2(){
  Instruction inst = {.mnemonic = DECF,.name = "decf"};	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0x01,
                    .operand2 =	-10000, 	// invalid input in operand2
                    .operand3 = 10000, 		// invalid input in operand3
                  };
  CException errorRange;
  FSR[code.operand1] = 10;
  Try{
	decf(&code);
	TEST_ASSERT_EQUAL(9,FSR[WREG]);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_OPERAND,errorRange);
  }
}