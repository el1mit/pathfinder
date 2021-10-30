#include "pathfinder.h"

static int mx_get_last_char_index(const char* str, char c) {
    if (str == NULL) return -2;
    for (int i = mx_strlen(str) - 1; i >= 0; i--) {
        if (str[i] == c) return i;
    }
    return -1;
}

static void mx_check_dup(char** arr_str, int size) {
    for (int i = 0; i < size; i += 3) {
        if (mx_strcmp(arr_str[i], arr_str[i + 1]) == 0) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa((i / 3) + 2));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }

    for (int i = 0; i < size; i += 3) {
        for (int j = i + 3; j < size; j += 3) {
            if ((mx_strcmp(arr_str[i], arr_str[j]) == 0 && mx_strcmp(arr_str[i + 1], arr_str[j + 1]) == 0)
                || (mx_strcmp(arr_str[i + 1], arr_str[j]) == 0 && mx_strcmp(arr_str[i], arr_str[j + 1]) == 0)) {
                mx_printerr("error: duplicate bridges\n");
                exit(0);
            }
        }
    }
}

static void mx_check_str(char* str, int line_num) {
    int index = mx_get_last_char_index(str, '-');
    if (index <= 0) {
        mx_printerr("error: line ");
        mx_printerr(mx_itoa(line_num));
        mx_printerr(" is not valid\n");
        exit(0);
    }
    for (int i = 0; i < index; i++) {
        if (!mx_isalpha(*str)) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(line_num));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        str++;
    }
    str++;

    index = mx_get_last_char_index(str, ',');
    if (index <= 0) {
        mx_printerr("error: line ");
        mx_printerr(mx_itoa(line_num));
        mx_printerr(" is not valid\n");
        exit(0);
    }
    for (int i = 0; i < index; i++) {
        if (!mx_isalpha(*str)) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(line_num));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        str++;
    }
    str++;

    for (; *str != '\0'; str++) {
        if (!mx_isdigit(*str)) {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(line_num));
            mx_printerr(" is not valid\n");
            exit(0);
        }
    }
}

char** mx_parse_file(char* str, int size) {
    if (str[0] == '\n') {
        mx_printerr("error: line 1 is not valid\n");
        exit(0);
    }

    int temp_lines = 1;
    for (int i = 0; str[i + 1] != '\0'; i++) {
        if (mx_isspace(str[i]) && mx_isspace(str[i + 1])) {
            if (str[i] == '\n')
                temp_lines++;
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(temp_lines));
            mx_printerr(" is not valid\n");
            exit(0);
        }
        else if (str[i] == '\n') {
            temp_lines++;
        }
    }

    for (int i = 0; *str != '\n'; i++) {
        if (!mx_isdigit(*str)) {
            mx_printerr("error: line 1 is not valid\n");
            exit(0);
        }
        str++;
    }


    int lin_num = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n')
            lin_num++;
    }

    str = mx_strtrim(str);

    char** str_res = (char**)malloc((3 * lin_num + 1) * sizeof(char*));
    for (int i = 0; i < (3 * lin_num + 1); i++) {
        str_res[i] = NULL;
    }

    char** arr_str = mx_strsplit(str, '\n');

    int iter = 0;
    int line_num = 1;
    for (int i = 0; arr_str[i] != NULL; i++) {

        line_num++;
        char* temp = mx_strtrim(arr_str[i]);
        mx_check_str(temp, line_num);

        temp = mx_strdup(arr_str[i]);
        temp = mx_strtrim(temp);
        char** arr_temp = mx_strsplit(temp, '-');

        str_res[iter] = mx_strdup(arr_temp[0]);
        iter++;
        str_res[iter] = mx_strdup(mx_strsplit(arr_temp[1], ',')[0]);
        iter++;
        str_res[iter] = mx_strdup(mx_strsplit(arr_temp[1], ',')[1]);
        iter++;

    }
    mx_check_dup(str_res, iter);
    char** islands = list_of_islands(str_res);
    int islands_size = 0;
    for (int i = 0; islands[i] != NULL; i++) {
        islands_size++;
    }
    if (size != islands_size) {
        mx_printerr("error: invalid number of islands\n");
        exit(0);
    }
    for (int i = 0; islands[i] != NULL; i++) {
        free(islands[i]);
    }
    free(islands);

    return str_res;
}

