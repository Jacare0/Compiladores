// SistVarredura.c
// Implementação de um scanner (analisador léxico) simples em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// DEFINIÇÃO DOS TIPOS DE TOKENS
typedef enum {
    // Fim de arquivo
    T_EOF,
    
    // Erro
    T_ERROR,

    // Identificadores e Números 
    T_ID,
    T_NUM,

    // Palavras-chave
    T_KW_ELSE,
    T_KW_IF,
    T_KW_INT,
    T_KW_RETURN,
    T_KW_VOID,
    T_KW_WHILE,

    // Símbolos Especiais (Operadores e Separadores)
    T_OP_MAIS,      // +
    T_OP_MENOS,     // -
    T_OP_MULT,      // *
    T_OP_DIV,       // /
    T_OP_IGUAL,     // =
    T_OP_IGUALIGUAL,// ==
    T_OP_DIF,       // !=
    T_OP_MENOR,     // <
    T_OP_MENORIGUAL,// <=
    T_OP_MAIOR,     // >
    T_OP_MAIORIGUAL,// >=
    T_SEP_LPAREN,   // (
    T_SEP_RPAREN,   // )
    T_SEP_LCHAVE,   // {
    T_SEP_RCHAVE,   // }
    T_SEP_LCOL,     // [
    T_SEP_RCOL,     // ]
    T_SEP_VIRGULA,  // ,
    T_SEP_PVIRGULA  // ;

} TokenType;

// Estrutura para o Token 
typedef struct {
    TokenType type;
    char lexeme[256];
} Token;

FILE *inputFile;
int lineno = 1; 

// Função auxiliar para converter o Tipo de Token em string
const char* tokenTypeToString(TokenType type) {
    switch (type) {
        case T_EOF: return "EOF";
        case T_ERROR: return "ERROR";
        case T_ID: return "ID";
        case T_NUM: return "NUM";
        // Palavras-chave
        case T_KW_ELSE: return "PALAVRA_CHAVE (else)";
        case T_KW_IF: return "PALAVRA_CHAVE (if)";
        case T_KW_INT: return "PALAVRA_CHAVE (int)";
        case T_KW_RETURN: return "PALAVRA_CHAVE (return)";
        case T_KW_VOID: return "PALAVRA_CHAVE (void)";
        case T_KW_WHILE: return "PALAVRA_CHAVE (while)";
        // Operadores
        case T_OP_MAIS: return "OPERADOR (MAIS)";
        case T_OP_MENOS: return "OPERADOR (MENOS)";
        case T_OP_MULT: return "OPERADOR (MULT)";
        case T_OP_DIV: return "OPERADOR (DIV)";
        case T_OP_IGUAL: return "OPERADOR (IGUAL)";
        case T_OP_IGUALIGUAL: return "OPERADOR (IGUALIGUAL)";
        case T_OP_DIF: return "OPERADOR (DIF)";
        case T_OP_MENOR: return "OPERADOR (MENOR)";
        case T_OP_MENORIGUAL: return "OPERADOR (MENORIGUAL)";
        case T_OP_MAIOR: return "OPERADOR (MAIOR)";
        case T_OP_MAIORIGUAL: return "OPERADOR (MAIORIGUAL)";
        // Separadores
        case T_SEP_LPAREN: return "SEPARADOR (LPAREN)";
        case T_SEP_RPAREN: return "SEPARADOR (RPAREN)";
        case T_SEP_LCHAVE: return "SEPARADOR (LCHAVE)";
        case T_SEP_RCHAVE: return "SEPARADOR (RCHAVE)";
        case T_SEP_LCOL: return "SEPARADOR (LCOL)";
        case T_SEP_RCOL: return "SEPARADOR (RCOL)";
        case T_SEP_VIRGULA: return "SEPARADOR (VIRGULA)";
        case T_SEP_PVIRGULA: return "SEPARADOR (PVIRGULA)";
        default: return "DESCONHECIDO";
    }
}


