#include "../inc/pathfinder.h"

char* errorhandler(int argc, char *argv[], int *islands_count, int *bridges_count) {
	// invalid number of arguments
	if (argc != 2) {
		mx_printerr("usage: ./pathfinder [filename]\n");
		exit(0);
	}

	// file doesnnt exist
	if (open(argv[1], O_RDONLY) < 0) {
		mx_printerr("error: file ");
		mx_printerr(argv[1]);
		mx_printerr(" does not exist\n");
		exit(0);
	}

	char* str_from_file = mx_file_to_str(argv[1]);

	// file is empty
	if (mx_strlen(str_from_file) == 0) {
		mx_printerr("error: file ");
		mx_printerr(argv[1]);
		mx_printerr(" is empty\n");
		exit(0);
	}

	char **lines = mx_strsplit(str_from_file, '\n');
	int lines_count = 0;

	while (lines[lines_count]) {
		lines_count++;
	}

	// line 1 is invalid
	for (int i = 0; lines[0][i] != '\0'; i++) {
		if (!(mx_isdigit(lines[0][i]))) {
			mx_printerr("error: line 1 is not valid\n");
			exit(0);
		}
	}

	*islands_count = mx_atoi(lines[0]);
	*bridges_count = lines_count - 1;

	// checking lines
	for (int n = 1, i = 0, copy_i = 0; n < lines_count; n++) {
		i = 0;
		copy_i = 0;

		while (mx_isalpha(lines[n][i])) {
			i++;
		}
		if (i == 0 || lines[n][i] != '-') {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(n + 1));
			mx_printerr(" is not valid\n");
			exit(0);
		}

		i++;
		copy_i = i;

		while (mx_isalpha(lines[n][copy_i])) {
			copy_i++;
		}
		if (copy_i - i == 0 || lines[n][copy_i] != ',') {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(n + 1));
			mx_printerr(" is not valid\n");
			exit(0);
		}

		copy_i++;
		i = copy_i;

		while (mx_isdigit(lines[n][copy_i])) {
			copy_i++;
		}
		if (copy_i - i == 0 || lines[n][copy_i] != '\0') {
			mx_printerr("error: line ");
			mx_printerr(mx_itoa(n + 1));
			mx_printerr(" is not valid\n");
			exit(0);
		}
	}

	char* file_str_copy = str_from_file;
	int i = 0;
	int len = 0;

	// checking spaces
	if (*file_str_copy == '\n') {
		mx_printerr("error: line 1 is not valid\n");
		exit(-1);
	}

	for (; *file_str_copy; file_str_copy++) {
		if (*file_str_copy == '\n' && *(file_str_copy + 1) == '\n') {
			for (; lines[i]; i++) {
				len = mx_strlen(lines[i]);

				if (mx_strncmp(file_str_copy - len, lines[i], mx_strlen(lines[i])) == 0) {
					mx_printerr("error: line ");
					mx_printerr(mx_itoa(i + 2));
					mx_printerr(" is not valid\n");
					exit(0);
				}
			}
		}
	}

	mx_del_strarr(&lines);
	return str_from_file;
}

