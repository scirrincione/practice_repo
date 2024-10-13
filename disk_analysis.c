#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

/*  This program was created using Claude AI*/

long long calculate_size(const char *path) {
    struct stat st;
    if (lstat(path, &st) == -1) {
        perror("lstat");
        return 0;
    }

    if (!S_ISDIR(st.st_mode)) {
        return st.st_size;
    }

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return 0;
    }

    long long total_size = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        total_size += calculate_size(full_path);
    }

    closedir(dir);
    return total_size;
}

void print_size(const char *path, long long size) {
    const char *units[] = {"B", "KB", "MB", "GB", "TB"};
    int unit_index = 0;
    double formatted_size = size;

    while (formatted_size >= 1024 && unit_index < 4) {
        formatted_size /= 1024;
        unit_index++;
    }

    printf("%-50s %.2f %s\n", path, formatted_size, units[unit_index]);
}

void analyze_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        long long size = calculate_size(full_path);
        print_size(full_path, size);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    analyze_directory(argv[1]);
    return 0;
}