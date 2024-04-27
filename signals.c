#include "signals.h"
#include "header.h"
#include "history.h"
#include "prompt.h"
#include "jobs.h"

void SIGINT_HANDLER(int signum)
{
    pid_t pid = getpid();
    if (pid < 0)
    {
        perror(ERROR);
        return;
    }
    else if (is_fg == -1)
        return;
    else if (pid != SHELL_PID)
    {
        remove_node(pid);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\n");
        fflush(stdout);
        prompt();
      
    }
}
void SIGCHILD_HANDLER(int signum)
{
    int child_status;

    pid_t child_pid = waitpid(-1, &child_status, WNOHANG | WUNTRACED);
    if (child_pid >= 0)
    {
        jobs *proc = get_data_by_pid(child_pid);
        if (proc != NULL)
        {

            if (WEXITSTATUS(child_status) == 0 && WIFEXITED(child_status))
            {
                fprintf(stderr, PROMPT "\nPROCESS %s WITH PID : %d EXITED NORMALLY \n" RESET, proc->proc_name, child_pid);
                remove_node(proc->proc_pid);
            }
            else if (WIFSTOPPED(child_status))
            {
                fprintf(stderr, ERROR "\nPROCESS %s WITH PID : %d STOPPED AFTER RECIEVING SIGNAL \n" RESET, proc->proc_name, child_pid);
            }
            else if (WIFSIGNALED(child_status))
            {
                fprintf(stderr, ERROR "\nPROCESS %s WITH PID : %d EXITED AFTER RECIEVING SIGNAL \n" RESET, proc->proc_name, child_pid);
                remove_node(proc->proc_pid);
            }
            else
            {
                fprintf(stderr, ERROR "\nPROCESS %s WITH PID : %d EXITED ABNORMALLY \n" RESET, proc->proc_name, child_pid);
                remove_node(proc->proc_pid);
            }
            fflush(stderr);
            prompt();
            fflush(stdout);
        }
    }
    return;
}

void SIGTSTP_HANDLER(int signum)
{
    pid_t pid = getpid();
    if (pid < 0)
    {
        perror(ERROR);
        return;
    }
    if (is_fg == -1)
        return;
    if (pid != SHELL_PID)
    {
        int flag = kill(pid, SIGTSTP);
        if (flag < 0)
        {
            perror(ERROR);
        }
    }
    else
        printf("\n");
}
void sig(int job_no, int sig_num)
{
    jobs *tmp = get_data_by_id(job_no);
    if (tmp == NULL)
    {
        fprintf(stderr, ERROR "NO PROCESS EXISTS WITH GIVEN job id!!!\n" RESET);
        return;
    }
    print_YELLOW();
    printf("signaling proc %s : %d\n", tmp->proc_name, tmp->proc_pid);
    int flag = kill(tmp->proc_pid, sig_num);
    if (flag < 0)
    {
        perror(ERROR "sig ");
    }

}
void execute_sig(int arg_count, char *argument[])
{
    if (arg_count != 3)
    {
        fprintf(stderr, ERROR "INVALID NUMBER OF ARGUMENTS , syntax - sig <job_number> <signal_number>\n" RESET);
        return;
    }
    int job_no = atoi(argument[1]);
    if (job_no <= 0)
    {
        fprintf(stderr, ERROR "ENTER A POSITIVE INTEGER FOR JOB NUMBER , syntax - sig <job_number> <signal_number>\n" RESET);
        return;
    }
    int sig_no = atoi(argument[2]);
    if (sig_no <= 0)
    {
        fprintf(stderr, ERROR "ENTER A POSITIVE INTEGER FOR SIGNAL NUMBER , syntax - sig <job_number> <signal_number>\n" RESET);
        return;
    }
    sig(job_no, sig_no);
}
