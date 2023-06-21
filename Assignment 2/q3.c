#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int n;
int* series;

void* fibonacciGenerator(void* arg)
{
    (void)arg;
    series[0] = 0;
    series[1] = 1;
    for (int i = 2; i < n; i++)
    {
        series[i] = series[i - 1] + series[i - 2];
    }

    printf("Series: ");
    for (int i = 0; i < n; i++)
    {
        printf(" %d", series[i]);
    }
    printf("\n");

    return NULL;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Error: Invalid Command Line Argument\n");
        exit(1);
    }

    n = atoi(argv[1]);
    series = malloc(n * sizeof(int));

    pthread_t thread;
    if (pthread_create(&thread, NULL, fibonacciGenerator, NULL) != 0)
    {
        printf("Error: Unable To Create Thread\n");
        exit(1);
    }

    if (pthread_join(thread, NULL) != 0)
    {
        printf("Error: Unable To Join Thread\n");
        exit(1);
    }

    for (int i = 1; argv[i + 1] != NULL; i++)
    {
        printf("%d\t", series[i - 1]);
    }

    free(series);

    return 0;
}