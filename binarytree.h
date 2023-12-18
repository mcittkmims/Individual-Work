#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>


typedef struct treenode{
    struct Token token;
    struct treenode *left;
    struct treenode *right;

} treenode;

treenode *createnode(struct Token token){
    treenode* result =(treenode*)malloc(sizeof(treenode));
    if (result !=NULL){
        result->left=NULL;
        result->right=NULL;
        result->token=token;
    }
    return result;
}

void printtabs(int numtabs){
    for (int i=0; i<numtabs; i++){
        printf("\t");
    }
}

void printtree_rec(treenode *root, int level){
    if (root==NULL){
        printtabs(level);
        printf("---<empty>---\n");
        return;
    }
    printtabs(level);
    printf("%s\n",root->token.type);

    printtabs(level);
    printf("left\n");
    
    printtree_rec(root->left,level+1);
    printtabs(level);
    printf("right\n");
    
    printtree_rec(root->right,level+1);
    
    printtabs(level);
    printf("done\n");

}

void printtree(treenode*root){
    printtree_rec(root,0);
}

int searchVariable(struct Node* head, char* key){
    struct Node *temp=head;
    int k=0;
    while(temp!= NULL&&strcmp(temp->token.type,"begin")!=0){ //||strcmp(temp->token.type,"begin")==0
        if(strcmp(temp->token.name,key)==0 && strcmp(temp->token.type,"vardeclaration")==0){
            k++;
        if (k==2){break;}
        }
    temp=temp->next;
    }

    if (k==1){return 1;}
    return-1;
}

void insertToken(treenode** root, treenode* parent, struct Token token, int insertOnLeft) {
    treenode* newNode = createnode(token);
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    if (*root == NULL) {
        *root = newNode;
    } else {
        if (insertOnLeft) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
}


struct Node* createTreeVar(treenode** root,struct Node* head,int &k){
    treenode *currenttree=NULL;
    treenode *currentline=NULL;
    struct Node* current=head;
    if (current==NULL){printf("Line %d: Missing var",k+1);getch();exit(1);}
    if (strcmp(current->token.type,"var")==0){
        (*root) =createnode(current->token);
    } else{printf("Line %d:Program should start with 'var'",k+1);getch();exit(1);};
    currenttree=(*root);

    current=current->next;
    if(current==NULL){printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}
    else if (strcmp(current->token.type,"newline")==0){
        currenttree->right=createnode(current->token);
        currenttree=currenttree->right;
        k++;
    } 
    else {printf("Line %d: Missing 'newline'",k+1);getch();exit(1);};
    if(current->next==NULL){printf("Line %d: Missing 'begin'",k+1);getch();exit(1);}
    while (strcmp(current->next->token.type,"begin")!=0){
        while(current->next!=NULL&&strcmp(current->next->token.type,"newline")==0){
                current=current->next;
                k++;
            }
        if(current==NULL){printf("Line %d: Missing 'begin'",k+1);getch();exit(1);}
        if (current->next==NULL){printf("Line %d: Missing 'begin'",k+1);getch();exit(1);}
        current=current->next;
        if (strcmp(current->token.type,"vardeclaration")==0&&searchVariable(head,current->token.name)==1){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            currentline=currenttree;
        } else{printf("Line %d: Incorrect variable declaration!",k+1);getch();exit(1);};    
        current=current->next;
        if (strcmp(current->token.type,"assigningtype")==0){
            currenttree->left=createnode(current->token);
            currenttree=currenttree->left;
        } else{printf("Line %d: Missing ':'",k+1);getch();exit(1);};  
        current=current->next;
        if (strcmp(current->token.type,"identifier")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
        } else{printf("Line %d: Missing 'identifier'",k+1);getch();exit(1);};
        current=current->next;
        if (strcmp(current->token.type,"newline")==0){
            currentline->right=createnode(current->token);
            currenttree=currentline->right;
            k++;
        } else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);};
        while(current->next!=NULL&&strcmp(current->next->token.type,"newline")==0){
                current=current->next;
                k++;
            }    
        if (current->next==NULL){printf("Line %d: Missing 'begin'",k+1);getch();exit(1);}
        

        //if (current->next==NULL){printf("Missing 'begin'");getch();exit(1);}
        //current=current->next;


    }
    return current->next;

}

