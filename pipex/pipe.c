#include "pipex.h"

char    *multi_pipe(char *infile, char *outfile, char **args1, char **args2, char **env)
{
    char    *cmd;
    char    *cmd2;
    int pid;
    int pid2;
    int status;
    int fd1;
    int fd2;
    int fd[2];


    cmd = find_path(env, args1[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pipe(fd)) == -1)
    {
        printf("error with pipe\n");
        return (NULL);
    }
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        close(fd[0]);
        fd1 = open(infile, O_RDONLY);
        dup2(fd1, 0);//cmd1 take output form file1
        dup2(fd[1], 1);//input of cmd1 in pipe fd[1]
        close (fd1);
        close(fd[1]);
        execve(cmd, args1, NULL);
    }
    else
    {
        cmd2 = find_path(env, args2[0]);
        if (cmd2 == NULL)
            return (NULL);
        if ((pid2 = fork()) == -1)
        {
            printf("error with fork\n");
            return (NULL);
        }
        else if (pid2 == 0)
        {
            close(fd[1]);
            fd2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            dup2(fd2, 1);//output of cmd2 to outfile fd2
            close (fd2);//
            dup2(fd[0], 0);//input of cmd2 from wpipe fd[0]
            close(fd[0]);
            execve(cmd2, args2, NULL);
        }
        close(fd[0]);
        close(fd[1]);
        wait(&status);
        wait(&status);
    }
    return ("succes");
}