// Função prinicipal do scanner
Token getToken() {
    Token token;
    int lexemeIndex = 0;
    int c;

    token.lexeme[0] = '\0';

    // pula espaços em branco
    while (isspace(c = fgetc(inputFile))) {
        if (c == '\n') {
            lineno++;
        }
    }

    // logica de comentarios e divisao
    if (c == '/') {
        int next_c = fgetc(inputFile);
        
        if (next_c == '*') { 
            c = fgetc(inputFile);
            while (c != EOF) {
                if (c == '*') {
                    int next_next_c = fgetc(inputFile);
                    if (next_next_c == '/') {
                        break; 
                    }
                    ungetc(next_next_c, inputFile); // Devolve o caractere
                }
                if (c == '\n') lineno++; 
                c = fgetc(inputFile);
            }
            
            if (c == EOF) {
                token.type = T_ERROR;
                strcpy(token.lexeme, "Comentario nao terminado");
                return token;
            }
            
            return getToken(); // Chama recursivamente para partir para o próximo token

        } else {
            // É apenas um operador de divisão!!
            ungetc(next_c, inputFile); // Devolve o caractere lido a mais
            token.type = T_OP_DIV;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            return token;
        }
    }

    // Fim de Arquivo (EOF)
    if (c == EOF) {
        token.type = T_EOF;
        strcpy(token.lexeme, "EOF");
        return token;
    }

    // Identificadores (ID) e Palavras-Chaves
    if (isalpha(c)) { // checa se c é uma 'letra'
        token.lexeme[lexemeIndex++] = c;
        
        // enquanto for 'letra' 
        while (isalpha(c = fgetc(inputFile))) { 
            token.lexeme[lexemeIndex++] = c;
        }
        ungetc(c, inputFile); // Devolve o último caractere lido (que não é letra)
        token.lexeme[lexemeIndex] = '\0';

        // Verifica se é uma palavra-chave 
        if (strcmp(token.lexeme, "else") == 0) token.type = T_KW_ELSE;
        else if (strcmp(token.lexeme, "if") == 0) token.type = T_KW_IF;
        else if (strcmp(token.lexeme, "int") == 0) token.type = T_KW_INT;
        else if (strcmp(token.lexeme, "return") == 0) token.type = T_KW_RETURN;
        else if (strcmp(token.lexeme, "void") == 0) token.type = T_KW_VOID;
        else if (strcmp(token.lexeme, "while") == 0) token.type = T_KW_WHILE;
        else token.type = T_ID; // Se não for palavra-chave, é ID 

        return token;
    }

    // Números (NUM)
    if (isdigit(c)) { // checa se c é um 'dígito'
        token.lexeme[lexemeIndex++] = c;
        // enquanto for 'dígito'
        while (isdigit(c = fgetc(inputFile))) {
            token.lexeme[lexemeIndex++] = c;
        }
        ungetc(c, inputFile); // Devolve o último caractere (que não é dígito)
        token.lexeme[lexemeIndex] = '\0';
        token.type = T_NUM;
        return token;
    }

    // Operadores (com "lookahead" para ==, !=, <=, >=) 
    token.lexeme[lexemeIndex++] = c;
    token.lexeme[lexemeIndex] = '\0';

    if (c == '=') {
        int next_c = fgetc(inputFile);
        if (next_c == '=') {
            token.lexeme[lexemeIndex++] = next_c;
            token.lexeme[lexemeIndex] = '\0';
            token.type = T_OP_IGUALIGUAL;
        } else {
            ungetc(next_c, inputFile);
            token.type = T_OP_IGUAL;
        }
        return token;
    }
    
    if (c == '!') {
        int next_c = fgetc(inputFile);
        if (next_c == '=') {
            token.lexeme[lexemeIndex++] = next_c;
            token.lexeme[lexemeIndex] = '\0';
            token.type = T_OP_DIF;
        } else {
            ungetc(next_c, inputFile);
            token.type = T_ERROR; // '!' sozinho não é um símbolo C-
            strcpy(token.lexeme, "Caractere '!' inesperado");
        }
        return token;
    }

    if (c == '<') {
        int next_c = fgetc(inputFile);
        if (next_c == '=') {
            token.lexeme[lexemeIndex++] = next_c;
            token.lexeme[lexemeIndex] = '\0';
            token.type = T_OP_MENORIGUAL;
        } else {
            ungetc(next_c, inputFile);
            token.type = T_OP_MENOR;
        }
        return token;
    }
    
    if (c == '>') {
        int next_c = fgetc(inputFile);
        if (next_c == '=') {
            token.lexeme[lexemeIndex++] = next_c;
            token.lexeme[lexemeIndex] = '\0';
            token.type = T_OP_MAIORIGUAL;
        } else {
            ungetc(next_c, inputFile);
            token.type = T_OP_MAIOR;
        }
        return token;
    }

    // Operadores e Separadores Simples (um caractere) 
    switch (c) {
        case '+': token.type = T_OP_MAIS; break;
        case '-': token.type = T_OP_MENOS; break;
        case '*': token.type = T_OP_MULT; break;
        case '(': token.type = T_SEP_LPAREN; break;
        case ')': token.type = T_SEP_RPAREN; break;
        case '{': token.type = T_SEP_LCHAVE; break;
        case '}': token.type = T_SEP_RCHAVE; break;
        case '[': token.type = T_SEP_LCOL; break;
        case ']': token.type = T_SEP_RCOL; break;
        case ',': token.type = T_SEP_VIRGULA; break;
        case ';': token.type = T_SEP_PVIRGULA; break;
        default:
            // Caractere desconhecido
            token.type = T_ERROR;
            sprintf(token.lexeme, "Caractere '%c' desconhecido", c);
            break;
    }

    return token;
}


// Função principal
int main(int argc, char *argv[]) {
    
    // Verifica se o nome do arquivo foi passado como argumento
    // caso contrário, exibe mensagem de erro, já que sem arquivo não tem varredura
    if (argc < 2) {
        fprintf(stderr, "Erro: Forneca um arquivo de entrada.\n");
        fprintf(stderr, "Uso: %s <arquivo.c->\n", argv[0]);
        return 1;
    }

    // Tenta abrir o arquivo
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s'.\n", argv[1]);
        return 1;
    }

    printf("Iniciando varredura do arquivo: %s\n", argv[1]);
    printf("---------------------------------------------\n");
    printf("[Tipo: %-25s] [Lexema (Cadeia)]\n", "Marca");
    printf("---------------------------------------------\n");


    Token currentToken;
    do {
        // Pega o próximo token
        currentToken = getToken();
        
        // Exibe na tela, conforme solicitado
        printf("[Tipo: %-25s] [Lexema: \"%s\"]\n", 
               tokenTypeToString(currentToken.type), 
               currentToken.lexeme);
        
        if (currentToken.type == T_ERROR) {
             fprintf(stderr, "Erro lexico na linha %d: %s\n", lineno, currentToken.lexeme);
        }

    } while (currentToken.type != T_EOF); // Loop até acabar o arquivo

    printf("---------------------------------------------\n");
    printf("Varredura concluida.\n");

    // Fecha o arquivo
    fclose(inputFile);
    return 0;
}