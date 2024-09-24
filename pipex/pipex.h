#ifndef PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# ifndef PROMPT
#   define PROMPT "\e[0m\e[35m\003 Minishell>$ \001\e[0m\002"
# endif

void    run_builts(char **argv, int argc, char **env);
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
char    *get_next_line(int fd);
char    *her_doc(char *Delimit, char **args, char **env);
size_t	ft_strlen(char *str);
char    *ft_echo(char **argv , int argc);

#endif
