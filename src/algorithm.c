#include "pathfinder.h"

static t_node* new_node(int len_to_parent, int all_way, char* name) {
    t_node* temp = (t_node*)malloc(sizeof(t_node));
    temp->len_to_parent = len_to_parent;
    temp->all_way = all_way;
    temp->name = mx_strdup(name);
    temp->parent = NULL;

    return temp;
}

static t_node** generate_successors(int** arr, t_node* parent, char** islands, int islands_num) {
    int index = 0;
    for (; mx_strcmp(islands[index], parent->name) != 0; index++);
   
    // int islands_num = 0;
    // for (; islands[islands_num] != NULL; islands_num++);

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
                successors[i] = new_node(arr[index][i], parent->all_way + arr[index][i], islands[i]);
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

// A* algorithm from https://www.geeksforgeeks.org/a-search-algorithm/
static t_node** a_star(int** arr, char** islands, int islands_num, int from, int to) {
    
    t_node* way = new_node(0, 0, islands[from]);    
    t_queue* queue = newNode(way);
    t_queue* queue_close = newNode(way);

    // int islands_num = 0;
    // for (; islands[islands_num] != NULL; islands_num++);

    t_node** paths = (t_node**)malloc(mx_pow(islands_num, 2) * sizeof(t_node*));
    for (int i = 0; i < islands_num; i++) {
        paths[i] = (t_node*)malloc(sizeof(t_node));
        paths[i] = NULL;
    }

    int paths_index = 0;
    int check = 0;

    while (!isEmpty(&queue)) {
        check++;
        way = queue->node;
        pop(&queue);

        t_node* temp = way;
        int j = 0;
        for (; temp->parent != NULL; j++) {
            if (j > islands_num)
                break;
            temp = temp->parent;
        }
        if (j >= islands_num) {
            continue;
        }

        bool in_islands = false;
        for (int h = 0; h < islands_num; h++) {
            if (mx_strcmp(way->name, islands[h]) == 0) {
                in_islands = true;
            }
        }
        if (in_islands == false) {
            continue;
        }

        t_node** successors = generate_successors(arr, way, islands, islands_num);
        for (int i = 0; successors[i] != NULL; i++) {
            successors[i]->parent = way;
        }

        for (int i = 0; successors[i] != NULL; i++) {
            if (mx_strcmp(successors[i]->name, islands[to]) == 0) {
                paths[paths_index] = successors[i];
                paths_index++;
            }

            t_queue* temp_queue = queue;
            bool in_queue = false;
            while (temp_queue != NULL) {
                if (mx_strcmp(temp_queue->node->name, successors[i]->name) == 0) {
                    if (temp_queue->node->all_way < successors[i]->all_way) {
                        in_queue = true;
                        break;
                    }
                }
                temp_queue = temp_queue->next;
            }

            bool in_cose_queue = false;
            t_queue* queue_close_temp = queue_close;
            while (queue_close_temp != NULL) {
                if (mx_strcmp(queue_close_temp->node->name, successors[i]->name) == 0) {
                    if (queue_close_temp->node->all_way < successors[i]->all_way) {
                        in_cose_queue = true;
                        break;
                    }
                }
                queue_close_temp = queue_close_temp->next;
            }

            if (in_queue == false && in_cose_queue == false) {
                push(&queue, successors[i]);
                push(&queue_close, successors[i]);
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
    for (int i = 0; i < counter; j++) {
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

