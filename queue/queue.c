#include <stdio.h>
#include <stdlib.h>

struct queue {
    int *data;
    int front;
    int rear;
    int capacity;
};

typedef struct queue *qu;

// Create queue
qu create(int max) {
    qu q = (qu)malloc(sizeof(struct queue));
    if (q == NULL) {
        printf("Memory allocation failed for queue struct\n");
        exit(1);
    }
    q->data = (int*)malloc(sizeof(int) * max);
    if (q->data == NULL) {
        printf("Memory allocation failed for queue data\n");
        free(q);
        exit(1);
    }
    q->capacity = max;
    q->front = -1;
    q->rear = -1;
    return q;
}

// Check if full
int isFull(qu q) {
    return ((q->rear + 1) % q->capacity) == q->front;
}

// Check if empty
int isEmpty(qu q) {
    return q->front == -1;
}

// Enqueue
void enqueue(qu q, int x) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (q->front == -1) { // first element
        q->front = 0;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = x;
}

// Dequeue
void dequeue(qu q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    if (q->front == q->rear) { // only one element
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->capacity;
    }
}

// Display
void display(qu q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int i = q->front;
    while (1) {
        printf("%d ", q->data[i]);
        if (i == q->rear) break;
        i = (i + 1) % q->capacity;
    }
    printf("\n");
}

// Main function
int main() {
    qu q = create(5);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    enqueue(q, 50);
    display(q);
    dequeue(q);
    display(q);
    enqueue(q, 60);
    display(q);
    return 0;
}
