#ifndef PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
# define PIPEX_H

# define PROMPT "\e[0m\e[35m\003 Minishell>$ \001\e[0m\002"

void    run_builts(char **argv, int argc);
char	**ft_split(char const *s, char c);
char    *run_normal(char **args, char **env);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char	*big, const char *little, size_t len);
char    *find_path(char **env, char *cmd);
char    *multi_pipe(char *infile, char *outfile, char **args1, char **args2, char **env);
char    *redirect_output(char *outfile, char **args, char **env);
char    *redirect_output_append(char *outfile, char **args, char **env);
char    *redirect_input(char *outfile, char **args, char **env);
int     check_if_builts(char **argv);
int     check_access(char *PATH);
int	get_next_line(char **line);
char    *her_doc(char *Delimit, char **args, char **env);

#endif
