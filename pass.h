/*
 * Header file which defines methods for the second pass of the assembler.
 * 
 * Authors:Tanush Samson
 * Date: 10/5/17
 */

#ifndef Assembler_pass2_h
#define Assembler_pass2_h

/*getBin function determines the unsigned binary value of a particular decimal number for a given number of bits
 */
char* getBin(int dec, int range);

/* getNextToken finds the next token in the line using delimeters of ',', '(', ')', ':', or '\0'
 */
int getNextToken(char **reg,char **tokBegin,char **tokEnd);

/* getRegisterCode determines the binary representation of each register
 */
char* getRegisterCode(char * regName);


/* getNameInfo determines all of the information about the instruction that can be determined by the name of the instruction
 */
int getNameInfo(char * name, char ** info);


/*getRegs assigns the source register, the shift amount, the destination register, and the address to the instruction
 */
int getRegs(char** rs, char** rt, char** rd, char** shamt, char** address, char* tokBegin, char* tokEnd);


#endif