#ifndef VM_H
#define VM_H

#include<stdio.h>
#include "instruction.h"

void init_vm(VM *vm, const int *program, int program_size);
int fetch(VM *vm);
bool underflow(VM *vm);
bool overflow(VM *vm);
bool validRegister(VM *vm, int reg);
void eval(VM *vm, int instr);
void run(VM *vm);

#endif