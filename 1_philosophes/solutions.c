#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Création de variables
#define CYCLES 1000000
pthread_mutex_t *forks;
int N;

void* philosophes(void* arg){
    int id = *(int*)arg;
    for (int i = 0; i < CYCLES; i++){
        if (id % 2 == 0){
            // D'abord les pairs
            pthread_mutex_lock(&forks[id]);
            pthread_mutex_lock(&forks[(id+1)%N]);

        } else{
            // Ensuite les impairs
            pthread_mutex_lock(&forks[(id+1)%N]);
            pthread_mutex_lock(&forks[id]);
        }

        // Manger
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id+1)%N]);
        // Penser 
    }
    return NULL;
}

int main(int argc, char *argv[]){
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
    for (int i = 0; i < N; i++){
        pthread_mutex_init(&forks[i], NULL);
    }

    // Créer les philosophes
    for (int i = 0; i < N; i++){
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosophes, &ids[i]);
    }

    // Attendre la fin
    for (int i = 0; i < N; i++){
        pthread_join(threads[i], NULL);
    }

    // Nettoyage
    for (int i = 0; i < N; i++){
        pthread_mutex_destroy(&forks[i]);
    }
    free(forks);
    free(threads);
    free(ids);

    //printf("Les %d philosophes ont termine leurs %d cycles.\n", N, CYCLES);
    return 0;
}