# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g

# Libraries
LIBFT_PATH	= ./includes/libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Source files and object files
SRC_DIR = sources
SRCS =	$(SRC_DIR)/parse.c
OBJ_DIR = objects
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME = minishell

# Default target
all: $(NAME)

# Name rule to create executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to create libft.a
$(LIBFT):
	@make -C $(LIBFT_PATH)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

# Clean up object files, libraries, and executable(s)
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

# Recompile all files
re: fclean all

# Phony targets
.PHONY: all clean fclean re