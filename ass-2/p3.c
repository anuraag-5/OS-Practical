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

int doTypeline(const char *option, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line_buffer[1024];
    long lines_to_print = -1;
    long current_line = 0;
    
    // --- 1. Parse the option ---
    if (strcmp(option, "a") == 0) {
        // 'a': Print all lines. lines_to_print remains -1 (or set to a huge number)
    } else if (option[0] == '-') {
        // '-n': Print last n lines.
        lines_to_print = atol(&option[1]); // Get n from "-n"
        
        // --- Logic for typeline -n (Last N lines) ---
        // 1. Count total lines (L)
        while (fgets(line_buffer, 1024, fp) != NULL) {
            current_line++;
        }
        long total_lines = current_line;
        
        // 2. Calculate the starting line number
        long start_line = total_lines - lines_to_print;
        if (start_line < 1) start_line = 1;

        // 3. Reset file pointer to the beginning
        rewind(fp);
        current_line = 0;

        // 4. Print from the calculated start line
        while (fgets(line_buffer, 1024, fp) != NULL) {
            current_line++;
            if (current_line >= start_line) {
                printf("%s", line_buffer);
            }
        }
        printf("\n");
        fclose(fp);
        return 0;

    } else {
        // 'n': Print first n lines.
        lines_to_print = atol(option);
    }

    // --- 2. Logic for typeline n (First N lines) or typeline a (All lines) ---
    while (fgets(line_buffer, 1024, fp) != NULL) {
        if (lines_to_print != -1 && current_line >= lines_to_print) {
            break; // Stop after n lines (for 'n' option)
        }
        printf("%s", line_buffer);
        current_line++;
    }

    printf("\n");
    fclose(fp);
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
        else if (strcmp(tokens[0], "typeline") == 0)
        {
            if (!tokens[1] || !tokens[2])
            {
                printf("Usage: list <f|n|i> <filename>");
                break;
            }
            else
            {
                doTypeline(tokens[1], tokens[2]);
            }
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