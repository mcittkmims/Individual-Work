#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//#include "lexer.h"

struct variables{
    char name[50];
    char vartype[20];
};

struct Token {
    char name[50];
    char type[20];
    long int valueint;
    float valuefloat;
    char vartype[20];
};


// Define the Node structure
typedef struct Node {
    struct Token token;
    struct Node* next;
} Tokens;

// Function to create a new node with a given token
struct Node* createNode(struct Token token) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode != NULL) {
        newNode->token = token;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to append a node to the linked list
void appendNode(struct Node** head, struct Token token) {
    struct Node* newNode = createNode(token);
    if (newNode == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed.\n");
        return;
    }

    if (*head == NULL) {
        // If the list is empty, set the new node as the head
        *head = newNode;
    } else {
        // Traverse the list to find the last node and append the new node
        struct Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to print the linked list of tokens
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("Name: %s, Type: %s, ValueInt: %d, ValueFloat: %f, vartype: %s\n",current->token.name, current->token.type, current->token.valueint, current->token.valuefloat,current->token.vartype);
        current = current->next;
    }
}

// Function to free the memory allocated for the linked list
void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}
int isOnlyLetters(const char *str) {
    while (*str) {
        if (!isalpha(*str)) {
            return 0; // Not a letter
        }
        str++;
    }
    return 1; // All characters are letters
}

int isNumber(const char *str) {
    // Check if the string is empty
    if (*str == '\0') {
        return 0; // Empty string is not a valid number
    }

    // Check if the first character is a minus sign
    if (*str == '-') {
        str++; // Move to the next character
    }

    // Check the remaining characters
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Not a digit
        }
        str++;
    }
    return 1; // All characters are digits
}


int isValidFloat(const char *str) {
    int dotCount = 0;

    // Check if the string is empty or starts with a dot
    if (*str == '\0' || *str == '.') {
        return 0; // Empty string or starting with a dot is not a valid float
    }

    // Check if the first character is a minus sign
    if (*str == '-') {
        str++; // Move to the next character
    }

    while (*str) {
        if (!isdigit(*str)) {
            // Check if the character is a dot
            if (*str == '.') {
                dotCount++;


                if (dotCount > 1 || str[1] == '\0') {
                    return 0;
                }
            } else {
                return 0;
            }
        }
        str++;
    }


    return (dotCount == 1);
}


struct Node* tokenlist(Tokens** head,int &k){
    char** tokenarray;
    int n=0,i=0;
    tokenarray=tokenize(n);
    tokenarray=(char**)realloc(tokenarray,(n+2)*sizeof(char*));
    tokenarray[n]=(char*)malloc(1*sizeof(char));
    tokenarray[n+1]=(char*)malloc(1*sizeof(char));
    tokenarray[n]="";
    tokenarray[n+1]="";
    
