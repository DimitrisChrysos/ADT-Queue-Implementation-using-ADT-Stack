#include "stdio.h"
#include <stdlib.h>
#include <string.h>

#include "ADTQueue.h"

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}


int main(int argc, char *argv[])  {
    
    FILE *filepntr = fopen("outcome.csv", "w");
    Queue queue = queue_create(NULL);

    // to have 2 inserts and 1 remove
    int insert1 = 1;
    int insert2 = 0;
    int remove = 0;
    int sum_real = 0;
    int sum_amortized = 0;
    for (int i=0 ; i < 9000 ; i++)  {
        if (insert1 == 1)  {
            Pointer temp = create_int(i);
            queue_insert_back(queue, temp);
            sum_amortized += queue_steps(queue);
            insert2 = 1;
            insert1 = 0;
            if (strcmp(argv[1], "amortized") == 0)  {
                int amortized_print = sum_amortized / (i + 1);
                fprintf(filepntr,"%d,%d\n", i + 1, amortized_print);
            }
            continue;
        }
        else if (insert2 == 1)  {
            Pointer temp = create_int(i);
            queue_insert_back(queue, temp);
            sum_amortized += queue_steps(queue);
            remove = 1;
            insert2 = 0;
            if (strcmp(argv[1], "amortized") == 0)  {
                int amortized_print = sum_amortized / (i + 1);
                fprintf(filepntr,"%d,%d\n", i + 1, amortized_print);
            }
            continue;
        }
        else if (remove == 1)  {
            queue_remove_front(queue);
            sum_amortized += queue_steps(queue);
            sum_real = queue_steps(queue);
            remove = 0;
            insert1 = 1;
            if (strcmp(argv[1], "real") == 0)  {
                fprintf(filepntr,"%d,%d\n", i + 1, sum_real);
            }
            else if (strcmp(argv[1], "amortized") == 0)  {
                int amortized_print = sum_amortized / (i + 1);      // i+1, because the for loop starts from zero
                fprintf(filepntr,"%d,%d\n", i + 1, amortized_print);
            }
            continue;
        }
    }
    fclose(filepntr);
}