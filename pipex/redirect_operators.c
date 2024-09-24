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

char    *her_doc(char *Delimit, char **args, char **env)
{
    int pid;
    int fd[2];
    int status;
    char    *cmd;
    char    *line;

    line = NULL;
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
        while (1)
        {
            line = readline("heredoc> ");
            if (strcmp(line, Delimit) == 0)
                exit(EXIT_SUCCESS);
            write(fd[1], line, ft_strlen(line));
            write(fd[1], "\n", 1);
        }
    }
    else
    {
        wait(&status);
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
            close(fd[1]);
            dup2(fd[0], 0);
            close(fd[0]);
            execve(cmd, args, NULL);
        }
        close(fd[1]);
        close(fd[0]);
        wait(&status);
    }
    return ("succes");
}