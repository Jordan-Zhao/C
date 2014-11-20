#include <exception>
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "../head/Stack.h"

using namespace std;

void Stack::init(int data) {
	head = (Node*) malloc(sizeof(Node));
	head->data = data;
	head->pre = NULL;
}

void Stack::push(int data) {
	Node* node = (Node*) malloc(sizeof(Node));
	node->data = data;
	node->pre = head;
	head->next = node;
	head = node;
}

int Stack::pop() {
	Node* node = head;
	int data = node->data;
	head = node->pre;
	free(node);
	return data;
}

void Stack::clean() {
	while (head) {
		Node* node = head;
		head = node->pre;
		free(node);
	}
}

void testStack() {
	try {
		Stack* stack = (Stack*) malloc(sizeof(Stack));
		stack->init(100);
		stack->push(108);
		stack->push(200);
		//printf("%d \n", stack->pop());
		//printf("%d \n", stack->pop());
		stack->clean();
	} catch (exception e) {
		cout << e.what();
	}
}
