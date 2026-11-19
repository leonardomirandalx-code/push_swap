NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -I.
RM = rm -f

SRC = main.c \
      parsing/parsing.c \
      parsing/parsing_utils.c \
      helpers/h_split.c \
      helpers/helpers.c \
	  helpers/stack_helpers.c \
	  helpers/stack_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
