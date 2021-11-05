#include "../inc/pathfinder.h"

static t_node* new_node(int len_to_parent, int all_dist, char* name) {
    t_node* temp = (t_node*)malloc(sizeof(t_node));
    temp->len_to_parent = len_to_parent;
    temp->all_dist = all_dist;
    temp->name = mx_strdup(name);
    temp->parent = NULL;

    return temp;
}

static t_node** generate_successors(int** arr, t_node* parent, char** islands, int islands_num) {
    int index = 0;
    for (; mx_strcmp(islands[index], parent->name) != 0; index++);

    t_node** successors = (t_node**)malloc((islands_num) * sizeof(t_node*));
    for (int i = 0; i < islands_num; i++) {
        successors[i] = (t_node*)malloc(sizeof(t_node));
        successors[i] = NULL;
    }

    for (int i = 0; i < islands_num; i++) {
        if (i != index && arr[index][i] != -1 && parent != NULL) {
            t_node* temp = parent;
            bool was = false;
            int j = 0;
            while (temp != NULL) {

                if (mx_strcmp(temp->name, islands[i]) == 0 || j > islands_num) {
                    was = true;
                    break;
                }
                temp = temp->parent;
                j++;
            }
            if (j > islands_num) {
                break;
            }
            if (was == false)
                successors[i] = new_node(arr[index][i], parent->all_dist + arr[index][i], islands[i]);
        }
    }

    int lenght = 0;
    for (int i = 0; i < islands_num; i++) {
        if (successors[i] != NULL) {
            lenght++;
        }
    }

    t_node** successors_res = (t_node**)malloc((lenght + 1) * sizeof(t_node*));
    for (int i = 0; i < lenght + 1; i++)
        successors_res[i] = NULL;

    lenght = 0;
    for (int i = 0; i < islands_num; i++) {
        if (successors[i] != NULL) {
            successors_res[lenght] = (t_node*)malloc(sizeof(t_node));
            successors_res[lenght] = successors[i];
            lenght++;
        }
    }

    return successors_res;
}

static bool is_in_open_queue(t_queue *open_queue, t_node **successors, int index) {
    while (open_queue != NULL) {
        if (mx_strcmp(open_queue->node->name, successors[index]->name) == 0) {
            if (open_queue->node->all_dist < successors[index]->all_dist) {
                return true;
            }
        }
        open_queue = open_queue->next;
    }
    return false;
}

static bool is_in_close_queue(t_queue *close_queue, t_node **successors, int index) {
    while (close_queue != NULL) {
        if (mx_strcmp(close_queue->node->name, successors[index]->name) == 0) {
            if (close_queue->node->all_dist < successors[index]->all_dist) {
                return true;
            }
        }
        close_queue = close_queue->next;
    }
    return false;

}

// A* algorithm from https://www.geeksforgeeks.org/a-search-algorithm/
static t_node** a_star(int** matrix, char** islands, int islands_num, int from, int to) {
    
    t_node* p_node = new_node(0, 0, islands[from]);    
    t_queue* open_queue = newNode(p_node);
    t_queue* close_queue = newNode(p_node);

    t_node** paths = (t_node**)malloc((islands_num * islands_num) * sizeof(t_node*));
    for (int i = 0; i < islands_num; i++) {
        paths[i] = (t_node*)malloc(sizeof(t_node));
        paths[i] = NULL;
    }

    int paths_index = 0;
    int check = 0;

    while (!isEmpty(&open_queue)) {
        check++;
        p_node = open_queue->node;
        pop(&open_queue);

        t_node* temp = p_node;
        int j = 0;
        for (; temp->parent != NULL; j++) {
            if (j > islands_num) {
                break;
            }
            temp = temp->parent;
        }
        if (j >= islands_num) {
            continue;
        }

        bool in_islands = false;
        for (int i = 0; i < islands_num; i++) {
            if (mx_strcmp(p_node->name, islands[i]) == 0) {
                in_islands = true;
            }
        }
        if (in_islands == false) {
            continue;
        }

        t_node** successors = generate_successors(matrix, p_node, islands, islands_num);
        for (int i = 0; successors[i] != NULL; i++) {
            successors[i]->parent = p_node;
        }

        for (int i = 0; successors[i] != NULL; i++) {
            if (mx_strcmp(successors[i]->name, islands[to]) == 0) {
                paths[paths_index] = successors[i];
                paths_index++;
            }

            if (!(is_in_open_queue(open_queue, successors, i)) 
             && !(is_in_close_queue(close_queue, successors, i))) {
                push(&open_queue, successors[i]);
                push(&close_queue, successors[i]);
            }
        }
    }
    return paths;
}

void find_and_print_paths(char **islands, int **adjacency_matrix, int islands_count) {
    int counter = 0;
    for (int i = 0; i < islands_count; i++) {
        for (int j = 0; j < islands_count; j++) {
            if (i != j) {
                t_node** a = a_star(adjacency_matrix, islands, islands_count, i, j);
                for (int k = 0; a[k] != NULL; k++) {
                    counter++;
                }
            }
        }
    }

    t_node** result = (t_node**)malloc((counter + 1) * sizeof(t_node*));
    for (int i = 0; i < counter; i++) {
        result[i] = NULL;
    }

    for (int i = 0, n = 0; i < islands_count; i++) {
        for (int j = 0; j < islands_count; j++) {
            if (i != j) {
                t_node** a = a_star(adjacency_matrix, islands, islands_count, i, j);
                for (int k = 0; a[k] != NULL; k++) {
                    result[n] = (t_node*)malloc(sizeof(t_node));
                    result[n] = a[k];
                    n++;
                }
            }
        }
    }
    
    print_result(result, counter, islands);
}

