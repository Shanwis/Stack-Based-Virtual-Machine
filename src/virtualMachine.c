#include "../include/virtualMachine.h"

void init_vm(VM *vm, const int *program, int program_size){
    for(int i=0;i<NUM_OF_REGISTERS;i++){
        vm->registers[i] = 0;
    }
    vm->registers[SP] = -1;

    for(int i=0; i<program_size; i++){
        vm->program[i] = program[i];
    }
    vm->flag_equal = false;
    vm->flag_greater = false;
    vm->flag_less = false;
    vm->running = true;
}

int fetch(VM *vm) {
    if (vm->registers[IP] >= PROGRAM_SIZE) {
        printf("Instruction pointer out of bounds!\n");
        vm->running = false;
        return HLT;
    }
    return vm->program[vm->registers[IP]++];
}

bool underflow(VM *vm){
    if (vm->registers[SP] < 0) {
        printf("Stack underflow!\n");
        vm->running = false;
        return true;
    }
    return false;
}

bool overflow(VM *vm){
    if (vm->registers[SP] >= STACK_SIZE-1) {
        printf("Stack overflow!\n");
        vm->running = false;
        return true;
    }
    return false;
}

bool validRegister(VM *vm, int reg){
    if(reg < 0 || reg >= NUM_OF_REGISTERS){
        printf("Invalid register %d\n", reg);
        vm->running = false;
        return false;
    }
    return true;
}

bool validJump(VM *vm, int pos){
    if(pos<0 || pos>=PROGRAM_SIZE){
        printf("Invalid position jump\n");
        vm->running = false;
        return false;
    }
    return true;
}

void eval(VM *vm, int instr) {
    switch (instr) {
        case HLT:{
            vm->running = false;
            break;
        }
        case PSH: {
            if(overflow(vm)) break;
            vm->stack[++vm->registers[SP]] = fetch(vm);
            break;
        }
        case POP: {
            if (underflow(vm)) break;
            printf("Popped %d\n",vm->stack[vm->registers[SP]--]);
            break;
        }
        case SET: {
            int reg = fetch(vm);
            int pos = fetch(vm);
            if(validRegister(vm, reg)) vm->registers[reg] = pos;
            break;
        }
        case MOV: {
            int reg1 = fetch(vm);
            int reg2 = fetch(vm);
            if(validRegister(vm,reg1) && validRegister(vm,reg2)){
                vm->registers[reg1] = vm->registers[reg2];
            }
            break;
        }
        case LOD: {
            int reg = fetch(vm);
            if(validRegister(vm,reg)){
                if(overflow(vm)) break;
                vm->stack[++vm->registers[SP]] = vm->registers[reg];
            }
            break;
        }
        case STR: {
            int reg = fetch(vm);
            if(validRegister(vm,reg)){
                if(underflow(vm)) break;
                vm->registers[reg] = vm->stack[vm->registers[SP]--];
            }
            break;
        }
        case ADD: {
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on ADD!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            int result = b+a;
            vm->stack[++vm->registers[SP]] = result;
            break;
        }
        case SUB: {
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on SUB!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            int result = b-a;
            vm->stack[++vm->registers[SP]] = result;
            break;
        }
        case MUL: {
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on MUL!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            int result = b*a;
            vm->stack[++vm->registers[SP]] = result;
            break;
        }
        case DIV: {
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on DIV!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            if(a == 0){
                printf("Can't perform division as element is zero");
                vm->running = false;
                break;
            }

            int result = b/a;
            vm->stack[++vm->registers[SP]] = result;
            break;
        }
        case MOD: {
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on MOD!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            if(a == 0){
                printf("Can't perform division as element is zero");
                vm->running = false;
                break;
            }

            int result = b%a;
            vm->stack[++vm->registers[SP]] = result;
            break;
        }
        case CMP:{
            if (vm->registers[SP] < 1) {
                printf("Stack underflow on CMP!\n");
                vm->running = false;
                break;
            }
            int a = vm->stack[vm->registers[SP]--];
            int b = vm->stack[vm->registers[SP]--];

            vm->flag_equal = false;
            vm->flag_greater = false;
            vm->flag_less = false;

            if(b>a) vm->flag_greater = true;
            else if(b<a) vm->flag_less = true;
            else vm->flag_equal = true;

            vm->stack[++vm->registers[SP]] = b;
            vm->stack[++vm->registers[SP]] = a;
            
            break;
        }
        case JMP: {
            int pos = fetch(vm);
            if(!validJump(vm,pos)) break;
            vm->registers[IP] = pos;
            break;
        }
        case JEQ: {
            int pos = fetch(vm);
            if(!vm->flag_equal) break;
            if(!validJump(vm,pos)) break;
            vm->registers[IP] = pos;
            break;
        }
        case JNE: {
            int pos = fetch(vm);
            if(vm->flag_equal) break;
            if(!validJump(vm,pos)) break;
            vm->registers[IP] = pos;
            break;
        }
        case JGT: {
            int pos = fetch(vm);
            if(!vm->flag_greater) break;
            if(!validJump(vm,pos)) break;
            vm->registers[IP] = pos;
            break;
        }
        case JLT: {
            int pos = fetch(vm);
            if(!vm->flag_less) break;
            if(!validJump(vm,pos)) break;
            vm->registers[IP] = pos;
            break;
        }
        case PRN: {
            if(underflow(vm)) break;
            printf("Top %d\n",vm->stack[vm->registers[SP]]);
            break;
        }
        default:
            printf("Unknown instruction %d\n", instr);
            vm->running = false;
            break;
    }
};

void run(VM *vm){
    while(vm->running){
        eval(vm, fetch(vm));
    }
}