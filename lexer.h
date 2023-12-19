#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

char* getcode(){
    FILE *file;
    char *code;
    char c;
    code=(char*)malloc(sizeof(char));
    file = fopen("Code.txt","r");
    int i = 0, j = 1;
    while ((c = getc(file))!= EOF) {
    code = (char*)realloc(code, j * sizeof(char));
    code[i] = c;

    i++;
    j++;
    }
    code[i] = '\0'; 
    fclose(file);
    return code;
}

char** tokenize(int &length){
    char ** tokens;  
    tokens=(char**)malloc(sizeof(char*));
    length=0;
    char *code;
    char *line,*instruction;
    line = (char*)malloc(sizeof(char));
    code=getcode();
    while (strstr(code,"\n")){
        int i=0,j=1;
        while (code[i]!='\n') {
            j++;
            i++;
        }
        line=(char*)realloc(line,j*sizeof(char));
        for (i=0;i<j-1;i++){
            line[i]=code[i];
        }
        line[i]='\0';
        memmove(code,code+strlen(line)+1,strlen(code)-strlen(line));
        char *saveptr;  
        instruction = strtok_r(line, " ",&saveptr);
        while(instruction!=NULL){
              
            length++;
            tokens=(char**)realloc(tokens,length*sizeof(char*));
            tokens[length-1]=(char*)malloc((strlen(instruction)+1)*sizeof(char));
            strncpy(tokens[length-1],instruction,strlen(instruction)+1);
            tokens[length-1][strlen(instruction)]='\0';

            instruction = strtok_r(NULL, " ", &saveptr);
            
        }
          

        length++;
        tokens=(char**)realloc(tokens,length*sizeof(char*));
        tokens[length-1]=(char*)malloc(2*sizeof(char));
        strcpy(tokens[length - 1], "\n"); 
          
        


    }

    
    if (*code!='\0'){
        char *saveptr;
        instruction = strtok_r(code, " ",&saveptr);
        while(instruction!=NULL){
        length++;
        tokens=(char**)realloc(tokens,length*sizeof(char*));
        tokens[length-1]=(char*)malloc((strlen(code)+1)*sizeof(char));
        strncpy(tokens[length-1],code,strlen(code)+1);
        tokens[length-1][strlen(code)]='\0';
        instruction = strtok_r(NULL, " ", &saveptr);
        }
    }
    free(code) ;
    free(line) ;
    return tokens;
}

// int main(){
//     char**token;
//     int i=0;
//     int n=0;
//     token = tokenize(n);


//     for(i=0;i<n;i++){
//         printf("%s\n", token[i]);
//     }
//     free(token);
//     getch();
    
//     return 0;
// }