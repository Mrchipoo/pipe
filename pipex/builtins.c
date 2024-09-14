#include "pipex.h"

char    *ft_echo(char **argv , int argc)
{
    int i;

    i = 1;
    while (i < argc)
    {
        printf("%s",argv[i]);
        i++;
    }
    return ("succes");
}

int ft_pwd()
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        return (EXIT_FAILURE);
    printf("%s\n",pwd);
    return (EXIT_SUCCESS);
}

int    check_if_builts(char **argv)
{
    if (strcmp(argv[1], "echo") == 0)
        return (0);
    else if (strcmp(argv[1], "pwd") == 0)
        return (0);
    return (1);
}

void    run_builts(char **argv, int argc)
{
    if (strcmp(argv[1], "echo") == 0)
        ft_echo(argv, argc);
    else if (strcmp(argv[1], "pwd") == 0)
        ft_pwd();
}