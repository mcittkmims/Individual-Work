#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

 
 


typedef struct Var{
    char name[50];
    char type[20];
    long int intvalue;
    float floatvalue;
}Var;

typedef struct Variables {
    Var variable;
    Variables* next;
}Variables;

Var* searchVariable(Variables* head, const char* variableName) {
    Variables* current = head;

    // Traverse the linked list
    while (current != NULL) {
        // Check if the current variable has the desired name
        if (strcmp(current->variable.name, variableName) == 0) {
            // Return the pointer to the current variable
            return &(current->variable);
        }

        // Move to the next variable
        current = current->next;
    }

    // If the variable is not found, return NULL
    return NULL;
}


int isFloatInteger(float number) {
    double integralPart;
    double fractionalPart = modf(number, &integralPart);

    // If the fractional part is very close to zero, consider it as an integer
    return (fractionalPart < 1e-10 && fractionalPart > -1e-10);
}



Variables* createVariable(Var variable) {
    Variables* newNode = (Variables*)malloc(sizeof(Variables));
    if (newNode != NULL) {
        newNode->variable = variable;
        newNode->next = NULL;
    }
    return newNode;
}

// Function to append a node to the linked list
void appendVariable(Variables** head, Var variable) {
    Variables* newNode = createVariable(variable);
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
        Variables* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}





void printVariables(Variables* head) {
    Variables* current = head;
    while (current != NULL) {
        printf("Name: %s, Type: %s, ValueInt: %d, ValueFloat: %f\n",current->variable.name, current->variable.type, current->variable.intvalue, current->variable.floatvalue);
        current = current->next;
    }
}

void VariableList(Variables **head,treenode* vartree){
    // treenode *vartree=NULL;
    // treenode *begintree=NULL;
    // The_Tree(&vartree,&begintree);
    treenode *current=vartree;
    while (current!=NULL){
        if (strcmp(current->token.type,"vardeclaration")==0){

            Var variable;
            snprintf(variable.name, sizeof(variable.name), "%s", current->token.name);
            snprintf(variable.type, sizeof(variable.type), "%s", current->token.vartype);
            variable.intvalue= 0;
            variable.floatvalue= 0;

            appendVariable(head, variable);
        }
        current=current->right;

        
    }

return;
}

