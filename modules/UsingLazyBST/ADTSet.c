///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Set μέσω Binary Search Tree (BST)
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "ADTSet.h"
#include "ADTVector.h"


// Υλοποιούμε τον ADT Set μέσω BST, οπότε το struct set είναι ένα Δυαδικό Δέντρο Αναζήτησης.
struct set {
	SetNode root;				// η ρίζα, NULL αν είναι κενό δέντρο
	int size;					// μέγεθος, ώστε η set_size να είναι Ο(1)
	CompareFunc compare;		// η διάταξη
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του set
};

// Ενώ το struct set_node είναι κόμβος ενός Δυαδικού Δέντρου Αναζήτησης
struct set_node {
	SetNode left, right;		// Παιδιά
	Pointer value;				// Τιμή κόμβου
	int height;					// Ύψος που βρίσκεται ο κόμβος στο δέντρο
	int size;					// Μέγεθος που έχει ο κόμβος
};

// Επιστρέφει τη max τιμή μεταξύ 2 ακεραίων

static int int_max(int a, int b) {
	return (a > b) ? a : b ;
}

// Επιστρέφει το ύψος που βρίσκεται ο κόμβος στο δέντρο

static int node_height(SetNode node) {
	if (!node) return 0;
	return node->height;
}

// Επιστρέφει το μέγεθος που έχει ο κόμβος που βρίσκεται ο κόμβος στο δέντρο

static int node_size(SetNode node) {
	if (!node) return 0;
	return node->size;
}

// Ενημερώνει το ύψος ενός κόμβου

static void node_update_height(SetNode node) {
	node->height = 1 + int_max(node_height(node->left), node_height(node->right));
}

// Ενημερώνει το μέγεθος ενός κόμβου

static void node_update_size(SetNode node) {
	node->size = 1 + node_size(node->left) + node_size(node->right);
}

// Παρατηρήσεις για τις node_* συναρτήσεις
// - είναι βοηθητικές (κρυφές από το χρήστη) και υλοποιούν διάφορες λειτουργίες πάνω σε κόμβους του BST.
// - είναι αναδρομικές, η αναδρομή είναι γενικά πολύ βοηθητική στα δέντρα.
// - όσες συναρτήσεις _τροποποιούν_ το δέντρο, ουσιαστικά ενεργούν στο _υποδέντρο_ με ρίζα τον κόμβο node, και επιστρέφουν τη νέα
//   ρίζα του υποδέντρου μετά την τροποποίηση. Η νέα ρίζα χρησιμοποιείται από την προηγούμενη αναδρομική κλήση.
//
// Οι set_* συναρτήσεις (πιο μετά στο αρχείο), υλοποιούν τις συναρτήσεις του ADT Set, και είναι απλές, καλώντας τις αντίστοιχες node_*.


// Δημιουργεί και επιστρέφει έναν κόμβο με τιμή value (χωρίς παιδιά)

static SetNode node_create(Pointer value) {
	SetNode node = malloc(sizeof(*node));
	node->left = NULL;
	node->right = NULL;
	node->value = value;
	node->height = 0;
	node->size = 1;
	
	return node;
}

// Επιστρέφει τον κόμβο με τιμή ίση με value στο υποδέντρο με ρίζα node, διαφορετικά NULL

static SetNode node_find_equal(SetNode node, CompareFunc compare, Pointer value) {
	// κενό υποδέντρο, δεν υπάρχει η τιμή
	if (node == NULL)
		return NULL;
	
	// Το πού βρίσκεται ο κόμβος που ψάχνουμε εξαρτάται από τη διάταξη της τιμής
	// value σε σχέση με την τιμή του τρέχοντος κόμβο (node->value)
	//
	int compare_res = compare(value, node->value);			// αποθήκευση για να μην καλέσουμε την compare 2 φορές
	if (compare_res == 0)									// value ισοδύναμη της node->value, βρήκαμε τον κόμβο
		return node;
	else if (compare_res < 0)								// value < node->value, ο κόμβος που ψάχνουμε είναι στο αριστερό υποδέντρο
		return node_find_equal(node->left, compare, value);
	else													// value > node->value, ο κόμβος που ψάχνουμε είνια στο δεξιό υποδέντρο
		return node_find_equal(node->right, compare, value);
}

// Επιστρέφει τον μικρότερο κόμβο του υποδέντρου με ρίζα node

static SetNode node_find_min(SetNode node) {
	return node != NULL && node->left != NULL
		? node_find_min(node->left)				// Υπάρχει αριστερό υποδέντρο, η μικρότερη τιμή βρίσκεται εκεί
		: node;									// Αλλιώς η μικρότερη τιμή είναι στο ίδιο το node
}

