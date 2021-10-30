#include "../inc/libmx.h"

char* mx_replace_substr(const char* str, const char* sub, const char* replace) {
    int sum = mx_strlen(replace) - mx_strlen(sub);
    int len = mx_strlen(str) + mx_count_substr(str, sub) * sum;
    char* result = mx_strnew(len);
    bool status = false;

    if (!str || !sub || !replace || mx_strlen(str) <= mx_strlen(sub)) {
        return NULL;
    }

    for (int i = 0; i < len; i++, str++) {
        status = false;
        if (!mx_strncmp((char*)str, (char*)sub, mx_strlen(sub))) {
            str += mx_strlen(sub);

            for (int j = 0; j < mx_strlen(replace); i++, j++) {
                result[i] = replace[j];
            }

            status = true;
        }
        result[i] = *str;
        if (status) {
            str--;
            i--;
        }
    }

    return result;
}

