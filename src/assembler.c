#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/assembler.h"

InstructionMapping instruction_table[NUM_OF_INSTRUCTIONS] = {
    {"PSH", PSH}, {"POP", POP}, {"SET", SET},
    {"MOV", MOV}, {"LOD", LOD}, {"STR", STR},
    {"ADD", ADD}, {"SUB", SUB}, {"MUL", MUL}, {"DIV", DIV}, {"MOD", MOD},
    {"JMP", JMP}, {"JEQ", JEQ}, {"JNE", JNE}, {"JLT", JLT}, {"JGT", JGT},
    {"CMP", CMP}, {"PRN", PRN}, {"HLT", HLT}
};


InstructionMapping register_table[] = {
    {"A", A},
    {"B", B},
    {"C", C},
    {"D", D},
    {"E", E},
    {"F", F},
    {"IP", IP},
    {"SP", SP}
};

int find_opcode(const char *name) {
    for(int i=0; i<NUM_OF_INSTRUCTIONS; i++){
        if(strcmp(name,instruction_table[i].name) == 0){
            return instruction_table[i].opcode;
        }
    }
    return -1;
}

int find_register(const char *name) {
    for(int i=0; i<NUM_OF_REGISTERS; i++){
        if(strcmp(name,register_table[i].name) == 0){
            return register_table[i].opcode;
        }
    }
    return -1;
}

int assemble_file(const char *filename, int *program) {
    FILE *fp = fopen(filename, "r");
    if(!fp){
        printf("Error opening the file\n");
        return -1;
    }
    char line[128];
    int size = 0;
    while(fgets(line, 128, fp)){
        line[strcspn(line, "\n;")] = '\0';
        int opcode;
        char *instr = strtok(line, " ");
        char *arg = strtok(NULL, " ");
        if((opcode = find_opcode(instr)) == -1){
            printf("Could not find %s", instr);
            return -1;
        }
        if(size<PROGRAM_SIZE) program[size++] = opcode;
        else{printf("Overflow!"); return -1;}
        while(arg) {
            int r = find_register(arg);
            if(r == -1){
                program[size++] = atoi(arg);
            }else{
                program[size++] = r;
            }
            arg = strtok(NULL, " ");
        }
    }
    fclose(fp);
    return size;
}

