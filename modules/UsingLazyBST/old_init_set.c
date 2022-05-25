SetNode init_set_from_vector_with_balanced_tree(Set set, Vector values, VectorNode start, VectorNode end, CompareFunc compare)  {
	int pos_start = 0;
	int pos_end = vector_size(values) - 1;
	int i = 0;

	// to find where start and end is
	for (VectorNode node = vector_first(values) ; node != vector_next(values, start) ; node = vector_next(values, node))  {
		SetNode node_set = vector_node_value(values, node);
		SetNode start_set = vector_node_value(values, start);
		if (node_set->value == start_set->value)  {
			pos_start = i;
		}
		i++;
	}
	i = 0;
	for (VectorNode node = vector_first(values) ; node != vector_next(values, end) ; node = vector_next(values, node))  {
		SetNode node_set = vector_node_value(values, node);
		SetNode end_set = vector_node_value(values, end);
		if (pos_end == pos_start)  {
			break;
		}
		else if (node_set->value == end_set->value)  {
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
	printf("~ node = %d\n", *(int*)value_of_middle);
	VectorNode middle_node = vector_find_node(values, value_of_middle, compare);
	SetNode middle_set_node = vector_node_value(values, middle_node);
	printf("~ vector_value_is = %d\n", *(int*)middle_set_node->value);
	SetNode node_for_root = vector_get_at(values, middle);
	SetNode root = node_for_root;
	printf("~ vector_value_is = %d\n", *(int*)node_for_root->value);
	set->size += 1;

	for(VectorNode node1 = vector_first(values) ; node1 != VECTOR_EOF ; node1 = vector_next(values, node1))  {
		SetNode temp_value = vector_node_value(values, node1);
		printf("value is: %d\n", *(int*)temp_value->value);
	}

	VectorNode new_end = vector_previous(values, middle_node);
	SetNode node_for_new_end = vector_get_at(values, middle-1);
	printf("~ vector_value_is = %d\n", *(int*)node_for_new_end->value);
	VectorNode new_start = vector_next(values, middle_node);
	SetNode node_for_new_start = vector_get_at(values, middle+1);
	printf("~ vector_value_is = %d\n", *(int*)node_for_new_start->value);
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