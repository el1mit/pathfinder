#include "pathfinder.h"

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

static char** get_path_names(t_node* paths) {
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

void sort_paths(t_node** paths, char** islands) {
    for (int i = 0; paths[i + 1] != NULL; i++) {
        char** paths1 = from_to(paths[i]);
        char** paths2 = from_to(paths[i + 1]);

        if (mx_strcmp(paths1[1], paths2[1]) == 0
         && mx_strcmp(paths1[0], paths2[0]) == 0) {

            t_node* temp1 = paths[i];
            t_node* temp2 = paths[i + 1];
            char** names1 = get_path_names(temp1);
            char** names2 = get_path_names(temp2);
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

