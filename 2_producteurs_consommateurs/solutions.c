#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TOTAL_ITEMS 131072
// création du buffer
int buffer[8];

// position actuelle de in out
int in = 0; 
int out = 0;

// création du mutex de des sémaphores
pthread_mutex_t mutex;
sem_t empty;   
sem_t full; 

// nbr de producteurs et consommateurs (par defaut)
int P = 2;
int C = 2; 

void simulate_cpu() {
    // simulation du traitement CPU
    for (int i = 0; i < 10000; i++); 
}

typedef struct {
    int id;
    int total_a_produire;
} prod_arg_t;

typedef struct {
    int total_a_consommer;
} cons_arg_t;

void* producteur(void* arg) {
    prod_arg_t* parg = (prod_arg_t*)arg;
    int id = parg->id;
    int total_a_produire = parg->total_a_produire;

    for (int i = 0; i < total_a_produire; i++) {
        // simuler un travail avant de produire
        simulate_cpu();

        // attendre qu'il y ait de la place dans le buffer
        sem_wait(&empty);          
        pthread_mutex_lock(&mutex);

        // mettre son ID dans le buffer 
        buffer[in] = id;

        // avancer dans le buffer circulaire           
        in = (in + 1) % 8;

        // libérer le mutex et signaler qu'un élément est disponible
        pthread_mutex_unlock(&mutex);
        sem_post(&full);           
    }
    return NULL;
}

void* consommateur(void* arg) {
    cons_arg_t* carg = (cons_arg_t*)arg;
    int total_a_consommer = carg->total_a_consommer;

    for (int i = 0; i < total_a_consommer; i++) {
        // attendre qu'un élément soit disponible
        sem_wait(&full);           
        pthread_mutex_lock(&mutex);

        // lire l'élément du buffer (inutile ici)
        (void)buffer[out];

        // avancer dans le buffer circulaire
        out = (out + 1) % 8;

        // libérer le mutex et signaler qu'une place est libre
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // simuler un travail après avoir consommé
        simulate_cpu();            
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc > 1) P = atoi(argv[1]);
    if (argc > 2) C = atoi(argv[2]);
    if (P <= 0) {
        fprintf(stderr, "Nombre de producteur(s) invalide\n");
        return 1;
    }
    if(C <= 0){
        fprintf(stderr, "Nombre de consommateur(s) invalide\n");
        return 1;
    }
    pthread_t* producteurs = malloc(P * sizeof(pthread_t));
    pthread_t* consommateurs = malloc(C * sizeof(pthread_t));
    prod_arg_t* pargs = malloc(P * sizeof(prod_arg_t));
    cons_arg_t* cargs = malloc(C * sizeof(cons_arg_t));

    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, 8);
    sem_init(&full, 0, 0);

    // Calcul répartition exacte des éléments
    int base_prod = TOTAL_ITEMS / P;
    int extra_prod = TOTAL_ITEMS % P;
    int base_cons = TOTAL_ITEMS / C;
    int extra_cons = TOTAL_ITEMS % C;

    // producteurs
    for (int i = 0; i < P; i++) {
        pargs[i].id = i;
        pargs[i].total_a_produire = base_prod + (i < extra_prod ? 1 : 0);
        pthread_create(&producteurs[i], NULL, producteur, &pargs[i]);
    }

    // consommateurs
    for (int i = 0; i < C; i++) {
        cargs[i].total_a_consommer = base_cons + (i < extra_cons ? 1 : 0);
        pthread_create(&consommateurs[i], NULL, consommateur, &cargs[i]);
    }

    // join
    for (int i = 0; i < P; i++) pthread_join(producteurs[i], NULL);
    for (int i = 0; i < C; i++) pthread_join(consommateurs[i], NULL);

    // suppression du mutex et sémaphores   
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    // free les threads 
    free(producteurs);
    free(consommateurs);
    free(pargs);
    free(cargs);
    return 0;
}
