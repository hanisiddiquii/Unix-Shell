#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void execute_find(int arg_count, char *argument[])
{
    if (arg_count != 2)
    {
        fprintf(stderr, "Usage: find <folder-name>\n");
        return;
    }

    char *folder_name = argument[1];

    DIR *dir = opendir("/");
    if (dir == NULL)
    {
        perror("Error opening root directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }

            char path[PATH_MAX];
            snprintf(path, sizeof(path), "/%s", entry->d_name);

            struct stat st;
            if (stat(path, &st) == -1)
            {
                perror("Error stat");
                continue;
            }

            if (S_ISDIR(st.st_mode))
            {
                if (strcmp(entry->d_name, folder_name) == 0)
                {
                    printf("%s\n", path);
                }

                // Recursively search in subdirectories
                execute_find_in_directory(path, folder_name);
            }
        }
    }

    closedir(dir);
}

void execute_find_in_directory(const char *dir_path, const char *folder_name)
{
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }

            char path[PATH_MAX];
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

            struct stat st;
            if (stat(path, &st) == -1)
            {
                perror("Error stat");
                continue;
            }

            if (S_ISDIR(st.st_mode))
            {
                if (strcmp(entry->d_name, folder_name) == 0)
                {
                    printf("%s\n", path);
                }

                // Recursively search in subdirectories
                execute_find_in_directory(path, folder_name);
            }
        }
    }

    closedir(dir);
}

