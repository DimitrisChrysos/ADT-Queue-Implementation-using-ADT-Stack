![run-tests](../../workflows/run-tests/badge.svg)

## 2022 Project 2

Εκφώνηση: https://k08.chatzi.org/projects/project2/


### Προσωπικά στοιχεία

__Όνομα__: ...

__Α.Μ.__: sdi???????

### Ασκήσεις που παραδίδονται

Συμπληρώστε εδώ τις ασκήσεις (και τυχόν bonus) που παραδίδετε. Αν κάποια άσκηση
βρίσκεται σε μη αναμενόμενα αρχεία αναφέρετε και τα αρχεία αυτά.

- ...
- ...

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


