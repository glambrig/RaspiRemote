.PHONY: all clean fclean re

NAME = libUinputWrapper.a

CC = gcc

CFLAGS = -Wall

SRC = uinputWrapperLib.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $< -O

clean:
	rm -f ./*.o

fclean: clean
	rm -f $(NAME)

re: fclean all
