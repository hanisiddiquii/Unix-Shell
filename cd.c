#include "cd.h"
#include "header.h"
#include "helper.h"

void execute_cd(int arg_count, char **argument)
{
    if (arg_count == 1)
        cd("~");
    else if (arg_count == 2)
    {
     
        cd(argument[1]);
    }
    else
    {
        fprintf(stderr, ERROR "TOO MANY ARGUMENTS FOR cd, ONLY ONE ARGUMENT REQUIRED\n" RESET);
    }
}
// runs on only one input
void cd(char *path)
{
    char *final_dir = (char *)malloc(name_len * sizeof(char));
    if (strcmp(path, "") == 0)
        strcpy(final_dir, cwd_path);
    else if (path[0] == '~')
    {
        strcpy(final_dir, get_home_dir_path(path));
    }
    else if (strcmp(path, "-") == 0)
    {
        if (strcmp(last_dir_visited, "") == 0)
        {
            fprintf(stderr, ERROR "PWD DIDN'T CHANGED\n" RESET);
            free(final_dir);
            return;
        }
        else
        {
            printf("%s\n", last_dir_visited);
            strcpy(final_dir, last_dir_visited);
        }
    }
    else
        strcpy(final_dir, path);
    int flag = chdir(final_dir);
    if (flag != 0)
    {
        perror(ERROR "DIRECTORY CAN'T BE CHANGED ");
        print_RESET();
    }
    getcwd(last_dir_visited, name_len);
    free(final_dir);
}
