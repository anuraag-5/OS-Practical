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

int doList(char arg, const char *dirname) {
    DIR *dir;
    struct dirent *dp;
    long entry_count = 0;

    // 1. Open the directory
    if ((dir = opendir(dirname)) == NULL) {
        perror("opendir");
        return 1;
    }

    printf("--- Directory: %s ---\n", dirname);

    // 2. Read entries and process based on argument
    while ((dp = readdir(dir)) != NULL) {
        entry_count++;

        if (arg == 'f') {
            // list f: Display filenames
            printf("  %s\n", dp->d_name);
        } else if (arg == 'i') {
            // list i: Display inode number and filenames
            // (Note: d_ino is typically an ino_t, printed as unsigned long or similar)
            printf("  Inode: %lu, Name: %s\n", (unsigned long)dp->d_ino, dp->d_name);
        }
        // 'n' option just counts, so no output here
    }

    // 3. Print count for 'n' option
    if (arg == 'n') {
        printf("Total entries counted: %ld\n", entry_count);
    } else if (arg != 'f' && arg != 'i') {
        fprintf(stderr, "Usage: list <f|n|i> <dirname>\n");
        closedir(dir);
        return 1;
    }

    // 4. Cleanup
    closedir(dir);
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
        else if (strcmp(tokens[0], "list") == 0)
        {
            if (!tokens[1] || !tokens[2])
            {
                printf("Usage: list <f|n|i> <filename>");
                break;
            }
            else
            {
                doList(tokens[1][0], tokens[2]);
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