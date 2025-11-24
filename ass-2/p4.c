#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

char **parseToken(char *line)
{
    char **tokens = malloc(sizeof(char *) * 10);
    int i = 0;

    char *tok = strtok(line, " \n");
    while (tok)
    {
        tokens[i++] = tok;
        tok = strtok(NULL, " \n");
    }

    tokens[i] = NULL;
    return tokens;
}

int doSearch(const char *option, const char *filename, const char *pattern) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    int line_no = 0;
    int first_line = -1;
    int last_line = -1;
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        line_no++;

        if (strstr(line, pattern)) {
            count++;

            if (first_line == -1)
                first_line = line_no;

            last_line = line_no;
        }
    }

    fclose(fp);

    if (strcmp(option, "f") == 0) {
        if (first_line == -1)
            printf("Pattern not found\n");
        else
            printf("First occurrence at line %d\n", first_line);

    } else if (strcmp(option, "l") == 0) {
        if (last_line == -1)
            printf("Pattern not found\n");
        else
            printf("Last occurrence at line %d\n", last_line);

    } else if (strcmp(option, "c") == 0) {
        printf("Total occurrences = %d\n", count);

    } else {
        printf("Invalid option. Use: f | l | c\n");
    }

    return 0;
}

int main()
{
    char tokensMain[80];

    while (1)
    {
        printf("myshell$ ");
        fflush(stdout);

        if (!(fgets(tokensMain, sizeof(tokensMain), stdin)))
        {
            printf("\n");
            break;
        }

        char *line = strdup(tokensMain);
        char **tokens = parseToken(line);

        if (tokens[0] == NULL)
        {
            printf("No Command\n");
            break;
        }
        else if (strcmp(tokens[0], "exit") == 0)
        {
            printf("Exiting...\n");
            break;
        }
        else if (strcmp(tokens[0], "search") == 0) {
            if (!tokens[1] || !tokens[2] || !tokens[3]) {
                printf("Usage: search <f|l|c> <filename> <pattern>\n");
                free(tokens);
                free(line);
                continue;
            }
        
            doSearch(tokens[1], tokens[2], tokens[3]);
        }        
        else
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(tokens[0], tokens);
                perror("execvp");
                _exit(1);
            }
            else
            {
                int status;
                waitpid(pid, &status, 0);
            }
        }

        free(tokens);
        free(line);
    }

    return 0;
}