    for (i=0;i<n;i++){
        if (strcmp(tokenarray[i],"var")==0){
            struct Token token ={"var","var",0,0,'-'};
            appendNode(head, token);
            
        }
        else if (strcmp(tokenarray[i],":")==0){
            struct Token token ={":","assigningtype",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"real")==0){
            struct Token token ={"real","identifier",0,0,'-'};
            appendNode(head, token);
        }
        else if( strcmp(tokenarray[i],"integer")==0){
            struct Token token ={"integer","identifier",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"begin")==0){
            struct Token token ={"begin","begin",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"end")==0){
            struct Token token ={"end","end",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],":=")==0){
            struct Token token ={":=","attribution",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"<")==0){
            struct Token token ={"<","<",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],">")==0){
            struct Token token ={">",">",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"=")==0){
            struct Token token ={"=","=",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"!=")==0){
            struct Token token ={"!=","!=",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],">=")==0){
            struct Token token ={">=",">=",0,0,'-'};
            appendNode(head, token);

        }
         else if (strcmp(tokenarray[i],"<=")==0){
            struct Token token ={"<=","<=",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"if")==0){
            struct Token token ={"if","if",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"while")==0){
            struct Token token ={"while","while",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"print")==0){
            struct Token token ={"print","print",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"sum")==0){
            struct Token token ={"sum","+",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"subtr")==0){
            struct Token token ={"subtr","-",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"mult")==0){
            struct Token token ={"mult","*",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"div")==0){
            struct Token token ={"div","/",0,0,'-'};
            appendNode(head, token);
        }
        else if (strcmp(tokenarray[i],"\n")==0){
            struct Token token ={"newline","newline",0,0,'-'};
            k++;
            appendNode(head, token);
        }
        else if (isOnlyLetters(tokenarray[i])&&strcmp(tokenarray[i+1],":")==0 &&strcmp(tokenarray[i+2],"integer")==0){
            struct Token token;// ={tokenarray[i],"number",atoi(tokenarray[i]),atoi(tokenarray[i]),"integer"  };
            snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
            snprintf(token.type, sizeof(token.type), "%s", "vardeclaration");
            token.valueint= 0;
            token.valuefloat= 0;
            snprintf(token.vartype, sizeof(token.vartype), "%s", "integer");

            appendNode(head, token);
        }
         else if (isOnlyLetters(tokenarray[i])&&strcmp(tokenarray[i+1],":")==0 &&strcmp(tokenarray[i+2],"real")==0){
            struct Token token;// ={tokenarray[i],"number",atoi(tokenarray[i]),atoi(tokenarray[i]),"integer"  };
            snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
            snprintf(token.type, sizeof(token.type), "%s", "vardeclaration");
            token.valueint= 0;
            token.valuefloat= 0;
            snprintf(token.vartype, sizeof(token.vartype), "%s", "real");

            appendNode(head, token);
        // }
        //  else if (isOnlyLetters(tokenarray[i])){
        //     struct Token token;// ={tokenarray[i],"number",atoi(tokenarray[i]),atoi(tokenarray[i]),"integer"  };
        //     snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
        //     snprintf(token.type, sizeof(token.type), "%s", "variable");
        //     token.valueint= 0;
        //     token.valuefloat= 0;
        //     snprintf(token.vartype, sizeof(token.vartype), "%s", "-");

        //     appendNode(head, token);
        }
        else if (isNumber(tokenarray[i])&&(strcmp(tokenarray[i-1],":=")==0||strcmp(tokenarray[i-1],"sum")==0||strcmp(tokenarray[i-1],"div")==0||strcmp(tokenarray[i-1],"subtr")==0||strcmp(tokenarray[i-1],"mult")==0||strcmp(tokenarray[i-1],"print")==0||strcmp(tokenarray[i-1],"if")==0||strcmp(tokenarray[i-1],"while")==0||strcmp(tokenarray[i-2],"sum")==0||strcmp(tokenarray[i-2],"div")==0||strcmp(tokenarray[i-2],"subtr")==0||strcmp(tokenarray[i-2],"mult")==0||strcmp(tokenarray[i-1],"<")==0||strcmp(tokenarray[i-1],">")==0||strcmp(tokenarray[i-1],"=")==0||strcmp(tokenarray[i-1],">=")==0||strcmp(tokenarray[i-1],"<=")==0)){
            struct Token token;// ={tokenarray[i],"number",atoi(tokenarray[i]),atoi(tokenarray[i]),"integer"  };
            snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
            snprintf(token.type, sizeof(token.type), "%s", "number");
            char *endptr;
            token.valueint= strtol(tokenarray[i],&endptr,10);
            token.valuefloat= atoi(tokenarray[i]);
            snprintf(token.vartype, sizeof(token.vartype), "%s", "integer");

            appendNode(head, token);
        }
        else if (isValidFloat(tokenarray[i])&&(strcmp(tokenarray[i-1],":=")==0||strcmp(tokenarray[i-1],"sum")==0||strcmp(tokenarray[i-1],"div")==0||strcmp(tokenarray[i-1],"subtr")==0||strcmp(tokenarray[i-1],"mult")==0||strcmp(tokenarray[i-1],"print")==0||strcmp(tokenarray[i-2],"sum")==0||strcmp(tokenarray[i-2],"div")==0||strcmp(tokenarray[i-2],"subtr")==0||strcmp(tokenarray[i-2],"mult")==0||strcmp(tokenarray[i-1],"<")==0||strcmp(tokenarray[i-1],">")==0||strcmp(tokenarray[i-1],"=")==0||strcmp(tokenarray[i-1],">=")==0||strcmp(tokenarray[i-1],"<=")==0||strcmp(tokenarray[i-1],"if")==0||strcmp(tokenarray[i-1],"while")==0)){
        
            struct Token token;// ={tokenarray[i],"number",0,atof(tokenarray[i]),"real"};
            snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
            snprintf(token.type, sizeof(token.type), "%s", "number");
            token.valueint= 0;
            token.valuefloat= atof(tokenarray[i]);
            snprintf(token.vartype, sizeof(token.vartype), "%s", "real");

            appendNode(head, token);
        }
        else if (isOnlyLetters(tokenarray[i])&&(strcmp(tokenarray[i+1],":=")==0||strcmp(tokenarray[i-1],":=")==0||strcmp(tokenarray[i-1],"sum")==0||strcmp(tokenarray[i-1],"div")==0||strcmp(tokenarray[i-1],"subtr")==0||strcmp(tokenarray[i-1],"mult")==0||strcmp(tokenarray[i-1],"print")==0||strcmp(tokenarray[i-2],"sum")==0||strcmp(tokenarray[i-2],"div")==0||strcmp(tokenarray[i-2],"subtr")==0||strcmp(tokenarray[i-2],"mult")==0||strcmp(tokenarray[i-1],"<")==0||strcmp(tokenarray[i-1],">")==0||strcmp(tokenarray[i-1],"=")==0||strcmp(tokenarray[i-1],">=")==0||strcmp(tokenarray[i-1],"<=")==0||strcmp(tokenarray[i-1],"if")==0||strcmp(tokenarray[i-1],"while")==0)){
            struct Token token;// ={tokenarray[i],"number",0,atof(tokenarray[i]),"real"};
            snprintf(token.name, sizeof(token.name), "%s", tokenarray[i]);
            snprintf(token.type, sizeof(token.type), "%s", "variable");
            token.valueint= 0;
            token.valuefloat= 0;
            snprintf(token.vartype, sizeof(token.vartype), "%s", "-");

            appendNode(head, token);
        }
        else{
            printf("Line %d: Undefined token '<%s>'!",k+1,tokenarray[i]);
            getch();
            exit(1);

        }
    }

    return *head;

}

// int main(){
//     struct Node* head=NULL;
//     tokenlist(&head);
//     printList(head);
//     getch();
//     freeList(head);
//     return 0;
// }