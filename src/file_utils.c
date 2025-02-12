#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../include/file_utils.h"

int file_exists(const char *filename) {
    if (access(filename, F_OK) != 0) {
        return 0;
    }
    return 1;
}

int delete_file(const char *filename) {
    if (remove(filename) != 0) {
        return -1;
    }
    return 0;
}

int is_file(const char *path) {
    size_t len = strlen(path);

    if (len < 4) {
        return 1;
    }

    if (path[len - 4] == '.') {
        return 0;
    }

    return 1;
}