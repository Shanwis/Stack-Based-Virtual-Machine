#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdbool.h>

#define STACK_SIZE 256
#define PROGRAM_SIZE 256

typedef enum {
    PSH,    // Push immediate value to stack
    POP,    // Pop top of stack
    SET,    // Set register to value

    MOV,    // Move value from one register to another
    LOD,    // Push value from register to stack
    STR,    // Pop value from stack into register

    ADD,    // Pop two, add, push result
    SUB,    // Pop two, subtract, push result
    MUL,    // Pop two, multiply, push result
    DIV,    // Pop two, divide, push result
    MOD,    // Pop two, modulus, push result

    JMP,    // Jump to address (set IP)
    JEQ,    // Jump if equal
    JNE,    // Jump if not equal
    JLT,    // Jump if less than
    JGT,    // Jump if greater than

    CMP,    // Compare top two stack values (set a flag register)
    PRN,    // Print top of stack
    HLT,    // Halt the program

    NUM_OF_INSTRUCTIONS
} InstructionSet;

typedef enum {
    A, B, C, D, E, F, IP, SP,
    NUM_OF_REGISTERS
} Registers;

typedef struct {
    int stack[STACK_SIZE];
    int registers[NUM_OF_REGISTERS];
    int program[256];
    bool running;
    bool flag_equal;
    bool flag_greater;
    bool flag_less;
} VM;

typedef struct{
    const char *name;
    int opcode;
} InstructionMapping;

#endif