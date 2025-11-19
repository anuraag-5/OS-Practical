#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #include<unistd.h>
#include<sys/types.h>

char **parseToken(char *line){
    char **tokens = malloc(sizeof(char *) * 10);
    int i = 0;

    char *tok = strtok(line, " \n");
    while(tok){
        tokens[i++] = tok;
        tok = strtok(NULL, " \n");
    }

    tokens[i] = NULL;
    return tokens;
}

void doCount(char cmd, const char *filename){

    FILE *fp = fopen(filename, "r");

    if(fp == NULL) {
        printf("Error in opening file\n");
        return;
    }

    int c;
    long charsCount = 0;
    int wordsCount = 0, linesCount = 0, inWord = 0, last = -1;
    while((c = fgetc(fp)) != EOF){
        char ch = (char)c;
        charsCount++;

        if(ch == '\n') linesCount++;

        if(ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r'){
            inWord = 0;
        } else {
            if(!inWord) {
                inWord = 1;
                wordsCount++;
            }
        }

        last = ch;
    }

    linesCount++;

    switch(cmd){
        case 'c':
        printf("Character Count: %ld\n", charsCount);
        break;

        case 'w': 
        printf("Words Count: %d\n", wordsCount);
        break;

        case 'l':
        printf("Lines Count: %d\n", linesCount);
        break;
    }
    fclose(fp);
}

int main(){
    char tokensMain[80];

    while(1){
        printf("myshell$ ");
        fflush(stdout);

        if(!(fgets(tokensMain, sizeof(tokensMain), stdin))){
            printf("\n");
            break;
        }

        char *line = strdup(tokensMain);
        char **tokens = parseToken(line);

        if(tokens[0] == NULL){
            printf("No Command\n");
            break;
        } else if(strcmp(tokens[0], "exit") == 0){
            printf("Exiting...\n");
            break;
        } else if(strcmp(tokens[0], "count") == 0){
            if(!tokens[1] || !tokens[2]){
                printf("Usage: count <c|w|l> <filenam>");
                break;
            } else {
                doCount(tokens[1][0], tokens[2]);
            }
        }
    }

    return 0;
}