.PHONY: all re clean fclean debug

CC = c++
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lwiringPi -lstdc++ -L./inc/LibUinputWrapper -lUinputWrapper -llirc_client
NAME = raspiremote

SRC = src/infared.cpp \
		src/keypress.cpp \
		src/main.cpp

OBJ = $(SRC:.cpp=.o)

all: LibUinputWrapper $(NAME)

LibUinputWrapper:
	make -C ./inc/LibUinputWrapper -O

$(NAME): $(OBJ)
	$(CC) -O -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ -O

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
	rm -rf $(OBJ)
	make -C ./inc/LibUinputWrapper clean

fclean: clean
	rm -rf $(NAME)
	make -C ./inc/LibUinputWrapper fclean

re: fclean all
