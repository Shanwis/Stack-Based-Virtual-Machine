#include "../include/virtualMachine.h"
#include "../include/assembler.h"

int main(int argc,char *argv[]){
    int program[PROGRAM_SIZE];
    int size = assemble_file(argv[1], program);
    if(size<0){
        printf("Error reading the file");
        return -1;
    }
    VM vm1;
    init_vm(&vm1, program, size);
    run(&vm1);
    return 0;
}