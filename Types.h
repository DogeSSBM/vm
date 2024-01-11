#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;
typedef unsigned long ul;
typedef size_t st;
typedef FILE File;

typedef struct Token{
    char *str;
    struct Token *next;
}Token;

typedef enum{I_PRINT1, I_PRINT, I_REACH, I_PLUCK, I_BACK, I_BRZ, I_BRNZ, I_GOTO, I_ADD, I_SUB, I_MUL, I_DIV, I_PUSH, I_POP, I_DUP, I_MOD, I_LABEL, I_END, I_NUM}Instruction;
const char* InstructionStr[I_NUM] = {"print1", "print", "reach", "pluck", "back", "brz", "brnz", "goto", "add", "sub", "mul", "div", "push", "pop", "dup", "mod", "end"};
typedef struct Stack{
    int data;
    struct Stack *next;
}Stack;

#endif /* end of include guard: TYPES_H */
