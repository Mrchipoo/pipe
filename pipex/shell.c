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
	char	**path;
	char	*big_path;
	int	i;
	int	check;

	i =	0;
	check = 0;
	while ((big_path = ft_strnstr(env[i], "PATH", 4)) == NULL)
		i++;
	path = ft_split(big_path, ':');
	i  = 0;
	cmd = ft_strjoin("/", cmd);
	while (path[i])
	{
        big_path = ft_strjoin(path[i],cmd);
        check = check_access(big_path);
        if (check == 0)
        {
            free(cmd);
            return (big_path);
        }
        i++;
    }
    free(cmd);
    free(*path);
    free(path);
    if (check == 1)
        return (dprintf(2, "command not found\n"), NULL);
    else if (check == 2)
        return (dprintf(2, "command not found\n"), NULL);
    return (NULL);
}

int main (int argc, char **argv, char **env)
{
    char **args1;
    char **args2;

    //printf("%s\n",PROMPT);
    if (argc == 5)
    {
        args1 = ft_split(argv[2], ' ');
        args2 = ft_split(argv[3], ' ');
        multi_pipe(argv[1],argv[4],args1,args2,env);
        free(args1);
        free(args2);
    }
    else if (argc == 4)
    {
        if (strcmp(argv[2], ">") == 0)
        {
            args1 = ft_split(argv[1], ' ');
            redirect_output(argv[3], args1,env);
            free(args1);
        }
        else if (strcmp(argv[2], ">>") == 0)
        {
            args1 = ft_split(argv[1], ' ');
            redirect_output_append(argv[3], args1,env);
            free(args1);
        }
        else if (strcmp(argv[2], "<") == 0)
        {
            args1 = ft_split(argv[1], ' ');
            redirect_input(argv[3], args1,env);
            free(args1);
        }
        else if (strcmp(argv[2] , "<<") == 0)
        {
            args1 = ft_split(argv[1], ' ');
            her_doc(argv[3], args1, env);
            free(args1);
        }
    }
    else if(argc == 2)
    {
        if (check_if_builts(argv) == 0)
            run_builts(argv, argc);
        else
        {
            args1 = ft_split(argv[1], ' ');
            run_normal(args1, env);
            free(*args1);
            free(args1);
        }
    }
    else
        printf("invalid arg\n");
    return (0);
}