// Επιστρέφει τον μεγαλύτερο κόμβο του υποδέντρου με ρίζα node

static SetNode node_find_max(SetNode node) {
	return node != NULL && node->right != NULL
		? node_find_max(node->right)			// Υπάρχει δεξί υποδέντρο, η μεγαλύτερη τιμή βρίσκεται εκεί
		: node;									// Αλλιώς η μεγαλύτερη τιμή είναι στο ίδιο το node
}

// Επιστρέφει τον προηγούμενο (στη σειρά διάταξης) του κόμβου target στο υποδέντρο με ρίζα node,
// ή NULL αν ο target είναι ο μικρότερος του υποδέντρου. Το υποδέντρο πρέπει να περιέχει τον κόμβο
// target, οπότε δεν μπορεί να είναι κενό.

static SetNode node_find_previous(SetNode node, CompareFunc compare, SetNode target) {
	if (node == target) {
		// Ο target είναι η ρίζα του υποδέντρου, o προηγούμενός του είναι ο μεγαλύτερος του αριστερού υποδέντρου.
		// (Aν δεν υπάρχει αριστερό παιδί, τότε ο κόμβος με τιμή value είναι ο μικρότερος του υποδέντρου, οπότε
		// η node_find_max θα επιστρέψει NULL όπως θέλουμε.)
		return node_find_max(node->left);

	} else if (compare(target->value, node->value) < 0) {
		// Ο target είναι στο αριστερό υποδέντρο, οπότε και ο προηγούμενός του είναι εκεί.
		return node_find_previous(node->left, compare, target);

	} else {
		// Ο target είναι στο δεξί υποδέντρο, ο προηγούμενός του μπορεί να είναι επίσης εκεί,
		// αν όχι ο προηγούμενός του είναι ο ίδιος ο node.
		SetNode res = node_find_previous(node->right, compare, target);
		return res != NULL ? res : node;
	}
}

// Επιστρέφει τον επόμενο (στη σειρά διάταξης) του κόμβου target στο υποδέντρο με ρίζα node,
// ή NULL αν ο target είναι ο μεγαλύτερος του υποδέντρου. Το υποδέντρο πρέπει να περιέχει τον κόμβο
// target, οπότε δεν μπορεί να είναι κενό.

static SetNode node_find_next(SetNode node, CompareFunc compare, SetNode target) {
	if (node == target) {
		// Ο target είναι η ρίζα του υποδέντρου, o επόμενός του είναι ο μικρότερος του δεξιού υποδέντρου.
		// (Aν δεν υπάρχει δεξί παιδί, τότε ο κόμβος με τιμή value είναι ο μεγαλύτερος του υποδέντρου, οπότε
		// η node_find_min θα επιστρέψει NULL όπως θέλουμε.)
		return node_find_min(node->right);

	} else if (compare(target->value, node->value) > 0) {
		// Ο target είναι στο δεξί υποδέντρο, οπότε και ο επόμενός του είναι εκεί.
		return node_find_next(node->right, compare, target);

	} else {
		// Ο target είναι στο αριστερό υποδέντρο, ο επόμενός του μπορεί να είναι επίσης εκεί,
		// αν όχι ο επόμενός του είναι ο ίδιος ο node.
		SetNode res = node_find_next(node->left, compare, target);
		return res != NULL ? res : node;
	}
}

bool check_balanced(Set set, SetNode node)  {
	if (node->height >= 4)  {
		if (node->right->size <= (2 / 3) * node->size)
			return true;
		else 
			return false;
		if (node->left->size <= (2 / 3) * node->size)
			return true;
		else 
			return false;
	}
	else
		return true;
}

bool check_upper_balance(Set set, SetNode node, SetNode moving_node)  {
	bool root_balance = check_balanced(set, moving_node);
	if (root_balance == true)  {
		int compare_value = set->compare(set_node_value(set, moving_node), set_node_value(set, node));
		if (compare_value > 0)  {
			moving_node = moving_node->left;
			bool x = check_upper_balance(set, node, moving_node);
			if (x == false)
				return false;
			else
				return true;
		}
		else if (compare_value < 0)  {
			moving_node = moving_node->right;
			bool y = check_upper_balance(set, node, moving_node);
			if (y == false)
				return false;
			else
				return true;
		}
		else
			return true;
	}
	else return false;
}



