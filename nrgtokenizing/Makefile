# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline
# -fsanitize=address
# Libraries
LIBFT_PATH	= ../includes/libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Source files and object files
SRCS =	$(wildcard *.c) \
		../sources/memory/commands.c \
		../sources/parse/parse_clean.c \
		../sources/memory/free.c

OBJ_DIR = objects
OBJS = $(SRCS:%.c=%.o)

# Output executable
NAME = token

# Default target
all: $(NAME)

# Name rule to create executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)

# Rule to create libft.a
$(LIBFT):
	@make -C $(LIBFT_PATH)

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