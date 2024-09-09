NAME =pipex
CC =cc
GFLAGS =-Wall -Wextra -Werror -g3
HEADER =pipex.h
SRC =pipex.c split.c string_utils.c
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
