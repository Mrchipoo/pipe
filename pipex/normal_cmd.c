#include "pipex.h"


char    *run_normal(char **args, char **env)
{
    char    *cmd;
    int pid;
    int status;

    cmd = find_path(env, args[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
        execve(cmd, args, NULL);
    else
        wait(&status);
    return ("succes");
}