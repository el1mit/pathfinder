#include "pathfinder.h"

//static int island_number(char** islands, int size, char* name) {
//	for (int i = 0; i < size; i++) {
//		if (!islands[i]) {
//			return -1;
//		}
//		if (!(mx_strcmp(islands[i], name))) {
//			return i;
//		}
//	}
//	return -1;
//}
//
//int **create_adjacency_matrix(t_bridge *list, char **islands, int islands_count) {
//
//	int** matrix = (int**)malloc((islands_count + 1) * sizeof(int*));
//	for (int j = 0; j < islands_count; j++) {
//		matrix[j] = (int*)malloc(islands_count * sizeof(int));
//		for (int k = 0; k < islands_count; k++) {
//			matrix[j][k] = -1;
//		}
//	}
//
//	for (t_bridge* temp = list; temp; temp = temp->next) {
//		int p1 = island_number(islands, islands_count, temp->point1);
//		int p2 = island_number(islands, islands_count, temp->point2);
//		if (p1 >= 0 && p2 >= 0) {
//			matrix[p1][p2] = temp->length;
//			matrix[p2][p1] = temp->length;
//		}
//	}
//
//	return matrix;
//}

static int mx_get_island_index(char** islands, char* island) {
    for (int i = 0; islands[i] != NULL; i++) {
        if (mx_strcmp(islands[i], island) == 0) {
            return i;
        }
    }
    return -1;
}

int** create_adjacency_matrix(char** islands, char** arr, int size) {
    int** res = (int**)malloc((size + 1) * sizeof(int*));
    for (int i = 0; i < size; i++) {
        res[i] = (int*)malloc(size * sizeof(int));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            res[i][j] = -1;
        }
    }
    int arr_size = 0;
    for (; arr[arr_size] != NULL; arr_size++);

    for (int i = 0; i < arr_size; i += 3) {
        int index1 = mx_get_island_index(islands, arr[i]);
        int index2 = mx_get_island_index(islands, arr[i + 1]);
        res[index1][index2] = mx_atoi(arr[i + 2]);
        res[index2][index1] = mx_atoi(arr[i + 2]);
    }

    return res;
}

