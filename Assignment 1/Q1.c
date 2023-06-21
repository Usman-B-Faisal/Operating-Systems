#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("You Are Now Using My Terminal\n");
    int cmd_totalsize = 256*4;
    int token_totalsize = 16*4;
    int token_totalcapacity = 16*4;
    char *tokens[token_totalcapacity];
    char buffer[cmd_totalsize];
    int token_usedcapacity = 0;
    pid_t pid;
    int cmd_status;
    int status;

    while (1)
    {
        printf("Command Here: ");
        fgets(buffer, cmd_totalsize, stdin);

        token_usedcapacity = 0;
        tokens[token_usedcapacity] = strtok(buffer, " \t\n");
        while (tokens[token_usedcapacity] != NULL && token_usedcapacity < token_totalcapacity - 1) 
        {
            token_usedcapacity++;
            tokens[token_usedcapacity] = strtok(NULL, " \t\n");
        }
        tokens[token_usedcapacity] = NULL;
        
        if (strcmp(tokens[0], "exit") == 0)
        {
            printf("Are You Sure You Want To Quit? (y/n): ");
            char choice;
            scanf(" %c", &choice);
            if (choice == 'y' || choice == 'Y')
            {
                printf("You Are Now Exiting My Terminal\n");
                break;
            }
            else
            {
                continue;
            }
        }

        int bg_flag = 0;
        if (token_usedcapacity > 0 && strcmp(tokens[token_usedcapacity - 1], "&") == 0)
        {
            bg_flag = 1;
            tokens[token_usedcapacity - 1] = NULL;
        }

        pid = fork();
        if (pid == 0)
        {
            cmd_status = execvp(tokens[0], tokens);
            if ( cmd_status < 0)
            {
                printf("Can't Execute This Command Because Of The Following Possible Reasons: \n1. You Entered Your Command Wrongly.\n2. This Terminal Can't Execute This Type Of Command.\n");
                exit(1);
            }
        } 
        else 
        {
            if (!bg_flag) 
            {
                waitpid(pid, &status, 0);
            }
        }
        bg_flag=0;
    }
    return 0;
}