void RunProgram(Variables* head,treenode *root){
    treenode *current=root;
    treenode *currentline=current;
    current=current->right->right;
    
    while(1){
        if (strcmp(current->token.type,"variable")==0){
            Var* result = searchVariable(head,current->token.name);
            if (result!=NULL){strcpy(current->token.vartype,result->type);}
        if (strcmp(current->token.vartype,"integer")==0){
            // Var* result = searchVariable(head,current->token.name);
            // if (result!=NULL){strcpy(current->token.vartype,result->type);}

            currentline=current->left;
            Var* parameter1 = searchVariable(head,currentline->right->token.name);
            if (parameter1!=NULL){strcpy(currentline->right->token.vartype,parameter1->type);currentline->right->token.valueint=parameter1->intvalue;currentline->right->token.valuefloat=parameter1->floatvalue;}
            if (strcmp(currentline->token.type,"attribution")==0){
                currentline=currentline->right;
                if (strcmp(currentline->token.vartype,"integer")==0){
                    result->intvalue=currentline->token.valueint;
                }else if (strcmp(currentline->token.type,"+")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->intvalue=(currentline->left->token.valueint)+(currentline->right->token.valueint);
                    }else{printf("Invalid value to data type!");getch();exit(1);}
                }else if (strcmp(currentline->token.type,"-")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->intvalue=(currentline->left->token.valueint)-(currentline->right->token.valueint);
                    }else{printf("Invalid value to data type!");getch();exit(1);}
                }else if (strcmp(currentline->token.type,"*")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        // if (isFloatInteger((currentline->left->token.valueint)*(currentline->right->token.valueint)))
                        result->intvalue=(currentline->left->token.valueint)*(currentline->right->token.valueint);
                    }else{printf("Invalid value to data type!");getch();exit(1);}
                }else if (strcmp(currentline->token.type,"/")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0&&currentline->right->token.valueint!=0){
                        if (isFloatInteger((float)(currentline->left->token.valueint)/(currentline->right->token.valueint))){
                        result->intvalue=(currentline->left->token.valueint)/(currentline->right->token.valueint);
                        }else{printf("The result is float! ");getch();exit(1);}
                    }else{printf("Invalid value to data type or can not divide by 0");getch();exit(1);}
                }else {printf("Invalid value to data type!");getch();exit(1);}
            }
        }else if (strcmp(current->token.vartype,"real")==0){
            // Var* result = searchVariable(head,current->token.name);
            // if (result!=NULL){strcpy(current->token.vartype,result->type);}
            currentline=current->left;
            Var* parameter1 = searchVariable(head,currentline->right->token.name);
            if (parameter1!=NULL){strcpy(currentline->right->token.vartype,parameter1->type);currentline->right->token.valueint=parameter1->intvalue;currentline->right->token.valuefloat=parameter1->floatvalue;}
            if (strcmp(currentline->token.type,"attribution")==0){
                currentline=currentline->right;
                if (strcmp(currentline->token.vartype,"real")==0){
                    result->floatvalue=currentline->token.valuefloat;
                }else if (strcmp(currentline->token.vartype,"integer")==0){
                    result->floatvalue=currentline->token.valueint;
                }else if (strcmp(currentline->token.type,"+")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valueint)+(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)+(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)+(currentline->right->token.valuefloat);
                    }else if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valueint)+(currentline->right->token.valuefloat);
                    }
                }else if (strcmp(currentline->token.type,"-")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valueint)-(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)-(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)-(currentline->right->token.valuefloat);
                    }else if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valueint)-(currentline->right->token.valuefloat);
                    }
                }else if (strcmp(currentline->token.type,"*")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valueint)*(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)*(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valuefloat)*(currentline->right->token.valuefloat);
                    }else if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                        result->floatvalue=(currentline->left->token.valueint)*(currentline->right->token.valuefloat);
                    }
                }else if (strcmp(currentline->token.type,"/")==0){
                    Var* parameter2 = searchVariable(head,currentline->left->token.name);
                    Var* parameter3 = searchVariable(head,currentline->right->token.name);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                   
                    if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0&&currentline->right->token.valueint!=0){
                        result->floatvalue=(float)(currentline->left->token.valueint)/(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"integer")==0&&currentline->right->token.valueint!=0){
                        result->floatvalue=(currentline->left->token.valuefloat)/(currentline->right->token.valueint);
                    }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0&&currentline->right->token.valuefloat!=0){
                        result->floatvalue=(currentline->left->token.valuefloat)/(currentline->right->token.valuefloat);
                    }else if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"real")==0&&currentline->right->token.valuefloat!=0){
                        result->floatvalue=(currentline->left->token.valueint)/(currentline->right->token.valuefloat);
                    }else {printf("Can not divide by 0");getch();exit(1);}
                }
            }
        }
        }else if(strcmp(current->token.type,"if")==0){
            currentline=current->left;
            Var* parameter2 = searchVariable(head,currentline->left->token.name);
            Var* parameter3 = searchVariable(head,currentline->right->token.name);
            if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
            if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
            if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
            if (strcmp(currentline->token.type,">")==0){
                if ((currentline->left->token.valueint)>(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"<")==0){
                if ((currentline->left->token.valueint)<(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"=")==0){
                if ((currentline->left->token.valueint)==(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"<=")==0){
                if ((currentline->left->token.valueint)<=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,">=")==0){
                if ((currentline->left->token.valueint)>=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"!=")==0){
                if ((currentline->left->token.valueint)>=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }
            }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                if (strcmp(currentline->token.type,">")==0){
                if ((currentline->left->token.valuefloat)>(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"<")==0){
                if ((currentline->left->token.valuefloat)<(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"=")==0){
                if ((currentline->left->token.valuefloat)==(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"<=")==0){
                if ((currentline->left->token.valuefloat)<=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,">=")==0){
                if ((currentline->left->token.valuefloat)>=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }else if (strcmp(currentline->token.type,"!=")==0){
                if ((currentline->left->token.valuefloat)>=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                }
                
            }

            }else {printf("Comparasion can be made only between the same data type!");getch();exit(1);}
        }else if(strcmp(current->token.type,"while")==0){
            currentline=current->left;
            Var* parameter2 = searchVariable(head,currentline->left->token.name);
            Var* parameter3 = searchVariable(head,currentline->right->token.name);
            if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
            if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
            if (strcmp(currentline->left->token.vartype,"integer")==0&&strcmp(currentline->right->token.vartype,"integer")==0){
            if (strcmp(currentline->token.type,">")==0){
                while ((currentline->left->token.valueint)>(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"<")==0){
                while ((currentline->left->token.valueint)<(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"=")==0){
                while ((currentline->left->token.valueint)==(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"<=")==0){
                while ((currentline->left->token.valueint)<=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,">=")==0){
                while ((currentline->left->token.valueint)>=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"!=")==0){
                while ((currentline->left->token.valueint)>=(currentline->right->token.valueint)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
           
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }
            }else if (strcmp(currentline->left->token.vartype,"real")==0&&strcmp(currentline->right->token.vartype,"real")==0){
                if (strcmp(currentline->token.type,">")==0){
                while ((currentline->left->token.valuefloat)>(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                   
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"<")==0){
                while ((currentline->left->token.valuefloat)<(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
             
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"=")==0){
                while ((currentline->left->token.valuefloat)==(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"<=")==0){
                while ((currentline->left->token.valuefloat)<=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,">=")==0){
                while ((currentline->left->token.valuefloat)>=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }else if (strcmp(currentline->token.type,"!=")==0){
                while ((currentline->left->token.valuefloat)>=(currentline->right->token.valuefloat)){
                    treenode *current1=current;
                    RunProgram(head,current1->right->left);
                    if (parameter2!=NULL){strcpy(currentline->left->token.vartype,parameter2->type);currentline->left->token.valueint=parameter2->intvalue;currentline->left->token.valuefloat=parameter2->floatvalue;}
                    if (parameter3!=NULL){strcpy(currentline->right->token.vartype,parameter3->type);currentline->right->token.valueint=parameter3->intvalue;currentline->right->token.valuefloat=parameter3->floatvalue;}
                    
                }
                
            }

            }else {printf("Comparasion can be made only between the same data type!");getch();exit(1);}
        }else if (strcmp(current->token.type,"print")==0){
            currentline=current->left;
            Var* parameter1 = searchVariable(head,currentline->token.name);
            if (parameter1!=NULL){strcpy(currentline->token.vartype,parameter1->type);currentline->token.valueint=parameter1->intvalue;currentline->token.valuefloat=parameter1->floatvalue;}


            if (strcmp(currentline->token.vartype,"integer")==0){
                printf("\n%d\n",currentline->token.valueint);
            }else if (strcmp(currentline->token.vartype,"real")==0){
                printf("\n%f\n",currentline->token.valuefloat);
            }
        }else if (strcmp(current->token.type,"end")==0){
            return;
        }
        current=current->right->right;
    }
    

}

void Interpreter(){
    treenode *vartree=NULL;
    treenode *begintree=NULL;
    The_Tree(&vartree,&begintree);
    Variables *head=NULL;
    VariableList(&head,vartree);
    RunProgram(head,begintree);

    return;
}

// int main(){ 
//     // Variables *head=NULL;
//     // VariableList(&head);
//     Interpreter();
//     getch();
//     return 0;
// }










