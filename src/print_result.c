#include "../inc/pathfinder.h"

static char** from_to(t_node* node) {
    char** result = (char**)malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        result[i] = NULL;
    }

    t_node* temp = node;
    result[0] = mx_strdup(node->name);
    for (int i = 0; temp->parent != NULL; i++) {
        temp = temp->parent;
    }
    result[1] = mx_strdup(temp->name);
    return result;
}

static void print_from_to(t_node *node) {
    char **names = from_to(node);
    mx_printstr("Path: ");
    mx_printstr(names[1]);
    mx_printstr(" -> ");
    mx_printstr(names[0]);
    mx_printchar('\n');
}

static void print_route(t_node *node) {
    int size = 0;
    t_node* temp = node;
    for (; temp != NULL; size++) {
        temp = temp->parent;
    }

    temp = node;
    char** names_arr = (char**)malloc(size * sizeof(char*));
    for (int i = 0; temp != NULL; i++) {
        names_arr[i] = mx_strdup(temp->name);
        temp = temp->parent;
    }

    mx_printstr("Route: ");
    for (int i = size - 1; i >= 0; i--) {
        mx_printstr(names_arr[i]);
        if (i - 1 >= 0) {
            mx_printstr(" -> ");
        }
    }
}


static void print_distance(t_node *node) {
    int size = 0;
    t_node* temp = node;
    for (; temp != NULL; size++) {
        temp = temp->parent;
    }
    
    if (size == 2) {
        mx_printstr("\nDistance: ");
        mx_printint(node->len_to_parent);
    }
    else {
        mx_printstr("\nDistance: ");

        temp = node;
        int* int_arr = (int*)malloc(size * sizeof(int));
        for (int i = 0; temp != NULL; i++) {
            int_arr[i] = temp->len_to_parent;
            temp = temp->parent;
        }

        for (int i = size - 2; i >= 0; i--) {
            mx_printint(int_arr[i]);
            if (i - 1 >= 0) {
                mx_printstr(" + ");
            }
        }
        mx_printstr(" = ");
        int sum = 0;
        for (int i = 0; i < size - 1; i++) {
            sum += int_arr[i];
        }
        mx_printint(sum);
    }
}

static void print_path(t_node* node) {
    mx_printstr("========================================\n");
    print_from_to(node);
    print_route(node);
    print_distance(node);
    mx_printstr("\n========================================\n");
}


void print_result(t_node** res, int size, char** islands) {
    t_node** result = (t_node**)malloc(size * sizeof(t_node*));
    for (int i = 0; i < size; i++) {
        result[i] = NULL;
    }

    int h = 0;
    bool add = true;

    for (int i = 0; res[i] != NULL; i++) {
        for (int j = 0; res[j] != NULL; j++) {
            t_node* temp = res[i];
            t_node* temp2 = res[j];

            if (i != j) {
                if (!cmppaths(temp, temp2, result)) {
                    add = false;
                    break;
                }
            }
        }
        if (add == true) {
            result[h] = res[i];
            h++;
        }
        add = true;
    }

    sort_paths(result, islands);
    for (int i = 0; result[i] != NULL; i++) {
        print_path(result[i]);
    }
}

