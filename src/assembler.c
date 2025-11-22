#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <Toy-Virtual-Machine/assembler.h>

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

Labels label_table[128];

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

int find_label(const char *name, int size_labels) {
    for(int i=0; i<size_labels; i++){
        char nname[64];
        strcpy(nname, name);
        nname[strcspn(nname," \n;")] = '\0';
        if(strcmp(nname,label_table[i].label) == 0){
            return label_table[i].address;
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
    int size_labels = 0;
    int size_lines = 0;

    while(fgets(line,128,fp)){
        line[strcspn(line, "\n;")] = '\0';
        if(line[0] == '\0') continue;
        int len = strlen(line);
        if(line[len-1] == ':'){
            line[len-1] = '\0';
            strcpy(label_table[size_labels].label,line);
            label_table[size_labels].address = size_lines;
            //printf("%s label %d value\n",line, size_lines);
            size_labels++;  
            continue;
        }else{
            char *arg = strtok(line," ");
            while(arg){
                size_lines++;
                arg = strtok(NULL," ");
            }
        }
    }

    rewind(fp);
    int program_size = 0;

    while(fgets(line, 128, fp)){
        line[strcspn(line, "\n;")] = '\0';
        if(line[0] == '\0') continue;

        int len = strlen(line);
        if(line[len-1] == ':') continue;

        char *instr = strtok(line, " ");
        int opcode = find_opcode(instr);
        if((opcode = find_opcode(instr)) == -1){
            printf("Could not find %s", instr);
            return -1;
        }
        if(program_size<PROGRAM_SIZE) program[program_size++] = opcode;
        else{printf("Overflow!"); return -1;}

        char *arg = strtok(NULL, " ");
        while(arg) {
            int r = find_register(arg);
            int l = find_label(arg,size_labels);
            if(r != -1) program[program_size++] = r;
            else if(l != -1) program[program_size++] = l;
            else program[program_size++] = atoi(arg);
            arg = strtok(NULL, " ");
        }
    }
    fclose(fp);
    return program_size;
}

