
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_bloqueo;

void *contador_padre(void *arg)
{
    int i;

    for (i = 1; i <= 10000; i++)
    {
        if (i == 4000)
        {
            sem_wait(&sem_bloqueo);
        }

        printf("HILO 1 (ASCENDENTE): %d\n", i);

        if (i == 8000)
        {
            sem_post(&sem_bloqueo);
        }
    }

    return NULL;
}

void *contador_hijo(void *arg)
{
    int i;

    for (i = 10000; i >= 1; i--)
    {
        if (i == 8000)
        {
            sem_wait(&sem_bloqueo);
        }

        printf("HILO 2 (DESCENDENTE): %d\n", i);

        if (i == 4000)
        {
            sem_post(&sem_bloqueo);
        }
    }

    return NULL;
}

int main()
{
    pthread_t hilo1, hilo2;

    sem_init(&sem_bloqueo, 0, 1);

    if (pthread_create(&hilo1, NULL, contador_padre, NULL) != 0)
    {
        perror("Error al crear el hilo 1");
        sem_destroy(&sem_bloqueo);
        return 1;
    }

    if (pthread_create(&hilo2, NULL, contador_hijo, NULL) != 0)
    {
        perror("Error al crear el hilo 2");
        pthread_join(hilo1, NULL);
        sem_destroy(&sem_bloqueo);
        return 1;
    }

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    sem_destroy(&sem_bloqueo);

    printf("Los hilos terminaron correctamente\n");

    return 0;
}
