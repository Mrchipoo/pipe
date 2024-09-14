NAME =pipex
CC =cc
GFLAGS =-Wall -Wextra -Werror -g3
HEADER =pipex.h
SRC =shell.c split.c string_utils.c pipe.c redirect_operators.c normal_cmd.c builtins.c
OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT) $(HEADER)
	$(CC) $(GFLAGS) $(OBJECT) -o $(NAME)
$(OBJECT): $(SRC)
	$(CC) $(GFLAGS) $(SRC) -c
clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)
re: fclean all
