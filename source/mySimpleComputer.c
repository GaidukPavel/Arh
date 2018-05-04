#include "mySimpleComputer.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#define N 100

int mem[100];
extern uint8_t flags;
int sc_memoryInit(){
	for (int i = 0; i < N; i++){
		mem[i] = 0;
	}
	extern struct memCell current;
	current.pointer = 0;
	current.x = 0;
	current.y = 0;
	return 0;
}

int sc_memorySet(int address, int value){
	if (address > 99 || address < 0)
		return -1;
	mem[address] = value;
	return 0;
}

int sc_memoryGet(int address, int * value){
	if (address > 99 || address < 0)
		return -1;
	*value = mem[address];
	return 0;
}

int sc_memorySave(char * filename){
	FILE * output = NULL;
	output = fopen(filename, "wb");
	if (output == NULL)
		return -1;
	fwrite(mem, sizeof(int), N, output);
	fclose(output);
	return 0;
}

int sc_memoryLoad(char * filename){
	FILE * input = NULL;
	input = fopen(filename, "rb");
	if (input == NULL)
		return -1;
	fread(mem, sizeof(int), N, input);
	fclose(input);
	return 0;
}

int sc_regInit(){
	flags = 0x0;
	return 0;
}

int sc_regSet(int reg, int value){
	flags &= ~reg;
	if (value == 1)
		flags |= reg;
	return 0;
}
int sc_regGet(int reg, int * value){
	int ch = flags;
	ch &= reg;
	if (ch == 0)
		*value = 0;
	else
		*value = 1;
	return 0;
}

int sc_commandEncode(int command, int operand, int * value){
	if (command > 76 || command < 10){
		flags |= E;		
		return -1;
	}
	if (operand > 127 || operand < 0)
		return 18;
	*value = 0;	
	*value += command;
	*value <<= 7;
	*value += operand;
	return 0;
}

int sc_commandDecode(int value, int * command, int * operand){
	unsigned int u = value;
	*operand = u & 0x7f;
	u = value >> 7;
	*command = u & 0x7f;
	return 0;
}

