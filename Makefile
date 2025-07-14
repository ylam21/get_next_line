NAME = gnl
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = get_next_line.c get_next_line_utils.c
TEST_SRC = test/main.c

OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:test/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ_DIR) $(TEST_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJ) -o $(NAME)
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
$(OBJ_DIR)/%.o: test/%.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run_test: all
	./$(NAME)

clean:
	rm -rf $(OBJ_DIR) $(NAME)

.PHONY: clean all run_test
