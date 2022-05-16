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
	Stack stack_insert;
	Stack stack_remove;
	Pointer stack_front;
	int steps;
};


int queue_steps(Queue queue) {
	return queue->steps;
}

Queue queue_create(DestroyFunc destroy_value) {
	Queue queue = malloc(sizeof(*queue));
	queue->stack_insert = stack_create(destroy_value);
	queue->stack_remove = stack_create(destroy_value);
	return queue;
}

int queue_size(Queue queue) {
	queue->steps = 1;
	int total_size = stack_size(queue->stack_insert) + stack_size(queue->stack_remove);
	return total_size;
}

Pointer queue_front(Queue queue) {
	queue->steps = 1;
	return queue->stack_front;
}

Pointer queue_back(Queue queue) {
	queue->steps = 1;
	if (stack_size(queue->stack_insert) == 0)  {
		return queue_front(queue);
	}
	else return stack_top(queue->stack_insert);
}

void queue_insert_back(Queue queue, Pointer value) {
	queue->steps = 1;
	if (queue_size(queue) == 0)  {
		queue->stack_front = value;
	}

	stack_insert_top(queue->stack_insert, value);
}


void queue_remove_front(Queue queue) {
	queue->steps = 0;
	int stack_insert_size = stack_size(queue->stack_insert);
	if (stack_size(queue->stack_remove) == 0)  {
		for (int i = 0 ; i < stack_insert_size ; i++)  {
			Pointer value = stack_top(queue->stack_insert);
			stack_insert_top(queue->stack_remove, value);
			stack_remove_top(queue->stack_insert);
		}
		queue->steps = stack_insert_size;
	}
	if (stack_size(queue->stack_remove) != 0)  {
		stack_remove_top(queue->stack_remove);
		if (stack_size(queue->stack_remove) != 0)  {
			queue->stack_front = stack_top(queue->stack_remove);
		}
	}
	if (queue->steps == 0)  {
		queue->steps = 1;
	}
}


DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value) {
	queue->steps = 1;
	stack_set_destroy_value(queue->stack_remove, destroy_value);
	return stack_set_destroy_value(queue->stack_insert, destroy_value);
}

void queue_destroy(Queue queue) {
	queue->steps = 1;
	stack_destroy(queue->stack_insert);
	stack_destroy(queue->stack_remove);
	free(queue);
}
