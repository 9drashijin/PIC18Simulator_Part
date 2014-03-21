#include "unity.h"
#include "Bytecode.h"
#include "BSF.h"
#include <stdio.h>
#include "CException.h"

void setUp() {}
void tearDown() {}

void test_BSF_should_set_the_first_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101101, FSR[code.operand1]);		//ADDRESS at 0x6C or with bit 0000 0001
  TEST_ASSERT_EQUAL(109, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6D, FSR[code.operand1]);
}
void test_BSF_should_set_the_second_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101110, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0000 0010
  TEST_ASSERT_EQUAL(110, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6E, FSR[code.operand1]);
}
void test_BSF_should_set_the_third_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101100, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0000 0100
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
  
  //test for other value
  FSR[code.operand1] = 0b1011;
  bsf(&code);
  TEST_ASSERT_EQUAL(0b1111, FSR[code.operand1]);
}
void test_BSF_should_set_the_fourth_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101100, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0000 1000
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
  
  //test for other value
  FSR[code.operand1] = 0b0011;
  bsf(&code);
  TEST_ASSERT_EQUAL(0b1011, FSR[code.operand1]);
}
void test_BSF_should_set_the_fifth_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01111100, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0001 0000
  TEST_ASSERT_EQUAL(124, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x7c, FSR[code.operand1]);
  
}
void test_BSF_should_set_the_sixth_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101100, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0010 0000
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
  
  //test for other value
  FSR[code.operand1] = 0b00001010;
  bsf(&code);
  TEST_ASSERT_EQUAL(0b00101010, FSR[code.operand1]);
}
void test_BSF_should_set_the_seventh_bit_to_1(){
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
  FSR[code.operand1] = 0x6C; //0b01101100
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  TEST_ASSERT_EQUAL(0b01101100, FSR[code.operand1]);		//ADDRESS at 0x6C with bit 0100 0000
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);
	
  //test for other value
  FSR[code.operand1] = 0b01001010;
  bsf(&code);
  TEST_ASSERT_EQUAL(0b01001010, FSR[code.operand1]);
}
void test_BSF_should_set_the_last_bit_to_1(){
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
  FSR[code.operand1] = 0b00000000;
  bsf(&code);
  //printf("FSR[code.operand1] :%d\n",FSR[code.operand1]);
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);	//ADDRESS at 0x6C with bit 1000 0000
  TEST_ASSERT_EQUAL(-(0b10000000), FSR[code.operand1]); //error become negative
  TEST_ASSERT_EQUAL(-128, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x80, FSR[code.operand1]);
}

void test_BSF_given_the_operand3_set_to_1_and_should_set_the_fifth_bit_to_1_with_the_BSR_address(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xB9,	// address of FileReg	
                    .operand2 =	4, 		// (0~7), Set bit 0 to 7
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x9B; //10011011
  FSR[BSR]			 = 8;		//BANK 8 is selected start from 0x05
  bsf(&code);
  
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  //printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  TEST_ASSERT_EQUAL_HEX8(0x9B, FSR[code.operand1]);					//ADDRESS of FileREg is at 0x9B

  TEST_ASSERT_EQUAL_HEX8(0xB9,code.operand1);						//The Address of FileReg Operand1 is B9 = 185 in decimal
  TEST_ASSERT_EQUAL_HEX8(0x08,FSR[BSR]);							//The selected BSR is bank 8 last bank and the Opcode should start form here.
  TEST_ASSERT_EQUAL_HEX8(0x8B9,code.operand1 + (FSR[BSR]<<8));		//The selected BSR is bank 8 last bank which start from 0x08 followed by the Opcode Address B9
}

void test_BSF_given_the_operand3_set_to_1_should_set_the_seventh_bit_to_1_with_the_BSR_address(){
  // Test fixture
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFC,	// address of FileReg	
                    .operand2 =	6, 		// (0~7), Set bit 0 to 7
                    .operand3 = 1, 		// 0 = Access Bank is Selected, BSR ignored\
										   1 = BSR is used to select the GPR bank (default).		
                  };
  // TEST the Bit Set
  //printf("code.operand1 :%d	code.operand2 :%d\n",code.operand1,code.operand2);
  FSR[code.operand1] = 0x6C; //0b01101100
  FSR[BSR]			 = 5;		//BANK 5 is selected start from 0x05
  bsf(&code);
  
  //printf("FSR[code.operand2] :%d\n",FSR[code.operand2]);
  // printf("code.operand1 + (FSR[BSR]<<8) :%#x\n",code.operand1 + (FSR[BSR]<<8));		// <<8 shift left 8 same as *256
  
  TEST_ASSERT_EQUAL(0b01101100, FSR[code.operand1]);				//ADDRESS at 0x6C with bit 0100 0000
  TEST_ASSERT_EQUAL(108, FSR[code.operand1]);
  TEST_ASSERT_EQUAL_HEX8(0x6c, FSR[code.operand1]);					//ADDRESS of FileREg is at 0x6C

  TEST_ASSERT_EQUAL_HEX8(0xFC,code.operand1);						//The Address of FileReg Operand1 is FC = 252 in decimal
  TEST_ASSERT_EQUAL_HEX8(0x05,FSR[BSR]);							//The selected BSR is bank 5 last bank and the Opcode should start form here.
  TEST_ASSERT_EQUAL_HEX8(0x5FC,code.operand1 + (FSR[BSR]<<8));		//The selected BSR is bank 5 last bank which start from 0x05 followed by the Opcode Address FC
  
  //test for other value
  FSR[code.operand1] = 0b00001111;
  bsf(&code);
  TEST_ASSERT_EQUAL(0b01001111, FSR[code.operand1]);
}

void test_BSF_invalid_range() {
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFFFF,
                    .operand2 =	0, 
                    .operand3 = 0, 
                  };
  CException errorRange;
  Try{
	bsf(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_RANGE,errorRange);
  }
}
void test_BSF_invalid_BSR() {
  Instruction inst = {
                      .mnemonic = BSF,
                      .name = "bsf"
                     };	
  Bytecode code = { .instruction = &inst,
                    .operand1 = 0xFF,
                    .operand2 =	1, 
                    .operand3 = 1, 
                  };
  FSR[BSR] = 20;
  CException errorRange;
  Try{
	bsf(&code);
  }
  Catch(errorRange){
	TEST_ASSERT_EQUAL(INVALID_BSR,errorRange);
  }
}