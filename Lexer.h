#ifndef LEXER_H
#define LEXER_H

void skipSpace(char **input)
{
    assertExpr(input && *input);
    while(isspace(**input))
        *input += 1;
}

Token* tokenNew(char **input)
{
    assertExpr(*input);
    if(**input == '\0')
        return NULL;
    const size_t len = strcspn(*input, " \n\t");
    if(!len)
        return NULL;
    Token *token = calloc(1, sizeof(Token));
    token->str = calloc(len, sizeof(char));
    memcpy(token->str, *input, len);
    *input = *input + len;
    return token;
}

Token* tokenAppend(Token *head, Token *tail)
{
    if(!head)
        return tail;
    Token *cur = head;
    while(cur->next)
        cur = cur->next;
    cur->next = tail;
    return head;
}

void tokenFree(Token *token)
{
    while(token){
        Token *next = token->next;
        free(token->str);
        free(token);
        token = next;
    }
}

void tokenPrint(Token *token)
{
    while(token){
        printf("%s\n", token->str);
        token = token->next;
    }
}

Token* tokenize(char *input)
{
    Token *token = NULL;
    while(1){
        skipSpace(&input);
        if(*input == '\0')
            return token;
        token = tokenAppend(token, tokenNew(&input));
    }

    return token;
}

Token tokenConsume(Token **token)
{
    assertExpr(token);
    assertExpr(*token);
    const Token ret = **token;
    Token *newHead = (*token)->next;
    free(*token);
    *token = newHead;
    return ret;
}

#endif /* end of include guard: LEXER_H */
