#include "pathfinder.h"

bool mx_compare_paths(t_node* node1, t_node* node2, t_node** res_temp) {
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

