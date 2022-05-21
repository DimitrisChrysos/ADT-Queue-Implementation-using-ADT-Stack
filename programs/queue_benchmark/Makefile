# Κάνοντας compile το <foo>_test.c με μια υλοποίηση <foo>.c του
# συγκεκριμένου τύπου, παράγουμε ένα tets για την υλοποίηση αυτή.


queue_benchmark_using_stack_OBJS = queue_benchmark.o $(MODULES)/UsingADTStack/ADTQueue.o $(MODULES)/UsingADTList/ADTStack.o $(MODULES)/UsingLinkedList/ADTList.o $(MODULES)/UsingDynamicArray/ADTVector.o

queue_benchmark_using_stack_alt_OBJS = queue_benchmark.o $(MODULES)/UsingADTStack/ADTQueue_alt.o $(MODULES)/UsingADTList/ADTStack.o $(MODULES)/UsingLinkedList/ADTList.o $(MODULES)/UsingDynamicArray/ADTVector.o

queue_benchmark_using_list_OBJS = queue_benchmark.o $(MODULES)/UsingADTList/ADTQueue.o $(MODULES)/UsingADTList/ADTStack.o $(MODULES)/UsingLinkedList/ADTList.o $(MODULES)/UsingDynamicArray/ADTVector.o

# Ο βασικός κορμός του Makefile
include ../../common.mk