#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <limits.h>

int n;
int* series;
int min = INT_MAX;
int max = INT_MIN;
int avg = 0;
int size = 0;

void* get_min(void* arg)
{
    (void)arg;
    for (int i = 0; i < size; i++)
    {
        if (series[i] < min)
        {
            min = series[i];
        }
    }

}

void* get_max(void* arg)
{
    (void)arg;
    for (int i = 0; i < size; i++)
    {
        if (series[i] > max)
        {
            max = series[i];
        }
    }
}

void* get_avg(void* arg)
{
    (void)arg;
    for (int i = 0; i < size; i++)
    {
        avg = avg + series[i];
    }
    avg = avg / size;
}

int main(int argc, char* argv[])
{
    size = argc - 1;
    n = atoi(argv[1]);
    series = malloc(n * sizeof(int));

    for (int i = 1; i <= size; i++)
    {
        series[i - 1] = atoi(argv[i]);
    }

    pthread_t thread[3];
    if (pthread_create(&thread[0], NULL, get_min, NULL) != 0)
    {
        printf("Error: Unable To Create Thread\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[1], NULL, get_max, NULL) != 0)
    {
        printf("Error: Unable To Create Thread\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&thread[2], NULL, get_avg, NULL) != 0)
    {
        printf("Error: Unable To Create Thread\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 3; i++)
    {
        if (pthread_join(thread[i], NULL) != 0)
        {
            printf("Error: Unable To Join Thread\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Min: %d\nMax: %d\nAvg: %d\n", min, max, avg);

    free(series);

    return 0;
}