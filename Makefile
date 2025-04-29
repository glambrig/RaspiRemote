.PHONY: all re clean fclean debug

CC = c++

#remove -g before final push
CFLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lwiringPi -lstdc++ -L./inc/libft -lft -llirc_client
NAME = raspiremote

SRC = src/infared.cpp \
		src/keypress.cpp \
		src/gui.cpp \
		src/main.cpp
OBJ = $(SRC:.cpp=.o)

all: libft $(NAME)

libft:
	make -C ./inc/libft -O

$(NAME): $(OBJ)
	$(CC) -O -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -O

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJ)
	make -C ./inc/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./inc/libft fclean


re: fclean all
