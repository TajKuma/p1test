#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define CYCLES 100000

pthread_mutex_t *forks;
int N; // Nombre de philosophes

void* philosophes(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < CYCLES; i++) {
        if (id % 2 == 0) {
            // Philosophe pair : gauche puis droite
            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id+1)%N]);
        } else {
            // Philosophe impair : droite puis gauche
            pthread_mutex_lock(&forks[(id+1)%N]);
            pthread_mutex_lock(&forks[id]);
        }

        // Manger (immédiat)
        
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id+1)%N]);

        // Penser (immédiat)
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    N = 5; // valeur par défaut
    if (argc > 1) {
        N = atoi(argv[1]);
        if (N < 2) {
            fprintf(stderr, "Le nombre de philosophes doit être >= 2.\n");
            return 1;
        }
    }

    forks = malloc(N * sizeof(pthread_mutex_t));
    pthread_t *threads = malloc(N * sizeof(pthread_t));
    int *ids = malloc(N * sizeof(int));

    // Initialiser les mutex
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Créer les philosophes
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosophes, &ids[i]);
    }

    // Attendre la fin
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Nettoyer
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    free(forks);
    free(threads);
    free(ids);

    printf("Les %d philosophes ont termine leurs %d cycles.\n", N, CYCLES);
    return 0;
}
