#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Error: Not Enough Arguments\n");
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(argv[1], &argv[1]);
        printf("Error: Can't Execute Command %s\n", argv[1]);
        exit(1);
    }
    else if (pid > 0) 
    {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            gettimeofday(&end, NULL);
            double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
            printf("Elapsed time: %f seconds\n", elapsed_time);
        }
    }
    return 0;
}
