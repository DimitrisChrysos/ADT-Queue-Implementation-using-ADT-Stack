///////////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Queue μέσω του ADT Stack (dependent data structure)
//
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTQueue.h"
#include "ADTStack.h"
#include "ADTVector.h"


// Ένα Queue είναι pointer σε αυτό το struct.
struct queue {
	Stack stack;
	Pointer stack_front;
	int steps;
};


int queue_steps(Queue queue) {
	return queue->steps;
}

Queue queue_create(DestroyFunc destroy_value) {
	Queue queue = malloc(sizeof(*queue));
	queue->stack = stack_create(destroy_value);
	queue->steps = 1;
	return queue;
}

int queue_size(Queue queue) {
	queue->steps = 1;
	return stack_size(queue->stack);
}

Pointer queue_front(Queue queue) {
	queue->steps = 1;
	return queue->stack_front;
}

Pointer queue_back(Queue queue) {
	queue->steps = 1;
	return stack_top(queue->stack);
}

void queue_insert_back(Queue queue, Pointer value) {
	if (queue_size(queue) == 0)  {
		queue->stack_front = value;
	}
	queue->steps = 1;
	stack_insert_top(queue->stack, value);
}

void queue_remove_front(Queue queue) {
	Vector vector = vector_create(queue_size(queue) - 1, NULL);
	int starting_size = queue_size(queue);
	for (int i = queue_size(queue) - 2 ; i >=0 ; i--)  {		// i = queue_size(queue) - 2, to not add the first value of the stack to the vector
		Pointer value = stack_top(queue->stack);
		vector_set_at(vector, i, value);
		stack_remove_top(queue->stack);
	}
	stack_remove_top(queue->stack);		// to remove the last one remaining from the stack
	for (int i = 0 ; i < vector_size(vector) ; i++)  {
		Pointer value = vector_get_at(vector, i);
		queue_insert_back(queue, value);
	}
	vector_destroy(vector);
	queue->steps = starting_size;
}

DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value) {
	queue->steps = 1;
	return stack_set_destroy_value(queue->stack, destroy_value);
}

void queue_destroy(Queue queue) {
	queue->steps = 1;
	stack_destroy(queue->stack);
	free(queue);
}
