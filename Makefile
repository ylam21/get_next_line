NAME = get_next_line

# Compilor and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = ./
OBJ_DIR = ./objects

# File names
SRC_FILE = get_next_line.c get_next_line_utils.c

# Sources
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILE))

# Objects
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c 	$< -o $@

clean:
	rm -rf $(OBJ_DIR)

clean_test:
	rm -rf $(SRC_DIR)/tmp

test:
	mkdir -p $(SRC_DIR)/tmp
	$(CC) $(CFLAGS) tests/main.c $(SRCS) -o tmp/a.out

run_test:
	./tmp/a.out

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re test
