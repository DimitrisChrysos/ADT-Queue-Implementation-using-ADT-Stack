///////////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Queue μέσω του ADT Stack (dependent data structure)
//
///////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTQueue.h"
#include "ADTStack.h"


// Ένα Queue είναι pointer σε αυτό το struct.
struct queue {
};


Queue queue_create(DestroyFunc destroy_value) {
	return NULL;
}

int queue_size(Queue queue) {
	return 0;
}

Pointer queue_front(Queue queue) {
	return NULL;
}

Pointer queue_back(Queue queue) {
	return NULL;
}

void queue_insert_back(Queue queue, Pointer value) {

}

void queue_remove_front(Queue queue) {

}

DestroyFunc queue_set_destroy_value(Queue queue, DestroyFunc destroy_value) {
	return NULL;
}

void queue_destroy(Queue queue) {

}
