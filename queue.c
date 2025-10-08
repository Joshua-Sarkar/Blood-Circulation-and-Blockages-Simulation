#include <stdlib.h>
#include "queue.h"

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue* queue, BloodCell* cell) {
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    temp->cell = cell;
    temp->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
    } else {
        queue->rear->next = temp;
        queue->rear = temp;
    }
    queue->size++;
}

BloodCell* dequeue(Queue* queue) {
    if (queue->front == NULL) return NULL;
    QNode* temp = queue->front;
    BloodCell* cell = temp->cell;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    queue->size--;
    return cell;
}

int is_empty(Queue* queue) {
    return queue->front == NULL;
}

void free_queue(Queue* queue) {
    while (!is_empty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
