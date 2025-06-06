////////////////////////////////////////////////////////////////////////
//
// ADT Set
//
// Abstract διατεταγμένο σύνολο. Τα στοιχεία είναι διατεταγμένα με βάση
// τη συνάρτηση compare, και καθένα εμφανίζεται το πολύ μία φορά.
// Παρέχεται γρήγορη αναζήτηση με ισότητα αλλά και με ανισότητα.
//
////////////////////////////////////////////////////////////////////////

#pragma once // #include το πολύ μία φορά

#include "common_types.h"

#include "ADTVector.h"


// Ενα σύνολο αναπαριστάται από τον τύπο Set

typedef struct set* Set;


// Δημιουργεί και επιστρέφει ένα σύνολο, στο οποίο τα στοιχεία συγκρίνονται με βάση
// τη συνάρτηση compare.
// Αν destroy_value != NULL, τότε καλείται destroy_value(value) κάθε φορά που αφαιρείται ένα στοιχείο.

Set set_create(CompareFunc compare, DestroyFunc destroy_value);

// Η συνάρτηση αυτή δημιουργεί ένα set, το οποίο περιέχει τα στοιχεία του vector values, τα οποία πρέπει 
// να δίνονται ταξινομημένα σε αύξουσα σειρά.
Set set_create_from_sorted_values(CompareFunc compare, DestroyFunc destroy_value, Vector values);

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το σύνολο set.

int set_size(Set set);

// Προσθέτει την τιμή value στο σύνολο, αντικαθιστώντας τυχόν προηγούμενη τιμή ισοδύναμη της value.
//
// ΠΡΟΣΟΧΗ:
// Όσο το value είναι μέλος του set, οποιαδήποτε μεταβολή στο περιεχόμενό του (στη μνήμη που δείχνει) δεν πρέπει
// να αλλάζει τη σχέση διάταξης (compare) με οποιοδήποτε άλλο στοιχείο, διαφορετικά έχει μη ορισμένη συμπεριφορά.

void set_insert(Set set, Pointer value);

// Αφαιρεί τη μοναδική τιμή ισοδύναμη της value από το σύνολο, αν υπάρχει.
// Επιστρέφει true αν βρέθηκε η τιμή αυτή, false διαφορετικά.

bool set_remove(Set set, Pointer value);

// Επιστρέφει την μοναδική τιμή του set που είναι ισοδύναμη με value, ή NULL αν δεν υπάρχει

Pointer set_find(Set set, Pointer value);

// Αλλάζει τη συνάρτηση που καλείται σε κάθε αφαίρεση/αντικατάσταση στοιχείου σε
// destroy_value. Επιστρέφει την προηγούμενη τιμή της συνάρτησης.

DestroyFunc set_set_destroy_value(Set set, DestroyFunc destroy_value);

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το σύνολο.
// Οποιαδήποτε λειτουργία πάνω στο set μετά το destroy είναι μη ορισμένη.

void set_destroy(Set set);


// Διάσχιση του set ////////////////////////////////////////////////////////////
//
// Η διάσχιση γίνεται με τη σειρά διάταξης.

// Οι σταθερές αυτές συμβολίζουν εικονικούς κόμβους _πριν_ τον πρώτο και _μετά_ τον τελευταίο κόμβο του set
#define SET_BOF (SetNode)0
#define SET_EOF (SetNode)0

typedef struct set_node* SetNode;

// Επιστρέφουν τον πρώτο και τον τελευταίο κομβο του set, ή SET_BOF / SET_EOF αντίστοιχα αν το set είναι κενό

SetNode set_first(Set set);
SetNode set_last(Set set);

// Επιστρέφουν τον επόμενο και τον προηγούμενο κομβο του node, ή SET_EOF / SET_BOF
// αντίστοιχα αν ο node δεν έχει επόμενο / προηγούμενο.

SetNode set_next(Set set, SetNode node);
SetNode set_previous(Set set, SetNode node);

// Επιστρέφει το περιεχόμενο του κόμβου node

Pointer set_node_value(Set set, SetNode node);

// Βρίσκει το μοναδικό στοιχείο στο set που να είναι ίσο με value.
// Επιστρέφει τον κόμβο του στοιχείου, ή SET_EOF αν δεν βρεθεί.

SetNode set_find_node(Set set, Pointer value);