// Αν υπάρχει κόμβος με τιμή ισοδύναμη της value, αλλάζει την τιμή του σε value, διαφορετικά προσθέτει
// νέο κόμβο με τιμή value. Επιστρέφει τη νέα ρίζα του υποδέντρου, και θέτει το *inserted σε true
// αν έγινε προσθήκη, ή false αν έγινε ενημέρωση.

static SetNode node_insert(SetNode node, CompareFunc compare, Pointer value, bool* inserted, Pointer* old_value) {
	// Αν το υποδέντρο είναι κενό, δημιουργούμε νέο κόμβο ο οποίος γίνεται ρίζα του υποδέντρου
	if (node == NULL) {
		*inserted = true;			// κάναμε προσθήκη
		// node_update_size(node);
		return node_create(value);
	}
	
	// Το που θα γίνει η προσθήκη εξαρτάται από τη διάταξη της τιμής
	// value σε σχέση με την τιμή του τρέχοντος κόμβου (node->value)
	//
	int compare_res = compare(value, node->value);
	if (compare_res == 0) {
		// βρήκαμε ισοδύναμη τιμή, κάνουμε update
		*inserted = false;
		*old_value = node->value;
		node->value = value;

	} else if (compare_res < 0) {
		// value < node->value, συνεχίζουμε αριστερά.
		node->left = node_insert(node->left, compare, value, inserted, old_value);

	} else {
		// value > node->value, συνεχίζουμε δεξιά
		node->right = node_insert(node->right, compare, value, inserted, old_value);
	}

	node_update_height(node);
	node_update_size(node);
	return node;	// η ρίζα του υποδέντρου δεν αλλάζει
}

// Αφαιρεί και αποθηκεύει στο min_node τον μικρότερο κόμβο του υποδέντρου με ρίζα node.
// Επιστρέφει τη νέα ρίζα του υποδέντρου.

static SetNode node_remove_min(SetNode node, SetNode* min_node) {
	if (node->left == NULL) {
		// Δεν έχουμε αριστερό υποδέντρο, οπότε ο μικρότερος είναι ο ίδιος ο node
		*min_node = node;
		return node->right;		// νέα ρίζα είναι το δεξιό παιδί

	} else {
		// Εχουμε αριστερό υποδέντρο, οπότε η μικρότερη τιμή είναι εκεί. Συνεχίζουμε αναδρομικά
		// και ενημερώνουμε το node->left με τη νέα ρίζα του υποδέντρου.
		node->left = node_remove_min(node->left, min_node);
		node_update_height(node);
		node_update_size(node);
		return node;			// η ρίζα δεν μεταβάλλεται
	}
}

// Διαγράφει το κόμβο με τιμή ισοδύναμη της value, αν υπάρχει. Επιστρέφει τη νέα ρίζα του
// υποδέντρου, και θέτει το *removed σε true αν έγινε πραγματικά διαγραφή.

static SetNode node_remove(SetNode node, CompareFunc compare, Pointer value, bool* removed, Pointer* old_value) {
	if (node == NULL) {
		*removed = false;		// κενό υποδέντρο, δεν υπάρχει η τιμή
		return NULL;
	}

	int compare_res = compare(value, node->value);
	if (compare_res == 0) {
		// Βρέθηκε ισοδύναμη τιμή στον node, οπότε τον διαγράφουμε. Το πώς θα γίνει αυτό εξαρτάται από το αν έχει παιδιά.
		*removed = true;
		*old_value = node->value;

		if (node->left == NULL) {
			// Δεν υπάρχει αριστερό υποδέντρο, οπότε διαγράφεται απλά ο κόμβος και νέα ρίζα μπαίνει το δεξί παιδί
			SetNode right = node->right;	// αποθήκευση πριν το free!
			free(node);
			return right;

		} else if (node->right == NULL) {
			// Δεν υπάρχει δεξί υποδέντρο, οπότε διαγράφεται απλά ο κόμβος και νέα ρίζα μπαίνει το αριστερό παιδί
			SetNode left = node->left;		// αποθήκευση πριν το free!
			free(node);
			return left;

		} else {
			// Υπάρχουν και τα δύο παιδιά. Αντικαθιστούμε την τιμή του node με την μικρότερη του δεξιού υποδέντρου, η οποία
			// αφαιρείται. Η συνάρτηση node_remove_min κάνει ακριβώς αυτή τη δουλειά.

			SetNode min_right;
			node->right = node_remove_min(node->right, &min_right);

			// Σύνδεση του min_right στη θέση του node
			min_right->left = node->left;
			min_right->right = node->right;

			free(node);
			return min_right;
		}
	}

	// compare_res != 0, συνεχίζουμε στο αριστερό ή δεξί υποδέντρο, η ρίζα δεν αλλάζει.
	if (compare_res < 0)
		node->left  = node_remove(node->left,  compare, value, removed, old_value);
	else
		node->right = node_remove(node->right, compare, value, removed, old_value);

	node_update_height(node);
	node_update_size(node);
	return node;
}

