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
};


Queue queue_create(DestroyFunc destroy_value) {
	Queue queue = malloc(sizeof(*queue));
	queue->stack = stack_create(destroy_value);
	return queue;
}

int queue_size(Queue queue) {
	return stack_size(queue->stack);
}

Pointer queue_front(Queue queue) {
	return queue->stack_front;	// Needs work, that's why test_insert does not work!!!
}

Pointer queue_back(Queue queue) {
	return stack_top(queue->stack);
}

void queue_insert_back(Queue queue, Pointer value) {
	if (queue_size(queue) == 0)  {
		queue->stack_front = value;
	}

	stack_insert_top(queue->stack, value);
}

void queue_remove_front(Queue queue) {
	Vector vector = vector_create(queue_size(queue), NULL);
	while (queue_size(queue) != 0)  {
		Pointer value = queue_back(queue);
		vector_insert_last(vector, value);
		stack_remove_top(queue->stack);
	}
	vector_remove_last(vector);
	int new_size = vector_size(vector);
	int i = new_size-1;
	while (queue_size(queue) != new_size)  {
		Pointer value = vector_get_at(vector, i);
		i--;
		stack_insert_top(queue->stack, value);
	}

	vector_destroy(vector);
}

DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value) {
	return stack_set_destroy_value(queue->stack, destroy_value);
}

void queue_destroy(Queue queue) {
	stack_destroy(queue->stack);
	free(queue);
}
