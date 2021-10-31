#include "pathfinder.h"

static char** first_last_name(t_node* node) {
    char** names = (char**)malloc(2 * sizeof(char*));
    for (int i = 0; i < 2; i++) {
        names[i] = NULL;
    }

    t_node* temp = node;
    names[0] = mx_strdup(node->name);
    for (int i = 0; temp->parent != NULL; i++) {
        temp = temp->parent;
    }
    names[1] = mx_strdup(temp->name);
    return names;
}


static char** mx_get_names(t_node* paths) {
    int i = 0;
    t_node* path = paths;
    for (; path != NULL; i++) {
        path = path->parent;
    }

    char** names = (char**)malloc((i + 1) * sizeof(char*));
    for (int j = 0; j <= i; j++) {
        names[j] = NULL;
    }

    path = paths;
    for (int j = 0; j < i; j++) {
        names[j] = mx_strdup(path->name);
        path = path->parent;
    }

    for (int j = 0; j < i / 2; j++) {
        char* temp = names[j];
        names[j] = names[i - 1 - j];
        names[i - 1 - j] = temp;
    }

    return names;
}

static void print_node(t_node* node) {
    mx_printstr("========================================\n");

    mx_printstr("Path: ");
    mx_printstr(first_last_name(node)[1]);
    mx_printstr(" -> ");
    mx_printstr(first_last_name(node)[0]);
    mx_printchar('\n');

    int arr_size = 0;
    t_node* temp = node;
    for (; temp != NULL; arr_size++) {
        temp = temp->parent;
    }

    temp = node;
    char** names_arr = (char**)malloc(arr_size * sizeof(char*));
    for (int i = 0; temp != NULL; i++) {
        names_arr[i] = mx_strdup(temp->name);
        temp = temp->parent;
    }

    mx_printstr("Route: ");
    for (int i = arr_size - 1; i >= 0; i--) {
        mx_printstr(names_arr[i]);
        if (i - 1 >= 0) {
            mx_printstr(" -> ");
        }
    }

    if (arr_size == 2) {
        mx_printstr("\nDistance: ");
        mx_printint(node->to_parent);
    }
    else {
        mx_printstr("\nDistance: ");

        temp = node;
        int* int_arr = (int*)malloc(arr_size * sizeof(int));
        for (int i = 0; temp != NULL; i++) {
            int_arr[i] = temp->to_parent;
            temp = temp->parent;
        }

        for (int i = arr_size - 2; i >= 0; i--) {
            mx_printint(int_arr[i]);
            if (i - 1 >= 0) {
                mx_printstr(" + ");
            }
        }
        mx_printstr(" = ");
        int sum = 0;
        for (int i = 0; i < arr_size - 1; i++) {
            sum += int_arr[i];
        }
        mx_printint(sum);
    }
    mx_printstr("\n========================================\n");
}

static void sort_paths(t_node** paths, char** islands) {
    for (int i = 0; paths[i + 1] != NULL; i++) {

        char** paths1 = first_last_name(paths[i]);
        char** paths2 = first_last_name(paths[i + 1]);
        if (mx_strcmp(paths1[1], paths2[1]) == 0
         && mx_strcmp(paths1[0], paths2[0]) == 0) {

            t_node* temp1 = paths[i];
            t_node* temp2 = paths[i + 1];
            char** names1 = mx_get_names(temp1);
            char** names2 = mx_get_names(temp2);
            int index1 = 0;
            int index2 = 0;
            for (int b = 0; names1[b] != NULL && names2[b] != NULL; b++) {
                if (mx_strcmp(names1[b], names2[b]) != 0) {

                    for (int j = 0; islands[j] != NULL; j++) {
                        if (mx_strcmp(islands[j], names1[b]) == 0) {
                            break;
                        }
                        index1++;
                    }

                    for (int j = 0; islands[j] != NULL; j++) {
                        if (mx_strcmp(islands[j], names2[b]) == 0) {
                            break;
                        }
                        index2++;
                    }

                    if (index1 != index2) {
                        break;
                    }
                }
            }
            if (index1 > index2) {
                t_node* temp = paths[i];
                paths[i] = paths[i + 1];
                paths[i + 1] = temp;
                i = 0;
            }

        }
    }
}

static bool mx_compare_paths(t_node* node1, t_node* node2, t_node** res_temp) {
    int length1 = 0;
    int length2 = 0;
    t_node* temp_node1 = node1;
    for (int i = 0; temp_node1->parent != NULL; i++) {
        length1 += temp_node1->to_parent;
        temp_node1 = temp_node1->parent;
    }

    t_node* temp_node2 = node2;
    for (int i = 0; temp_node2->parent != NULL; i++) {
        length2 += temp_node2->to_parent;
        temp_node2 = temp_node2->parent;
    }

    temp_node1 = node1;
    temp_node2 = node2;
    char** temp_name1 = first_last_name(temp_node1);
    char** temp_name2 = first_last_name(temp_node2);

    if ((mx_strcmp(temp_name1[0], temp_name2[0]) == 0 
      && mx_strcmp(temp_name1[1], temp_name2[1]) == 0)) {
        if (length1 > length2) {
            return false;
        }
    }
    else if ((mx_strcmp(temp_name1[1], temp_name2[0]) == 0 
           && mx_strcmp(temp_name1[0], temp_name2[1]) == 0)) {
        if (res_temp == NULL) {
            if (length1 >= length2) {
                return false;
            }
            return true;
        }
        for (int i = 0; res_temp[i] != NULL; i++) {
            t_node* temp = res_temp[i];
            if (length1 > length2 || !mx_compare_paths(node1, temp, NULL)) {
                return false;
            }
        }
    }

    return true;
}

void print_result(t_node** res, int size, char** islands) {

    t_node** res_temp = (t_node**)malloc(size * sizeof(t_node*));
    for (int i = 0; i < size; i++) {
        res_temp[i] = NULL;
    }

    int h = 0;
    bool add = true;

    for (int i = 0; res[i] != NULL; i++) {
        for (int j = 0; res[j] != NULL; j++) {
            t_node* temp_2 = res[j];
            t_node* temp = res[i];
            if (i != j) {
                if (!mx_compare_paths(temp, temp_2, res_temp)) {
                    add = false;
                    break;
                }
            }
        }
        if (add == true) {
            res_temp[h] = res[i];
            h++;
        }
        add = true;
    }

    sort_paths(res_temp, islands);
    for (int i = 0; res_temp[i] != NULL; i++) {
        print_node(res_temp[i]);
    }
}

