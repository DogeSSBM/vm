#include "Includes.h"

Stack* stackAppend(Stack *head, Stack *tail)
{
    if(!head)
        return tail;
    Stack *cur = head;
    while(cur->next)
        cur = cur->next;
    cur->next = tail;
    return head;
}

Stack* stackPush(Stack *oldHead, Stack *newHead)
{
    return stackAppend(newHead, oldHead);
}

Stack* stackNew(const int data)
{
    Stack *stack = calloc(1, sizeof(Stack));
    assertExpr(stack);
    stack->data = data;
    return stack;
}

void stackPrint(Stack *stack)
{
    while(stack){
        printf("%i\n", stack->data);
        stack = stack->next;
    }
}

Token* tokenSearchLabel(Token *head, char *label)
{
    while(head){
        if(!strcmp(head->str+1, label))
            return head;
        head = head->next;
    }
    panic("Could not find label: \"%s\"", label);
    return NULL;
}

int main(int argc, char **argv)
{
    if(argc != 2)
        panic("Usage:\n\t\t%s <Input File>\n", argv[0]);

    char *src = fileReadText(argv[1]);
    Token *token = tokenize(src);
    Token *head = token;
    free(src);
    Stack *stack = NULL;
    while(token){
        printf("token: %s\n", token->str);
        Instruction i = 0;
        if(token->str[i] == ':'){
            token = token->next;
            continue;
        }
        for(i = 0; i <= I_NUM; i++){
            if(i >= I_NUM){
                tokenPrint(token);
                stackPrint(stack);
                panic("uh oh");
            }
            if(!strcmp(token->str, InstructionStr[i]))
                break;
        }

        switch(i){
            case I_BRZ:{
                assertExpr(stack);
                token = token->next;
                assertExpr(token);
                if(stack->data == 0){
                    token = tokenSearchLabel(head, token->str);
                    break;
                }
                token = token->next;
                break;
            }
            case I_BRNZ:{
                assertExpr(stack);
                token = token->next;
                assertExpr(token);
                if(stack->data != 0){
                    token = tokenSearchLabel(head, token->str);
                    break;
                }
                token = token->next;
                break;
            }
            case I_GOTO:{
                token = token->next;
                assertExpr(token);
                token = tokenSearchLabel(head, token->str);
                break;
            }
            case I_ADD:{
                assertExpr(stack);
                const int a = stack->data;
                Stack *next = stack->next;
                assertExpr(next);
                next->data += a;
                free(stack);
                stack = next;
                token = token->next;
                break;}
            case I_SUB:{
                assertExpr(stack);
                const int a = stack->data;
                Stack *next = stack->next;
                assertExpr(next);
                next->data -= a;
                free(stack);
                stack = next;
                token = token->next;
                break;}
            case I_MUL:{
                assertExpr(stack);
                const int a = stack->data;
                Stack *next = stack->next;
                assertExpr(next);
                next->data *= a;
                free(stack);
                stack = next;
                token = token->next;
                break;}
            case I_PUSH:
                token = token->next;
                assertExpr(token);
                const bool neg = *token->str == '-';
                for(st i = 0; i < strlen(token->str); i++)
                    assertExpr(isdigit(token->str[i]) || (i == 0 && neg));
                char *end = NULL;
                if(neg)
                    assertExpr(strlen(token->str) > 1);
                const ul nat = strtoul(neg ? token->str+1 : token->str, &end, 10);
                stack = stackPush(stack, stackNew((int)nat * (neg ? -1 : 1)));
                token = token->next;
                break;
            case I_DUP:
                stack = stackPush(stack, stackNew(stack->data));
                token = token->next;
                break;
            case I_MOD:{
                assertExpr(stack);
                const int a = stack->data;
                Stack *next = stack->next;
                assertExpr(next);
                next->data %= a;
                free(stack);
                stack = next;
                token = token->next;
                break;}
            case I_END:
                token = token->next;
                break;
            default:
                panic("unknown instruction: %zu", i);
                break;
        }
    }
    stackPrint(stack);
    return 0;
}
