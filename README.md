![run-tests](../../workflows/run-tests/badge.svg)

## 2022 Project 2

Εκφώνηση: https://k08.chatzi.org/2022/projects/project2/


### Προσωπικά στοιχεία

__Όνομα__: ΔΗΜΗΤΡΙΟΣ ΧΡΥΣΟΣ

__Α.Μ.__: sdi2100275

### Ασκήσεις που παραδίδονται

Συμπληρώστε εδώ τις ασκήσεις (και τυχόν bonus) που παραδίδετε. Αν κάποια άσκηση
βρίσκεται σε μη αναμενόμενα αρχεία αναφέρετε και τα αρχεία αυτά.

- Άσκηση 1
- Άσκηση 2
- Άσκηση 3 (Και το bonus)
- Άσκηση 4
- Άσκηση 5

### Documentation

Συμπληρώστε εδώ __όσο documentation χρειάζεται__ ώστε οι βαθμολογητές να
κατανοήσουν πλήρως τις λύσεις σας και να τις βαθμολογήσουν ανάλογα. Αυτό θα
πρέπει να γίνει ανεξάρτητα με το αν ο κώδικάς σας είναι καλά σχολιασμένος,
πράγμα που συνιστάται.


Άσκηση 1:

~ Πολυπλοκότητες:
- queue_create -> O(1)
- queue_size -> O(1)
- queue_front -> O(1)
- queue_back -> O(1)
- queue_insert_back -> O(1)
- queue_remove_front -> O(n)
- queue_set_destroy_value -> O(1)
- queue_destroy -> O(1)



Άσκηση 2:

~ Σύγκριση Πολυπλοκότητων:
- queue_create
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_size
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_front
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_back
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_insert_back
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_remove_front
ασκ1 -> O(n)
ασκ2 -> O(1) (Πολύ πιο σπάνια χρησιμοποιήται το for για το copy μεταξύ των 2 στοιβών, άρα έχει real time O(n), αλλά amortized time O(1))

- queue_set_destroy_value
ασκ1 -> O(1)
ασκ2 -> O(1)

- queue_destroy
ασκ1 -> O(1)
ασκ2 -> O(1)






Άσκηση 3:

need to type "make" on folder 
/Documents/2022-project-2-DimitrisChrysos/programs/queue_benchmark

run:
a) ./queue_benchmark_using_stack_alt real
b) ./queue_benchmark_using_stack_alt amortized
c) ./queue_benchmark_using_stack real
d) ./queue_benchmark_using_stack amortized
e) ./queue_benchmark_using_list real
f) ./queue_benchmark_using_list amortized

- queue_benchmark_using_stack real:
είναι λογικό καθώς έχει πολυπλοκότητα O(n), που το n συνέχεια αυξάνεται κάτα ένα.

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-17%20153529.png?raw=true)

- queue_benchmark_using_stack amortized:
είναι λογικό καθώς έχει πολυπλοκότητα O(n) και O(1) και διαίρούνται τα steps με n, που το n συνέχεια αυξάνεται κάτα ένα.

temp_node

- queue_benchmark_using_stack_alt real:
είναι λογικό καθώς έχει πολυπλοκότητα O(n) όταν αδειάζει η remove και άλλες O(1) όταν δεν είναι άδεια

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-17%20155910.png?raw=true)

- queue_benchmark_using_stack_alt amortized:
είναι λογικό καθώς έχει πολυπλοκότητα O(1), αφού κυριαρχή η πολυπλότητα σε μεγάλο χρόνο O(1) και διαιρείται με n, που το n συνέχεια αυξάνεται κάτα ένα.

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-17%20160324.png?raw=true)

- queue_benchmark_using_list real:
είναι λογικό καθώς έχει πολυπλοκότητα O(1).

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-17%20160525.png?raw=true)

- queue_benchmark_using_list amortized:
είναι λογικό καθώς έχει πολυπλοκότητα O(1).

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-17%20160812.png?raw=true)


- Bonus:

Για το bonus χρησιμοποιήθηκε ADTVector, και οι συναρτήσεις:
α) vector_insert_last
β) vector_remove_last

Το νέο αρχείο λέγεται vector_benchmark.c, και τα commands για να το τρέξουμε στο
dir .../programs/vector_benchmark είναι:
α) ./vector_benchmark real
β) ./vector_benchmark amortized

- vector_benchmark real:
είναι λογικό καθώς έχει πολυπλοκότητα O(1).

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-19%20143330.png?raw=true)

- vector_benchmark amortized:
είναι λογικό καθώς έχει πολυπλοκότητα O(1).

![alt text](https://github.com/DimitrisChrysos/Data-Structures-project2/blob/master/programs/queue_benchmark/images_for_README/Screenshot%202022-05-19%20142915.png?raw=true)
