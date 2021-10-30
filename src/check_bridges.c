#include "pathfinder.h"

static bool is_island_present(char **islands, int size, char *point) {
	for (int i = 0; i < size; i++) {
		if (!islands[i]) {
			return false;
		}
		if (!(mx_strcmp(islands[i], point))) {
			return true;
		}
	}
	return false;
}

void check_bridges(t_bridge* list, int received_count) {
	t_bridge *head = list;
	int outter_counter = 0, inner_counter = 0; 
	
	// duplicate islands in one line
	for (t_bridge* temp = head; temp; temp = temp->next) {
		if (!(mx_strcmp(temp->point1, temp->point2))) {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(outter_counter + 2));
			mx_printerr(" is not valid\n");
			exit(0);
		}
		outter_counter++;
	}
	
	outter_counter = 0;

	// duplicate bridges
	for (; list; list = list->next) {
		inner_counter = 0;
		for (t_bridge *temp = head; temp; temp = temp->next) {
			if (inner_counter == outter_counter) {
				inner_counter++;
				continue;
			}
			if (!(mx_strcmp(list->point1, temp->point1)) 
			 && !(mx_strcmp(list->point2, temp->point2))) {
				mx_printerr("error: duplicate bridges\n");
				exit(0);
			}
			if (!(mx_strcmp(list->point1, temp->point2))
				&& !(mx_strcmp(list->point2, temp->point1))) {
				mx_printerr("error: duplicate bridges\n");
				exit(0);
			}
			inner_counter++;
		}
		outter_counter++;
	}

	// checking sum of bridges
	long long sum_of_bridges = 0;
	for (t_bridge* temp = head; temp; temp = temp->next) {
		sum_of_bridges += temp->length;
		if (sum_of_bridges > INT_MAX) {
			mx_printerr("error: sum of bridges lengths is too big\n");
			exit(0);
		}
	}

	char **islands = malloc(outter_counter * 2 * sizeof(char*));
	for (int j = 0; j < outter_counter * 2; j++) {
		islands[j] = NULL;
	}

	// checking count of islands
	int i = 0;
	for (t_bridge* temp = head; temp; temp = temp->next) {
		if (!(is_island_present(islands, outter_counter * 2, temp->point1))) {
			islands[i++] = mx_strncpy(mx_strnew(mx_strlen(temp->point1)), temp->point1, mx_strlen(temp->point1));
		}
		if (!(is_island_present(islands, outter_counter * 2, temp->point2))) {
			islands[i++] = mx_strncpy(mx_strnew(mx_strlen(temp->point2)), temp->point2, mx_strlen(temp->point2));
		}
	}

	mx_del_strarr(&islands);

	if (i != received_count) {
		mx_printerr("error: invalid number of islands\n");
		exit(0);
	}


}

