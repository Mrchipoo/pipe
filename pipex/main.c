#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
	/env print envar
	/export with no arg behave like env but sorted from a to z
	/export a var with no value doesnt show up in env cmd, but show up in export
	/i will not work on export with no args for now
	/unset remove var from env

*/

typedef struct s_env_list
{
	char	*name;
	int	value;
struct s_env_list    *next;
} t_env_list;

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '\0')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

t_env_list	*ft_last_node(t_env_list *head)
{
	t_env_list	*new_node;

	new_node = head;
	while (new_node->next != NULL)
		new_node = new_node->next;
	return (new_node);
}

t_env_list	*ft_create_node(char *str)
{
	t_env_list	*new_node;
	int	flag;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
		return (0);
	new_node->name = str;
	if ((flag = check_value(str)) == 0)
		new_node->value = 1;
	else
		new_node->value = 0;
	new_node->next = NULL;
	return (new_node);
}

t_env_list	*env_to_list(char	**env)
{
	int	i;
	t_env_list	*current;
	t_env_list	*new_node;
	t_env_list	*first;

	i = 0;
	current = NULL;
	while (env[i])
	{
		new_node = ft_create_node(env[i]);
		if (current == NULL)
		{
			current = new_node;
			first = current;
		}
		else
			ft_last_node(current)->next = new_node;
		i++;
	}
	return (first);
}

void	add_new_var(char *str, t_env_list *list)
{
	t_env_list	*new_node;
	t_env_list	*current;

	current = list;
	new_node = ft_create_node(str);
	ft_last_node(current)->next = new_node;//add new var to env linked list
}

char	*ft_export(t_env_list *list, char **argv)
{
	int j;

	j = 2;
	if (argv[j] == NULL)// no args mean print
	{
		//print_export();
		return (NULL);
	}
	while (argv[j])
	{
		add_new_var(argv[j], list);
		j++;
	}
	return (NULL);
}

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

char	*ft_env(t_env_list *list)
{
	t_env_list	*new_node;

	new_node = list;
	while(new_node != NULL)
	{
		if (new_node->value == 1)
			printf("%s\n",new_node->name);
		new_node = new_node->next;
	}
	return ("succes");
}

int    check_if_builts(char **argv)
{
    if (strcmp(argv[1], "echo") == 0)
        return (0);
    else if (strcmp(argv[1], "pwd") == 0)
        return (0);
	else if (strcmp(argv[1], "env") == 0)
		return (0);
	else if (strcmp(argv[1], "export") == 0)
		return (0);
	else if (strcmp(argv[1], "unset") == 0)
		return (0);
    return (1);
}

void    run_builts(char **argv, int argc, t_env_list *list)
{
    if (strcmp(argv[1], "echo") == 0)
        ft_echo(argv, argc);
    else if (strcmp(argv[1], "pwd") == 0)
        ft_pwd();
	else if (strcmp(argv[1], "env") == 0)
		ft_env(list);
	else if (strcmp(argv[1], "export") == 0)
		ft_export(list, argv);
	else if (strcmp(argv[1], "unset") == 0)//to do
		return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_env_list *list;

	if (argc > 1)
	{
		if (check_if_builts(argv) == 0)
		{
			list = env_to_list(env);
            run_builts(argv, argc, list);
		}
	}
	else
		printf("invalid arg\n");
	return (0);
}
