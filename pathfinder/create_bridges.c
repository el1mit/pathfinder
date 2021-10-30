#include "pathfinder.h"

static t_bridge* mx_create_bridge(char *island1, char *island2, int length) {
    if (!island1 || !island2) {
        return NULL;
    }
    
    t_bridge* node = NULL;

    node = (t_bridge*)malloc(sizeof(t_bridge));
    if (!node) {
        return NULL;
    }

    node->point1 = island1;
    node->point2 = island2;
    node->length = length;
    node->next = NULL;
    return node;
}

static void mx_push_back_bridge(t_bridge **list, char *island1, char *island2, int length) {
    t_bridge* back = mx_create_bridge(island1, island2, length);
    t_bridge* temp = NULL;

    if (!list || !(*list)) {
        *list = back;
    }
    else {
        temp = *list;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = back;
    }
}

t_bridge *create_bridges(char *file) {
    char **lines = mx_strsplit(file, '\n');
    int lines_count = 0;
    t_bridge *bridges = NULL;
    char *island1 = NULL, *island2 = NULL, *lenght = NULL;

    while (lines[lines_count]) {
        lines_count++;
    }

    // parsing file into linked list
    for (int n = 1, i = 0, count = 0; n < lines_count; n++) {
        i = 0;
        count = 0;

        while (mx_isalpha(lines[n][i])) {
            count++;
            i++;
        }
        island1 = mx_strncpy(mx_strnew(count), &lines[n][i - count], count);
        count = 0;
        i++;

        while (mx_isalpha(lines[n][i])) {
            count++;
            i++;
        }
        island2 = mx_strncpy(mx_strnew(count), &lines[n][i - count], count);
        count = 0;
        i++;

        while (mx_isdigit(lines[n][i])) {
            count++;
            i++;
        }
        lenght = mx_strncpy(mx_strnew(count) , &lines[n][i - count], count);

        mx_push_back_bridge(&bridges, island1, island2, mx_atoi(lenght));
    }

    return bridges;
}

