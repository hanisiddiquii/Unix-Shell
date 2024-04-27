#include "header.h"
#include "find.h"
#include <dirent.h>

void search_directory(char *dir_path, char *file_name);

void execute_find(int arg_count, char *argument[])
{
    if (arg_count != 2)
    {
        fprintf(stderr, ERROR "Invalid number of arguments. Usage: find <file_name>\n" RESET);
        return;
    }

    char *file_name = argument[1];
    search_directory(".", file_name);
}

void search_directory(char *dir_path, char *file_name)
{
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        perror(ERROR "Unable to open directory" RESET);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (entry->d_type == DT_DIR)
        {
            search_directory(full_path, file_name);
        }
        else if (entry->d_type == DT_REG && strcmp(entry->d_name, file_name) == 0)
        {
            printf("%s\n", full_path);
        }
    }

    closedir(dir);
}

