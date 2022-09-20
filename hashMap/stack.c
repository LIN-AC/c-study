//#include <stdio.h>
//#include<stdlib.h>
//
//typedef int Elem;
//
//typedef struct stack_c {
//	int size;
//	int max;
//	int* data;
//}Stack;
//
//Stack* init_stack(int);//��ʼ��
//void push(Stack*, Elem);//��ջ
//Elem pop(Stack*);//��ջ
//Elem peek(Stack*);//��ȡջ��Ԫ��
//int is_full(Stack*);//����
//int is_empty(Stack*);//�п�
//
//
//
//Stack* init_stack(int max) {
//	Stack* stack = (Stack*)malloc(sizeof(Stack));
//	if (stack == NULL) return NULL;
//	stack->size = 0;
//	stack->max = max;
//	stack->data = (Elem*)malloc(sizeof(Elem) * max);
//	return stack;
//}
//
//int is_full(Stack* stack) {
//	return stack->size == stack->max;
//}
//int is_empty(Stack* stack) {
//	return stack->size == 0;
//}
//
//void push(Stack* stack, Elem item) {
//	if (is_full(stack)) {
//		puts("the stack is full.\n");
//		return;
//	}
//	stack->data[stack->size++] = item;
//}
//
//Elem pop(Stack* stack) {
//	if (is_empty(stack)) {
//		puts("the stack is empty.\n");
//		return;
//	}
//	return stack->data[--stack->size];
//}
//
//Elem peek(Stack* stack) {
//	if (is_empty(stack)) {
//		puts("the stack is empty.\n");
//		return;
//	}
//	return stack->data[stack->size-1];
//}
//
