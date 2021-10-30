#include "pathfinder.h"

int main(int argc, char *argv[]) {

	int islands_count = 0;
	int bridges_count = 0;
	char *str_from_file = errorhandler(argc, argv, &islands_count, &bridges_count);

	t_bridge *bridges = create_bridges(str_from_file);
	check_bridges(bridges, islands_count);
	
	char **islands = islands_list(bridges, islands_count);	
	int **matrix = create_adjacency_matrix(bridges, islands, islands_count);

    int i = 0;
    for (int islands_i = 0; islands_i < islands_count; islands_i++) {
        for (int islands_j = 0; islands_j < islands_count; islands_j++) {
            if (islands_i != islands_j) {
                t_node** a = find_path(matrix, islands, islands_i, islands_j);
                for (int j = 0; a[j] != NULL; j++) {
                    i++;
                }
            }
        }
    }

    t_node** res_paths = (t_node**)malloc((i + 1) * sizeof(t_node*));
    for (int j = 0; j < i; j++) {
        res_paths[j] = NULL;
    }

    int ii = 0;
    for (int islands_i = 0; islands_i < islands_count; islands_i++) {
        for (int islands_j = 0; islands_j < islands_count; islands_j++) {
            if (islands_i != islands_j) {
                t_node** a = find_path(matrix, islands, islands_i, islands_j);
                for (int j = 0; a[j] != NULL; j++) {
                    res_paths[ii] = (t_node*)malloc(sizeof(t_node));
                    res_paths[ii] = a[j];
                    ii++;
                }
            }
        }
    }

	print_result(res_paths, i, islands);

	for (; bridges; bridges = bridges->next) {
		mx_strdel(&(bridges->point1));
		mx_strdel(&(bridges->point2));
	}
	mx_strdel(&str_from_file);
	return 0;
}

