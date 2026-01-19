#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ITER 2000000000LL   // total iterations
#define THREADS 1           // number of threads

typedef struct {
    long long start;
    long long end;
    long long result;
} ThreadData;

void* work(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    long long sum = 0;
    for (long long i = data->start; i < data->end; i++) {
        sum += i;   // dummy computation
    }
    data->result = sum;
    return NULL;
}

int main() {
    struct timespec start, end;
    pthread_t threads[THREADS];
    ThreadData td[THREADS];

    long long chunk = ITER / THREADS;

    clock_gettime(CLOCK_MONOTONIC, &start);

    // Create threads
    for (int i = 0; i < THREADS; i++) {
        td[i].start = i * chunk;
        td[i].end = (i == THREADS - 1) ? ITER : (i + 1) * chunk;
        td[i].result = 0;
        pthread_create(&threads[i], NULL, work, &td[i]);
    }

    // Wait for threads
    long long total = 0;
    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
        total += td[i].result;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time = (end.tv_sec - start.tv_sec) +
                  (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Total sum = %lld\n", total);
    printf("Time taken with %d threads: %.2f seconds\n", THREADS, time);

    return 0;
}

