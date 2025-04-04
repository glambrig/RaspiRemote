.PHONY: all re clean fclean debug

CC = c++
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lX11
NAME = raspiremote
SRC = src/hardware.cpp \
        src/keypress.cpp \
        src/mouse.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
    $(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
    $(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS = $(DEBUG_FLAGS)
debug: re

clean:
    rm -rf $(OBJ)

fclean: clean
    rm -rf $(NAME)

re: fclean all