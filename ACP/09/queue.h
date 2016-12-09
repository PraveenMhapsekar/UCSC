
typedef struct queue {
    int front;
    int rear;
    int capacity;
    char *data;
 } queue_t;

queue_t *createQ(int);
void enQueue(queue_t *q, int data);
int deQueue(queue_t *q);
int front(queue_t *q);
int isFull(queue_t *q);
int isEmpty(queue_t *q);

