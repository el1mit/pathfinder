#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include <limits.h>

//received_from_file
typedef struct s_bridge {
    char *point1;
    char *point2;
    int length;
    struct s_bridge *next;
}              t_bridge;

//graph
typedef struct s_node { 
    int len_to_parent;
    int all_way;
    char* name;
    struct s_node* parent;
}              t_node;

//handling errors
char *errorhandler(int argc, char* argv[], int *islands_count, int* bridges_count);
t_bridge *create_bridges(char *file);
void check_bridges(t_bridge* list, int received_count);

//pathfinding
char **islands_list(t_bridge* bridges, int islands_count);
int **create_adjacency_matrix(t_bridge *list, char **islands, int islands_count);
void find_and_print_paths(char **islands, int **adjacency_matrix, int islands_count);

//output
void print_result(t_node** res, int size, char** islands);
bool mx_compare_paths(t_node* node1, t_node* node2, t_node** res_temp);
void sort_paths(t_node** paths, char** islands);

//queue
typedef struct s_queue {
    t_node* node;
    struct s_queue* next;
    int priority;
}              t_queue;

t_queue* newNode(t_node* node);
void push(t_queue** head, t_node* node);
void pop(t_queue** head);
int peek(t_queue** head);
int isEmpty(t_queue** head);

#endif

