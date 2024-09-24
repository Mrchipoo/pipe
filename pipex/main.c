#include "pipex.h"

int	echo_check(char **argv, int argc)
{
	int	i;
	int	j;

	i = 2;

	while (i < argc)
	{
		j = 1;
		if (argv[i][0] == '-')
		{
			while (argv[i][j])
			{
				if (argv[i][j] == 'n')
					j++;
				else
					return (i);
			}
		}
		else
			return (i);
		i++;
	}
	return (i);
}
char    *ft_echo(char **argv , int argc)
{
    int i;
	int	flag;

    i = echo_check(argv, argc);
	if (i == 2)
		flag = 1;
	else
		flag = 0;
    while (i < argc)
    {
        printf("%s",argv[i]);
        i++;
		if (i != argc)
			printf(" ");
    }
	if (flag == 1)
		printf("\n");
    return ("succes");
}

int ft_pwd()
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        return (EXIT_FAILURE);
    printf("%s\n",pwd);
    free (pwd);
    return (EXIT_SUCCESS);
}

int    check_if_builts(char **argv)
{
    if (strcmp(argv[1], "echo") == 0)
        return (0);
    else if (strcmp(argv[1], "pwd") == 0)
        return (0);
	else if (strcmp(argv[1], "env") == 0)
		return (0);
    return (1);
}

char	*ft_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		printf("%s\n",env[i]);
		i++;
	}
	return ("succes");
}

void    run_builts(char **argv, int argc, char **env)
{
    if (strcmp(argv[1], "echo") == 0)
        ft_echo(argv, argc);
    else if (strcmp(argv[1], "pwd") == 0)
        ft_pwd();
	else if (strcmp(argv[1], "env") == 0)
		ft_env(env);
}

int	main(int argc, char **argv, char **env)
{
	if (argc > 1)
	{
		if (check_if_builts(argv) == 0)
            run_builts(argv, argc, env);
	}
	else
		printf("invalid arg\n");
	return (0);
}
