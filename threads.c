#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 4

long long sum = 0;
pthread_mutex_t mutex;

typedef struct {
    int *data;
    int size;
} ThreadArgs;

void *worker(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    long long local_sum = 0;

    for (int i = 0; i < args->size; i++) {
        local_sum += args->data[i];
    }

    pthread_mutex_lock(&mutex);
    sum += local_sum;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    int n;
    printf("Enter N: ");
    scanf("%d", &n);

    if (n < 16) {
        printf("N must be at least 16\n");
        return 1;
    }

    int *array = malloc(n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 100;
    }

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    pthread_mutex_init(&mutex, NULL);

    pthread_t threads[NUM_THREADS];
    ThreadArgs args[NUM_THREADS];

    int base = n / NUM_THREADS;
    int remainder = n % NUM_THREADS;
    int offset = 0;

    for (int i = 0; i < NUM_THREADS; i++) {
        args[i].data = array + offset;
        args[i].size = base + (i < remainder ? 1 : 0);
        offset += args[i].size;
        pthread_create(&threads[i], NULL, worker, &args[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Sum: %lld\n", sum);

    pthread_mutex_destroy(&mutex);
    free(array);
    return 0;
}
