#ifndef QUEUE_H
#define QUEUE_H

typedef struct BloodCell {
    int id;
} BloodCell;

typedef struct QNode {
    BloodCell* cell;
    struct QNode* next;
} QNode;

typedef struct Queue {
    QNode* front;
    QNode* rear;
    int size;
} Queue;

Queue* create_queue();
void enqueue(Queue* queue, BloodCell* cell);
BloodCell* dequeue(Queue* queue);
int is_empty(Queue* queue);
void free_queue(Queue* queue);

#endif
