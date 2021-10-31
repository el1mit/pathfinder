#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "libmx.h"
#include <limits.h>

typedef struct s_node { 
    int to_parent;
    int all_way;
    char* name;
    struct s_node* parent;
}              t_node;

typedef struct s_queue {
    int priority;
    t_node* node;
    struct s_queue* next;
}              t_queue;

t_queue* newNode(t_node* node);
void push(t_queue** head, t_node* node);
void pop(t_queue** head);
int peek(t_queue** head);
int isEmpty(t_queue** head);

typedef struct s_bridge {
    char *point1;
    char *point2;
    int length;
    struct s_bridge *next;
}              t_bridge;


char *errorhandler(int argc, char* argv[], int *islands_count, int* bridges_count);
t_bridge *create_bridges(char *file);
void check_bridges(t_bridge* list, int received_count);
char **islands_list(t_bridge* bridges, int islands_count);
int **create_adjacency_matrix(t_bridge *list, char **islands, int islands_count);
t_node** find_path(int** arr, char** islands, int cur_x, int goal_x);
void print_result(t_node** res, int size, char** islands);

#endif

