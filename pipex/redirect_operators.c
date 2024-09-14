#include "pipex.h"

char    *redirect_input(char *infile, char **args, char **env)
{
    int fd;
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, args[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        fd = open(infile, O_RDONLY);
        dup2(fd, 0);//input of file to stdin
        close (fd);
        execve(cmd, args, NULL);
    } 
    wait(&status);
    return ("succes");  
}

char    *redirect_output(char *outfile, char **args, char **env)
{
    int fd;
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, args[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, 1);//output of cmd to outfile fd
        close (fd);
        execve(cmd, args, NULL);
    } 
    wait(&status);
    return ("succes");  
}

char    *redirect_output_append(char *outfile, char **args, char **env)
{
    int fd;
    int pid;
    int status;
    char *cmd;

    cmd = find_path(env, args[0]);
    if (cmd == NULL)
        return (NULL);
    if ((pid = fork()) == -1)
    {
        printf("error with fork\n");
        return (NULL);
    }
    else if (pid == 0)
    {
        fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        dup2(fd, 1);//output of cmd to outfile fd
        close (fd);
        execve(cmd, args, NULL);
    } 
    wait(&status);
    return ("succes");  
}