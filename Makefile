.PHONY: all re clean fclean debug

CC = c++
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lwiringPi -lstdc++ -L./inc/libft -lft -L./inc/uinputWrapperLib -lUinputWrapper -llirc_client
NAME = raspiremote

SRC = src/infared.cpp \
		src/keypress.cpp \
		src/gui.cpp \
		src/main.cpp

OBJ = $(SRC:.cpp=.o)

all: libft uinputWrapperLib $(NAME)

libft:
	make -C ./inc/libft -O

uinputWrapperLib:
	make -C ./inc/uinputWrapperLib -O

$(NAME): $(OBJ)
	$(CC) -O -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -O

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJ)
	make -C ./inc/libft clean
	make -C ./inc/uinputWrapperLib clean

fclean: clean
	rm -rf $(NAME)
	make -C ./inc/libft fclean
	make -C ./inc/uinputWrapperLib fclean

re: fclean all
