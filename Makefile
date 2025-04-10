.PHONY: all re clean fclean debug

CC = c++

CFLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lX11 -lwiringPi -lstdc++ -L./inc/libft -lft -llirc_client
NAME = raspiremote

SRC = src/hardware.cpp \
		src/keypress.cpp \
		src/gui.cpp \
		src/main.cpp
OBJ = $(SRC:.cpp=.o)

all: libft $(NAME)

libft:
	make -C ./inc/libft

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJ)
	make -C ./inc/libft clean

fclean: clean
	rm -rf $(NAME)
	make -C ./inc/libft fclean


re: fclean all
