#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "instruction.h"

int find_opcode(const char *name);
int find_register(const char *name);
int assemble_file(const char *filename, int *program);

#endif