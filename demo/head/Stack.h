/*
 * Stack
 *
 *  Created on: 2014��11��12��
 *      Author: jindong.zjd
 */

#ifndef STACK_
#define STACK_

struct Stack {
	struct Node{
		int data;
		struct Node* pre;
		struct Node* next;
	}* head;
	void init(int data);
	void push(int data);
	int pop();
	void clean();
} ;


#endif /* STACK_ */
