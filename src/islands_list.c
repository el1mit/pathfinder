#include "pathfinder.h"

static bool is_island_present(char** islands, int size, char* point) {
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

char** islands_list(t_bridge *bridges, int islands_count) {
	char** islands = malloc((islands_count + 1) * sizeof(char*));
	for (int j = 0; j < islands_count + 1; j++) {
		islands[j] = NULL;
	}

	// filling islands array without duplicates
	int i = 0;
	for (t_bridge* temp = bridges; temp; temp = temp->next) {
		if (!(is_island_present(islands, islands_count, temp->point1))) {
			islands[i++] = mx_strncpy(mx_strnew(mx_strlen(temp->point1)), temp->point1, mx_strlen(temp->point1));
		}
		if (!(is_island_present(islands, islands_count * 2, temp->point2))) {
			islands[i++] = mx_strncpy(mx_strnew(mx_strlen(temp->point2)), temp->point2, mx_strlen(temp->point2));
		}
	}

	return islands;
}

