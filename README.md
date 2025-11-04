# A Stack Based Virtual Machine
[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)

A simple stack-based virtual machine built in C++. This project was inspired by Felix Angell's tutorial and serves as a stepping stone to better understand computer architecture and build more complex projects like a CHIP-8 virtual machine or an NES emulator.

## Core functionality

* **Instructions**: Implemented a set of 18 instructions to manipulate the stack, registers, and control program flow.
    * **Stack Operations**: `PSH <val>`, `POP`, `PRN`
    * **Register Operations**: `SET <reg> <val>`, `MOV <reg1> <reg2>`, `LOD <reg>`, `STR <reg>`
    * **Arithmetic**: `ADD`, `SUB`, `MUL`, `DIV`, `MOD`
    * **Control Flow**: `CMP`, `JMP <addr>`, `JEQ <addr>`, `JNE <addr>`, `JLT <addr>`, `JGT <addr>`
    * **Execution**: `HLT`
* **Registers**: Includes 6 general-purpose registers (A-F), plus the Stack Pointer (SP) and Instruction Pointer (IP).
* **Assembler**: A simple assembler is included to convert assembly-like text files into machine code that the VM can execute.(currently does not support empty lines or lines with only comments)


## Prerequisites

* A C++ compiler that supports C++11 (e.g., g++, Clang).
* The `make` build automation tool.

## Try for yourself

1. **Clone the repository**:
    ```bash
    git clone https://github.com/Shanwis/Toy-Virtual-Machine.git
    cd Toy-Virtual-Machine
    ```
2. **Run the VM**:
    ```
    make
    make run <file to run>
    ```

3.  **Write a program:**
    Create a new file, for example `my_program.asm`, with instructions for the VM.

    **`my_program.asm`**
    ```asm
    PSH 6       ; Push 5
    STR A       ; Store n in register A (A=5). Stack is empty.
    PSH 1       ; Push 1
    STR B       ; Store result in register B (B=1). Stack is empty.
    LOD A       ; Push n (from reg A)
    PSH 1       ; Push 1
    CMP         ; Compare n and 1
    JEQ 31      ; If n == 1, jump to 'end' (Address 31)
    LOD B       ; Push result (from reg B)
    LOD A       ; Push n (from reg A)
    MUL         ; Pop n, pop result. Push (result * n)
    STR B       ; Store new result in reg B. Stack is empty.
    LOD A       ; Push n (from reg A)
    PSH 1       ; Push 1
    SUB         ; Pop 1, pop n. Push (n - 1)
    STR A       ; Store new n in reg A. Stack is empty.
    JMP 8       ; Jump back to loop start (Address 8)
    LOD B       ; Push final result from reg B
    PRN         ; Print it
    HLT
    ```

4.  **Run the program:**
    Use the `make run` command and pass the program file path as an argument.
    ```bash
    make run program=my_program.asm
    ```
    *Note: The `program=` part is important!*

5. **Clean up after use**:
    ```
    make clean
    ```

## Future Scope

This is quite a simple VM. I wish to make a CHIP-8 VM in the near future as an excersise and run a tetris ROM in it. 

This was a great learning experience, maybe I will try adding a few more stuff to it, before going to more advanced topic.


