;this is a comment to test 
PSH 5       ; Push 5
STR A       ; Store n in register A (A=5). Stack is empty.
PSH 1       ; Push 1
STR B       ; Store result in register B (B=1). Stack is empty.
loop:
    LOD A       ; Push n (from reg A)
    PSH 1       ; Push 1
    CMP         ; Compare n and 1
    JEQ finish      ; If n == 1, jump to 'end' (Address 31)
    LOD B       ; Push result (from reg B)
    LOD A       ; Push n (from reg A)
    MUL         ; Pop n, pop result. Push (result * n)
    STR B       ; Store new result in reg B. Stack is empty.
    LOD A       ; Push n (from reg A)
    PSH 1       ; Push 1
    SUB         ; Pop 1, pop n. Push (n - 1)
    STR A       ; Store new n in reg A. Stack is empty.
    JMP loop    ; Jump back to loop start (Address 8)
finish:
    LOD B       ; Push final result from reg B
    PRN         ; Print it
    HLT