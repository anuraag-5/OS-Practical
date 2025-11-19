// myshell_count.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char **parsetoken(char *line)
{
    char **tokens = malloc(10 * sizeof(char *));
    int i = 0;
    char *tok = strtok(line, " \n");
    while (tok && i < 10)
    {
        tokens[i++] = tok;
        tok = strtok(NULL, " \n");
    }
    tokens[i] = NULL;
    return tokens;
}

int do_count(char arg, const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (!fp)
    {
        perror("fopen");
        return 1;
    }

    int ch;
    long chars = 0, words = 0, lines = 0;
    int inword = 0;
    int last = -1;

    while ((ch = fgetc(fp)) != EOF)
    {
        chars++;
        if (ch == '\n')
            lines++;
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
        {
            inword = 0;
        }
        else
        {
            if (!inword)
            {
                inword = 1;
                words++;
            }  
        }
        last = ch;
    }

    if (chars > 0 && last != '\n')
        lines++;
        
    switch (arg)
    {
    case 'c':
        printf("Character count: %ld\n", chars);
        break;
    case 'w':
        printf("Word count: %ld\n", words);
        break;
    case 'l':
        printf("Line count: %ld\n", lines);
        break;
    default:
        fprintf(stderr, "Usage: count <c|w|l> <filename>\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);
    return 0;
}

int main()
{
    char buf[80];

    while (1)
    {
        printf("myshellS$ ");
        fflush(stdout);
        if (!fgets(buf, sizeof(buf), stdin))
        {
            printf("\n");
            break;
        }

        char *line = strdup(buf);
        char **tokens = parsetoken(line);

        if (!tokens)
        {
            free(line);
            continue;
        }
        if (tokens[0] == NULL)
        {
            free(tokens);
            free(line);
            continue;
        }
        if (strcmp(tokens[0], "exit") == 0)
        {
            free(tokens);
            free(line);
            break;
        }

        if (strcmp(tokens[0], "count") == 0)
        {
            if (!tokens[1] || !tokens[2])
            {
                fprintf(stderr, "Usage: count <c|w|l> <filename>\n");
            }
            else
            {
                do_count(tokens[1][0], tokens[2]);
            }
            free(tokens);
            free(line);
            continue;
        }

        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
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

        free(tokens);
        free(line);
    }
    return 0;
}
