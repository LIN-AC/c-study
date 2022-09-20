#include <stdio.h>
#include <stdlib.h>

typedef int Elem;

typedef struct node {
	Elem data;
	struct node* next;
} Node;

typedef struct queue {
	Node* head;
	Node* rear;
	int size;
} Queue;

Queue* init_queue(Queue*);//初始化
int is_empty(Queue*);//判空
void insert_queue(Queue*, Elem);//入队
Elem dequeue(Queue*);//出队
void destroy(Queue*);//销毁

Queue* init_queue() {
	Queue* queue = (Queue*)malloc(sizeof(Queue));
	if (queue == NULL) return;
	queue->head = NULL;
	queue->rear = NULL;
	queue->size = 0;
	return queue;
}

int is_empty(Queue* queue) {
	return queue->size == 0;
}

void insert_queue(Queue* queue, Elem item) {
	Node* p = (Node*)malloc(sizeof(Node));
	if (p == NULL) return;
	p->data = item;
	p->next = NULL;
	if (is_empty(queue)) {
		queue->head = p;
		queue->rear = p;
	}
	else {
		queue->rear->next = p;
		queue->rear = p;
	}
	queue->size++;
	return;
}

Elem dequeue(Queue* queue) {
	if (is_empty(queue)) return -1;
	Node* p = queue->head;
	queue->head = p->next;
	queue->size--;
	Elem elem = p->data;
	free(p);
	return elem;
}

void destroy(Queue* queue) {
	if (queue->size == 0) free(queue);
	while (queue->size) {
		dequeue(queue);
	}
	free(queue);
}

//int main() {
//	Queue* queue = init_queue();
//	free(queue);
//	return 0;
//	/*insert_queue(queue, 1);
//	insert_queue(queue, 2);
//	insert_queue(queue, 3);
//	insert_queue(queue, 4);
//
//	for (int i = 0; i < 2; i++) {
//		printf("第%d次出队：%d", i, dequeue(queue));
//	}
//
//	destroy(queue);
//
//	return 0;*/
//}