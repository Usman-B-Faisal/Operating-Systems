#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int size = 0;

bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

void* findPrimes(void* arg)
{
    int n = *((int*)arg);

    for (int i = 2; i <= n; i++)
    {
        if (isPrime(i))
        {
            printf("%d ", i);
        }
    }

    printf("\n");

    return NULL;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);

    pthread_t thread;
    if (pthread_create(&thread, NULL, findPrimes, &n) != 0)
    {
        printf("Error: Unable To Create Thread\n");
        exit(1);
    }

    pthread_join(thread, NULL);

    return 0;
}
