#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;     // Значение элемента
    int priority;  // Приоритет элемента
} QueueElement;

typedef struct {
    QueueElement *elements; // Массив элементов
    int size;               // Текущий размер очереди
    int capacity;           // Вместимость очереди
} PriorityQueue;
PriorityQueue* createQueue(int capacity) {                     
    PriorityQueue *queue = (PriorityQueue *)malloc(sizeof(PriorityQueue)); ///
    queue->capacity = capacity;
    queue->size = 0;
    queue->elements = (QueueElement *)malloc(capacity * sizeof(QueueElement));
    return queue;
}
void enqueue(PriorityQueue *queue, int value, int priority) {
    if (queue->size >= queue->capacity) {
        printf("The queue is full!\n");
        return;
    }
    
    QueueElement newElement;
    newElement.value = value;
    newElement.priority = priority;

    // Находим позицию для нового элемента
    int i;
    for (i = queue->size - 1; (i >= 0 && queue->elements[i].priority < priority); i--) {
        queue->elements[i + 1] = queue->elements[i];
    }
    
    queue->elements[i + 1] = newElement;
    queue->size++;
}
QueueElement dequeue(PriorityQueue *queue) {
    if (queue->size == 0) {
        printf("The queue is empty!\n");
        exit(EXIT_FAILURE);
    }
    
    return queue->elements[--queue->size];
}
QueueElement dequeueWithPriority(PriorityQueue *queue, int priority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority == priority) {
            QueueElement element = queue->elements[i];

            // Сдвигаем элементы влево
            for (int j = i; j < queue->size - 1; j++) {
                queue->elements[j] = queue->elements[j + 1];
            }
            queue->size--;
            return element;
        }
    }

    printf("The priority element was  %d not found!\n", priority);
    exit(EXIT_FAILURE);
}
QueueElement dequeueWithMinPriority(PriorityQueue *queue, int minPriority) {
    for (int i = 0; i < queue->size; i++) {
        if (queue->elements[i].priority >= minPriority) {
            QueueElement element = queue->elements[i];

            // Сдвигаем элементы влево
            for (int j = i; j < queue->size - 1; j++) {
                queue->elements[j] = queue->elements[j + 1];
            }
            queue->size--;
            return element;
        }
    }

    printf("An element with a priority of at least %d not found!\n", minPriority);
    exit(EXIT_FAILURE);
}
int main() {

    PriorityQueue *queue = createQueue(100);

    enqueue(queue, 5, 10);
    enqueue(queue, 10, 2);
    enqueue(queue, 15, 20);
    enqueue(queue, 16, 40);
    enqueue(queue, 200, 60);
    enqueue(queue, 2500, 50);

    printf("Retrieving the item with the highest priority: %d\n", dequeue(queue).value); //извлечение элемента с наивысшим приоритетом 
    
    printf("Retrieving the item with the 10 priority: %d\n", dequeueWithPriority(queue, 10).value); //извлечение элемента с приоритетом 2
    
    printf("Extracting an item with a priority of at least 50: %d\n", dequeueWithMinPriority(queue, 50).value); //извлечение элемента с приоритетом не ниже 3 
    
    // Освобождение памяти
    free(queue->elements);
    free(queue);
    return 0;
}
