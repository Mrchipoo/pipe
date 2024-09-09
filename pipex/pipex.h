#ifndef PIPEX_H
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
# define PIPEX_H

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char	*big, const char *little, size_t len);

#endif
