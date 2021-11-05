#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {

	int islands_count = 0;
	int bridges_count = 0;
	char *str_from_file = errorhandler(argc, argv, &islands_count, &bridges_count);

	t_bridge *bridges = create_bridges(str_from_file);
	check_bridges(bridges, islands_count);
	
	char **islands = islands_list(bridges, islands_count);	
	int **adjacency_matrix = create_adjacency_matrix(bridges, islands, islands_count);

    find_and_print_paths(islands, adjacency_matrix, islands_count);

	for (; bridges; bridges = bridges->next) {
		mx_strdel(&(bridges->point1));
		mx_strdel(&(bridges->point2));
	}
	mx_strdel(&str_from_file);
    
	return 0;
}

