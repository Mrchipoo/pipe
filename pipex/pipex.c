#include "pipex.h"


int check_access(char *PATH)
{
    if (access(PATH, F_OK) == 0)
    {
        if (access(PATH, X_OK) == 0)
            return (0);
        else
            return (2);
    }
    else
        return (1);      
}

char    *find_path(char **env, char *cmd)
{
    char    **path;
    char    *PATH;
    int i;
    int check;

    i = 0;
    check = 0;
    while ((PATH = ft_strnstr(env[i], "PATH", 4)) == NULL)
        i++;
    path = ft_split(PATH, ':');
    i  = 0;
    cmd = ft_strjoin("/", cmd); 
    while (path[i])
    {
        PATH = ft_strjoin(path[i],cmd);
        check = check_access(PATH);
        if (check == 0)
            return (PATH);
        i++;
    }
    if (check == 1)
        return (dprintf(2, "command not found\n"), NULL);
    else if (check == 2)
        return (dprintf(2, "command not found\n"), NULL);
    return (NULL);
}

int main (int argc, char **argv, char **env)
{
    int pid;
    int pid2;
    int fd1;
    int status;
    int fd2;
    int fd[2];
    char **args1;
    char **args2;
    char    *cmd;
    char    *cmd2;

    args1 = ft_split(argv[2], ' ');
    args2 = ft_split(argv[3], ' ');
    if (argc == 5)
    {
        cmd = find_path(env, args1[0]);
        if (cmd == NULL)
            return (1);
        if ((pipe(fd)) == -1)
        {
            printf("error with pipe\n");
            return (1);
        }
        if ((pid = fork()) == -1)
        {
            printf("error with fork\n");
            return (1);
        }
        else if (pid == 0)
        {
            close(fd[0]);
            fd1 = open(argv[1], O_RDONLY);
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
                return (1);
            if ((pid2 = fork()) == -1)
            {
                printf("error with fork\n");
                return (1);
            }
            else if (pid2 == 0)
            {
                close(fd[1]);
                fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
    }
    else
        printf("invalid arg\n");
    free(args1);
    free(args2);
    return (0);
}