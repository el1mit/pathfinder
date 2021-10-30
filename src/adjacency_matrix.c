#include "pathfinder.h"

static int island_number(char** islands, int size, char* name) {
	for (int i = 0; i < size; i++) {
		if (!islands[i]) {
			return -1;
		}
		if (!(mx_strcmp(islands[i], name))) {
			return i;
		}
	}
	return -1;
}

int **create_adjacency_matrix(t_bridge *list, char **islands, int islands_count) {

    // create adjacency matrix and fill with -1
	int** matrix = (int**)malloc((islands_count + 1) * sizeof(int*));
	for (int i = 0; i < islands_count; i++) {
		matrix[i] = (int*)malloc(islands_count * sizeof(int));
        for (int j = 0; j < islands_count; j++) {
            matrix[i][j] = -1;
        }
	}

    // fill adjacency matrix with bridges values
	for (t_bridge* temp = list; temp; temp = temp->next) {
		int p1 = island_number(islands, islands_count, temp->point1);
		int p2 = island_number(islands, islands_count, temp->point2);
		if (p1 >= 0 && p2 >= 0) {
			matrix[p1][p2] = temp->length;
			matrix[p2][p1] = temp->length;
		}
	}

	return matrix;
}

