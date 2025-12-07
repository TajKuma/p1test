#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Synchronisation pour lecteurs/écrivains
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_lecteur = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_ecrivain = PTHREAD_COND_INITIALIZER;

int nb_lecteurs = 0;      // Nombre de lecteurs actuellement dans la zone critique
int nb_ecrivains = 0;     // Nombre d'écrivains en train d'écrire (0 ou 1 dans cette version)
int attente_ecrivains = 0; // File d'attente des écrivains

// Données simulées
int base_de_donnees = 0;

void *lecteur(void *arg) {
    int total_lectures = *(int*)arg;

    for(int k = 0; k < total_lectures; k++) {
        // Début section d'entrée lecteur
        pthread_mutex_lock(&mutex);

        // Un écrivain a la priorité si il attend
        while(nb_ecrivains > 0 || attente_ecrivains > 0) {
            pthread_cond_wait(&cond_lecteur, &mutex);
        }

        nb_lecteurs++;
        pthread_mutex_unlock(&mutex);
        // Fin entrée lecteur

        // ---- ZONE CRITIQUE ----
        for(int i = 0; i < 10000; i++); // Simulation de lecture
        int valeur_lue = base_de_donnees;
        // ------------------------

        // Sortie lecteur
        pthread_mutex_lock(&mutex);
        nb_lecteurs--;
        if(nb_lecteurs == 0)
            pthread_cond_signal(&cond_ecrivain);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *ecrivain(void *arg) {
    int total_ecritures = *(int*)arg;

    for(int k = 0; k < total_ecritures; k++) {
        // Début section d'entrée écrivain
        pthread_mutex_lock(&mutex);
        attente_ecrivains++;

        while(nb_lecteurs > 0 || nb_ecrivains > 0) {
            pthread_cond_wait(&cond_ecrivain, &mutex);
        }

        attente_ecrivains--;
        nb_ecrivains = 1;
        pthread_mutex_unlock(&mutex);
        // Fin section d'entrée

        // ---- ZONE CRITIQUE ----
        for(int i = 0; i < 10000; i++); // Simulation d'écriture
        base_de_donnees++;
        // ------------------------

        // Sortie écrivain
        pthread_mutex_lock(&mutex);
        nb_ecrivains = 0;
        pthread_cond_broadcast(&cond_lecteur);
        pthread_cond_signal(&cond_ecrivain);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s <nb_lecteurs> <nb_ecrivains>\n", argv[0]);
        return 1;
    }

    int L = atoi(argv[1]);
    int E = atoi(argv[2]);

    int total_lectures = 25400 / (L > 0 ? L : 1);
    int total_ecritures = 6400 / (E > 0 ? E : 1);

    pthread_t lecteurs[L], ecrivains[E];

    for(int i = 0; i < L; i++)
        pthread_create(&lecteurs[i], NULL, lecteur, &total_lectures);

    for(int i = 0; i < E; i++)
        pthread_create(&ecrivains[i], NULL, ecrivain, &total_ecritures);

    for(int i = 0; i < L; i++)
        pthread_join(lecteurs[i], NULL);

    for(int i = 0; i < E; i++)
        pthread_join(ecrivains[i], NULL);

    printf("Valeur finale de la base de données = %d\n", base_de_donnees);

    return 0;
}