// Καταστρέφει όλο το υποδέντρο με ρίζα node

static void node_destroy(SetNode node, DestroyFunc destroy_value) {
	if (node == NULL)
		return;
	
	// πρώτα destroy τα παιδιά, μετά free το node
	node_destroy(node->left, destroy_value);
	node_destroy(node->right, destroy_value);

	if (destroy_value != NULL)
		destroy_value(node->value);

	free(node);
}


//// Συναρτήσεις του ADT Set. Γενικά πολύ απλές, αφού καλούν τις αντίστοιχες node_*

Set set_create(CompareFunc compare, DestroyFunc destroy_value) {
	assert(compare != NULL);	// LCOV_EXCL_LINE

	// δημιουργούμε το stuct
	Set set = malloc(sizeof(*set));
	set->root = NULL;			// κενό δέντρο
	set->size = 0;
	set->compare = compare;
	set->destroy_value = destroy_value;

	return set;
}


SetNode init_set_from_vector_with_balanced_tree(Set set, Vector values, VectorNode start, VectorNode end, CompareFunc compare)  {
	int pos_start = 0;
	int pos_end = vector_size(values) - 1;
	int i = 0;

	// to find where start and end is
	for (VectorNode node = vector_first(values) ; node != vector_next(values, start) ; node = vector_next(values, node))  {
		if (vector_node_value(values, node) == vector_node_value(values, start))  {
			pos_start = i;
		}
		i++;
	}
	i = 0;
	for (VectorNode node = vector_first(values) ; node != vector_next(values, end) ; node = vector_next(values, node))  {
		if (pos_end == pos_start)  {
			break;
		}
		else if (vector_node_value(values, node) == vector_node_value(values, end))  {
			pos_end = i;
		}
		i++;
	}

	// to stop
	if (pos_start > pos_end)  {
		return NULL;
	}

	// recursive work
	int middle = (pos_start + pos_end) / 2;
	Pointer value_of_middle = vector_get_at(values, middle);
	// printf("~ node = %d\n", *(int*)value_of_middle);
	VectorNode middle_node = vector_find_node(values, value_of_middle, compare);
	SetNode root = node_create(value_of_middle);
	set->size += 1;


	VectorNode new_end = vector_previous(values, middle_node);
	VectorNode new_start = vector_next(values, middle_node);
	if (set->size < vector_size(values))  {
		if (new_end != NULL)  {
			root->left = init_set_from_vector_with_balanced_tree(set, values, start, new_end, compare);
		}
		else if (vector_size(values) == 2)  {
			root->right = init_set_from_vector_with_balanced_tree(set, values, new_start, end, compare);
			return root;
		}
		if (new_start != NULL)  {
			root->right = init_set_from_vector_with_balanced_tree(set, values, new_start, end, compare);
		}
		else return root;
	}
	node_update_height(root);
	node_update_size(root);
	return root;
}

Set set_create_from_sorted_values(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	Set set = set_create(compare, destroy_value);
	if (vector_size(values) == 0)  {
		return set;
	}

	VectorNode start = vector_first(values);
	VectorNode end = vector_last(values);
	set->root = init_set_from_vector_with_balanced_tree(set, values, start, end, compare);
	
	return set;
}

int set_size(Set set) {
	return set->size;
}

SetNode find_node_father(Set set, SetNode node)  {
	SetNode moving_node = set->root;
	int activate = 1;
	SetNode parent_node;
	while (activate == 1)  {
		int compare_value = set->compare(set_node_value(set, moving_node), set_node_value(set, node));
		if (compare_value > 0)  {
			moving_node = moving_node->left;
		}
		else if (compare_value < 0)  {
			moving_node = moving_node->right;
		}
		else if (compare_value == 0)  {
			moving_node = moving_node->left;
			return parent_node;
		}
		parent_node = moving_node;
	}
	return parent_node;
}

