#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *contador_padre(void *arg)
{
    int i;

    for (i = 1; i <= 10000; i++)
    {
        printf("HILO 1 (ASCENDENTE): %d\n", i);
    }

    return NULL;
}

void *contador_hijo(void *arg)
{
    int i;

    for (i = 10000; i >= 1; i--)
    {
        printf("HILO 2 (DESCENDENTE): %d\n", i);
    }

    return NULL;
}

int main()
{
    pthread_t hilo1, hilo2;

    if (pthread_create(&hilo1, NULL, contador_padre, NULL) != 0)
    {
        perror("Error al crear el hilo 1");
        return 1;
    }

    if (pthread_create(&hilo2, NULL, contador_hijo, NULL) != 0)
    {
        perror("Error al crear el hilo 2");
        pthread_join(hilo1, NULL);
        return 1;
    }

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    printf("Los hilos terminaron correctamente\n");

    return 0;
}

