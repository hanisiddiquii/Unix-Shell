#include "header.h"
#include "system_command.h"
#include <signal.h>
#include "jobs.h"

void execute_sys_command(int arg_count, char *argument[])
{
    bool is_background_proc = false;
    if (arg_count == 0)
    {
        perror(ERROR "Invalid Argument Called, give atleast one command to execute\n");
        return;
    }
    if (arg_count >= 2 && strcmp(argument[arg_count - 1], "&") == 0)
    {
        is_background_proc = true;
        argument[arg_count - 1] = NULL;
        arg_count--;
    }
    else if (arg_count >= 1 && argument[arg_count - 1][strlen(argument[arg_count - 1]) - 1] == '&')
    {
        is_background_proc = true;
        argument[arg_count - 1][strlen(argument[arg_count - 1]) - 1] = '\0';
        argument[arg_count] = NULL;
    }
    // system command run in foreground
    if (is_background_proc == false)
    {
        argument[arg_count] = NULL;
        pid_t proc_fork = fork();
        if (proc_fork < 0)
        {
            perror(ERROR "Failed To Execute Command ");
            return;
        }
        else if (proc_fork == 0)
        {
            // child
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            setpgid(0, 0);
            // set the child process group id to child ka pid ( creating a new group )
            int exec_flag = execvp(argument[0], argument);
            if (exec_flag < 0)
            {
                perror(ERROR "Failed To Execute Command ");
                fprintf(stderr, RESET);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // control passed on to the child
            dup2(copy_stdin_fileno, 0);
            dup2(copy_stdout_fileno, 1);
            signal(SIGTTIN, SIG_IGN);
            // stop the terminal input for the parent
            signal(SIGTTOU, SIG_IGN);
            // here we are stopping the terminal output to the terminal for the parent
            int st_wait;
            // set the group id of parent process as the pid of the parent, the child sets it's group as child ka pid
            setpgid(proc_fork, 0);
            // for setting the terminal display permission to the parent process
            tcsetpgrp(STDIN_FILENO, proc_fork);

            waitpid(proc_fork, &st_wait, WUNTRACED); 
            pid_t pgid_parent = getpgrp();
            tcsetpgrp(STDIN_FILENO, pgid_parent);
            //input
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);
            
            if (WIFSTOPPED(st_wait))
            {
                add_node(argument[0], proc_fork);
                printf("Process %s with pid %d stopped .... \n", argument[0], proc_fork);
            }
        }
    }
    else
    {
        // background process hoga
        // no need for backgrounfd to give permission for read and write from parent
        pid_t proc_fork = fork();
        if (proc_fork < 0)
        {
            perror(ERROR "Failed To Execute Command");
            fprintf(stderr, RESET);
            return;
        }
        else if (proc_fork == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            setpgid(0, 0);
            int exec_flag = execvp(argument[0], argument);
            if (exec_flag < 0)
            {
                perror(ERROR "Failed To Execute Command");
                fprintf(stderr, RESET);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // in parent
            // no need to wait
            dup2(copy_stdin_fileno, 0);
            dup2(copy_stdout_fileno, 1);

            char *command = (char *)malloc(sizeof(char) * name_len);
            strcpy(command, argument[0]);
            for (int i = 1; i < arg_count && argument[i] != NULL; i++)
            {
                strcat(command, " ");
                strcat(command, argument[i]);
            }
            add_node(command, proc_fork);
            free(command);
            pid_t pgid_parent = getpgrp();
            setpgid(proc_fork, 0);
            print_WHITE();
            printf("%d\n", proc_fork);
            print_RESET();
            tcsetpgrp(STDIN_FILENO, pgid_parent);
        }
    }
}