void set_insert(Set set, Pointer value) {
	int starting_size = set->size;
	bool inserted;
	Pointer old_value;
	set->root = node_insert(set->root, set->compare, value, &inserted, &old_value);
	
	// Το size αλλάζει μόνο αν μπει νέος κόμβος. Στα updates κάνουμε destroy την παλιά τιμή
	if (inserted)
		set->size++;
	else if (set->destroy_value != NULL)
		set->destroy_value(old_value);

	SetNode temp_node = set_find_node(set, value);
	SetNode moving_node = set->root;
	bool x = check_upper_balance(set, temp_node, moving_node);
	int after_size = set->size;
	if (x == false && starting_size != after_size)  {
		
		Vector values = vector_create(0, free);

		int activate = 1;
		// SetNode father_node = find_node_father(set, temp_node);
		while (activate == 1)  {
			SetNode	min_node = node_find_min(temp_node);
			Pointer min_value = set_node_value(set, min_node);
			vector_insert_last(values, min_value);
			if (min_node == temp_node)  {
				activate = 0;
				break;
			}
			node_destroy(min_node, set->destroy_value);
		}
		
		// int compare_value = set->compare(set_node_value(set, father_node), set_node_value(set, temp_node));
		Set temp_set = set_create_from_sorted_values(set->compare, free, values);
		// node_destroy(temp_node, free);

		temp_node = temp_set->root;
		// if (compare_value > 0)  {
		// 	father_node->left = temp_set->root;
		// }
		// else if (compare_value < 0)  {
		// 	father_node->right = temp_set->root;
		// }

		// vector_destroy(values);
	}
}

bool set_remove(Set set, Pointer value) {
	bool removed;
	Pointer old_value = NULL;
	set->root = node_remove(set->root, set->compare, value, &removed, &old_value);

	// Το size αλλάζει μόνο αν πραγματικά αφαιρεθεί ένας κόμβος
	if (removed) {
		set->size--;

		if (set->destroy_value != NULL)
			set->destroy_value(old_value);
	}

	return removed;
}

Pointer set_find(Set set, Pointer value) {
	SetNode node = node_find_equal(set->root, set->compare, value);
	return node == NULL ? NULL : node->value;
}

DestroyFunc set_set_destroy_value(Set vec, DestroyFunc destroy_value) {
	DestroyFunc old = vec->destroy_value;
	vec->destroy_value = destroy_value;
	return old;
}

void set_destroy(Set set) {
	node_destroy(set->root, set->destroy_value);
	free(set);
}

SetNode set_first(Set set) {
	return node_find_min(set->root);
}

SetNode set_last(Set set) {
	return node_find_max(set->root);
}

SetNode set_previous(Set set, SetNode node) {
	return node_find_previous(set->root, set->compare, node);
}

SetNode set_next(Set set, SetNode node) {
	return node_find_next(set->root, set->compare, node);
}

Pointer set_node_value(Set set, SetNode node) {
	return node->value;
}

SetNode set_find_node(Set set, Pointer value) {
	return node_find_equal(set->root, set->compare, value);
}



// Συναρτήσεις που δεν υπάρχουν στο public interface αλλά χρησιμοποιούνται στα tests.
// Ελέγχουν ότι το δέντρο είναι ένα σωστό BST.

// LCOV_EXCL_START (δε μας ενδιαφέρει το coverage των test εντολών, και επιπλέον μόνο τα true branches εκτελούνται σε ένα επιτυχημένο test)

static bool node_is_lbst(SetNode node, CompareFunc compare) {
	if (node == NULL)
		return true;

	// Ελέγχουμε την ιδιότητα:
	// κάθε κόμβος είναι > αριστερό παιδί, > δεξιότερο κόμβο του αριστερού υποδέντρου, < δεξί παιδί, < αριστερότερο κόμβο του δεξιού υποδέντρου.
	// Είναι ισοδύναμη με την BST ιδιότητα (κάθε κόμβος είναι > αριστερό υποδέντρο και < δεξί υποδέντρο) αλλά ευκολότερο να ελεγθεί.
	bool res = true;
	if(node->left != NULL)
		res = res && compare(node->left->value, node->value) < 0 && compare(node_find_max(node->left)->value, node->value) < 0;
	if(node->right != NULL)
		res = res && compare(node->right->value, node->value) > 0 && compare(node_find_min(node->right)->value, node->value) > 0;

	// Το ύψος είναι σωστό
	res = res && node->height == 1 + int_max(node_height(node->left), node_height(node->right));


	// Τα υποδέντρα είναι σωστά
	res = res &&
		node_is_lbst(node->left, compare) &&
		node_is_lbst(node->right, compare);

	return res;
}

bool set_is_proper(Set node) {
	return node_is_lbst(node->root, node->compare);
}

// LCOV_EXCL_STOP