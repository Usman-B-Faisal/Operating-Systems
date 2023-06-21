#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>

int main(int argc, char* argv[])
{
    int org_num = atoi(argv[1]);

        while (org_num > 1)
        {
            int fd1[2];
            int fd2[2];
            pipe(fd1);
            pipe(fd2);

            int pid = fork();

            if(pid > 0)
            {
                close(fd1[0]);
                int updated_num=0;
                write(fd1[1], &org_num, sizeof(int));
                close(fd2[1]);
                wait(0);
                read(fd2[0], &updated_num, sizeof(int));
                printf("%d\n", updated_num);
                org_num = updated_num;
                close(fd2[0]);
                close(fd1[1]);
            }

            else if(pid == 0)
            {
                close(fd2[0]);
                close(fd1[1]);
                int rec_num = 0;
                read(fd1[0], &rec_num, sizeof(int));

                if(rec_num%2==0)
                {
                    rec_num=rec_num/2;
                }
                else
                {
                    rec_num=((rec_num*3)+1);
                }
            
                write(fd2[1], &rec_num, sizeof(int));
                close(fd2[1]);
                close(fd1[0]);
                exit(0);
            }
        }

    return 0;
}