struct Node* RecursiveTree(treenode** root,Tokens* current,Tokens*beginning,int &k){

  
    treenode *currenttree=*root;
    treenode *operat=NULL;
    treenode *currentline=NULL;
    struct Node* variable=current;
    while(strcmp(current->token.type,"newline")==0&&current!=NULL){
                current=current->next;
                k++;
            }
    
    if (strcmp(current->token.type,"begin")==0){
        if (currenttree==NULL){

        currenttree=createnode(current->token);*root=currenttree;}
        else{

            currenttree->left=createnode(current->token);
            currenttree=currenttree->left;
        }
        current=current->next;
        if (current!=NULL &&strcmp(current->token.type,"newline")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            current=current->next;
            k++;
        } else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}; 
         //else{printf("Missing 'begin'");getch();exit(1);}
        while (current!=NULL){

        if (strcmp(current->token.type,"newline")==0){
            current=current->next;
            k++;
        }
        else if (strcmp(current->token.type,"variable")==0 && searchVariable(beginning,current->token.name)==1){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            currentline=currenttree;
            current=current->next;
            if(strcmp(current->token.type,"attribution")==0){
                currenttree->left=createnode(current->token);
                currenttree=currenttree->left;
                current=current->next;   
            } else{printf("Line %d: Missing ':='",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"+")==0||strcmp(current->token.type,"-")==0||strcmp(current->token.type,"/")==0||strcmp(current->token.type,"*")==0){
                currenttree->right=createnode(current->token);
                currenttree=currenttree->right;
                current=current->next;
                operat=currenttree;
            
            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                currenttree->left=createnode(current->token);
                currenttree=currenttree->left;
                current=current->next;
            }else{printf("Line %d: Incorrect existing variable or number!",k+1);getch();exit(1);}

            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                operat->right=createnode(current->token);
                currenttree=operat->right;
                current=current->next;
            }else{printf("Line %d: Incorrect existing variable or number !",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"newline")==0){
                currentline->right=createnode(current->token);
                currenttree=currentline->right;
                current=current->next;
                k++;
            }else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}
            }else if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                currenttree->right=createnode(current->token);
                currenttree=currenttree->right;
                current=current->next;
                if(strcmp(current->token.type,"newline")==0){
                    currentline->right=createnode(current->token);
                    currenttree=currentline->right;
                    current=current->next;
                    k++;
                }else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}
            }
            else{printf("Line %d: Missing ':=' or parameter!",k+1);getch();exit(1);}
        
        }else if (strcmp(current->token.type,"print")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            currentline=currenttree;
            current=current->next;
            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                currenttree->left=createnode(current->token);
                currenttree=currenttree->left;
                current=current->next;
            }else{printf("Line %d: Incorrect existing 'variable or number'",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"newline")==0){
                currentline->right=createnode(current->token);
                currenttree=currentline->right;
                current=current->next;
                k++;
            }else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}

        }else if (strcmp(current->token.type,"if")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            currentline=currenttree;
            current=current->next;
            if(strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0 && searchVariable(beginning,current->token.name)==1)){
                variable=current;
                current=current->next;
            }else{printf("Line %d: Missing 'number' or 'variable':",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"<")==0||strcmp(current->token.type,"<=")==0||strcmp(current->token.type,">")==0||strcmp(current->token.type,">=")==0||strcmp(current->token.type,"=")==0||strcmp(current->token.type,"!=")==0){
                currenttree->left=createnode(current->token);
                currenttree=currenttree->left;
                operat=currenttree;
                current=current->next;
                currenttree->left=createnode(variable->token);
            }else{printf("Line %d: Missing 'condition'",k+1);getch();exit(1);}
            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                operat->right=createnode(current->token);
                current=current->next;
                currenttree=operat->right;
            }else{printf("Line %d: Missing 'number' or 'variable'",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"newline")==0){
                currentline->right=createnode(current->token);
                currenttree=currentline->right;
                current=current->next;
                k++;
            }else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}
            currentline=currenttree;
            current = RecursiveTree(&currenttree,&*current,beginning,k);
            if (current==NULL){printf("Line %d: Missing 'end'",k+1);getch();exit(1);}
           
            
            
            currenttree=currentline;



        }else if (strcmp(current->token.type,"while")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            currentline=currenttree;
            current=current->next;
            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                variable=current;
                current=current->next;
            }else{printf("Line %d: Missing 'number' or 'variable'",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"<")==0||strcmp(current->token.type,"<=")==0||strcmp(current->token.type,">")==0||strcmp(current->token.type,">=")==0||strcmp(current->token.type,"=")==0||strcmp(current->token.type,"!=")==0){
                currenttree->left=createnode(current->token);
                currenttree=currenttree->left;
                operat=currenttree;
                current=current->next;
                currenttree->left=createnode(variable->token);
            }else{printf("Line %d: Missing 'condition'",k+1);getch();exit(1);}
            if((strcmp(current->token.type,"number")==0||(strcmp(current->token.type,"variable")==0)&& searchVariable(beginning,current->token.name)==1)){
                operat->right=createnode(current->token);
                current=current->next;
                currenttree=operat->right;
            }else{printf("Line %d: Missing 'number' or 'variable'",k+1);getch();exit(1);}
            if(strcmp(current->token.type,"newline")==0){
                currentline->right=createnode(current->token);
                currenttree=currentline->right;
                current=current->next;
                k++;
            }else{printf("Line %d: Missing 'newline'",k+1);getch();exit(1);}
            currentline=currenttree;
            current = RecursiveTree(&currenttree,&*current,beginning,k);
            if (current==NULL){printf("Line %d: Missing 'end'",k+1);getch();exit(1);}
            currenttree=currentline;

        }else if (strcmp(current->token.type,"end")==0){
            currenttree->right=createnode(current->token);
            currenttree=currenttree->right;
            current=current->next; 
            if (current==NULL){
                return current;
            }else if(strcmp(current->token.type,"newline")==0){
                currenttree->right=createnode(current->token);
                currenttree=currenttree->right;
                current=current->next;
                k++;
                while(current!=NULL &&strcmp(current->token.type,"newline")==0){
                    current=current->next;
                    k++;
                }
                // if(strcmp(current->token.type,"newline")==0){
                //     current=current->next;}

                // current=current->next;
                
                return current;   }    
        }else {printf("Line %d: Unrecognized tokens!",k+1);getch();exit(1);}
    }printf("Line %d: Missing 'end'",k+1);getch(); exit(1);
    }else{printf("Line %d: Missing 'begin'!",k+1);getch();exit(1);}
}
void The_Tree(treenode **rootVar,treenode **level){
    struct Node* head=NULL;
    int lineparser=0;
    int linetree=0;
    tokenlist(&head,lineparser);
    struct Node* beginning=head;
    struct Node* current1=createTreeVar(rootVar,head,linetree);

    current1=RecursiveTree(level,&*current1,beginning,linetree);
    //printtree(rootVar);
    //printtree(level);

}

// int main(){
//     // struct Node* head=NULL;
//     // tokenlist(&head);
//     // printList(head);
//     // printf("\n\n%d",searchVariable(head,"mom"));
    
//     treenode *vartree=NULL;
//     treenode *begintree=NULL;
//     The_Tree(&vartree,&begintree);
//     printtree(vartree);
//     printf("\n\n");
//     printtree(begintree);
//     // treenode *rootVar=NULL;
//     // struct Node* current=createTreeVar(&rootVar);
//     // printf("%s",current->token.name);
//     // treenode *n2=createnode(145);
//     // treenode *n3=createnode(50);
//     // treenode *n4=createnode(43);
//     // treenode *n5=createnode(32);

//     // n1->left=n2;
//     // n1->right =n3;
//     // n3->left=n4;
//     // n3->right=n5;
//     // printtree(n1);
//     // free(n1);
//     // free(n2);
//     // free(n3);
//     // free(n4);
//     // free(n5);
//     // freeList(head);
//     getch();
//     return 0;

// }