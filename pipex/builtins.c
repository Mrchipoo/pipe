#include "pipex.h"




void    check_if_built()
{

}


char    *echo(char **argv , int argc)
{
    int i;

    i = 1;
    while (i < argc)
    {
        printf("%s",argv[i]);
        i++;
    }
}