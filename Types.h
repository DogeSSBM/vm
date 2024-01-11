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

typedef enum{I_ADD, I_PUSH, I_END, I_NUM}Instruction;
const char* InstructionStr[I_NUM] = {"add", "push", "end"};
typedef struct Stack{
    int data;
    struct Stack *next;
}Stack;

#endif /* end of include guard: TYPES_H */
