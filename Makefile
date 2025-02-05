# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline

# Libraries
LIBFT_PATH	= ./includes/libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Source files and object files
SRC_DIR = sources
SRCS =	$(SRC_DIR)/commands.c $(SRC_DIR)/variables.c \
		$(SRC_DIR)/parse_cmds.c $(SRC_DIR)/parse_var.c $(SRC_DIR)/parse.c \
		$(SRC_DIR)/parse_clean.c $(SRC_DIR)/parse_redirect.c \
		$(SRC_DIR)/redirections.c $(SRC_DIR)/minishell.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/builtins.c \
		$(SRC_DIR)/cd.c \
		$(SRC_DIR)/echo.c \
		$(SRC_DIR)/env.c \
		$(SRC_DIR)/exit.c \
		$(SRC_DIR)/export.c \
		$(SRC_DIR)/pwd.c \
		$(SRC_DIR)/unset.c \
		$(SRC_DIR)/execution.c \
		$(SRC_DIR)/find_path.c \
		$(SRC_DIR)/redirect.c \
		$(SRC_DIR)/execution_without_pipe.c \
		$(SRC_DIR)/execution_with_pipe_1.c \
		$(SRC_DIR)/execution_with_pipe_2.c \
		$(SRC_DIR)/export_2.c \
		$(SRC_DIR)/execution_without_pipe_2.c \
		$(SRC_DIR)/find_path_2.c \
		$(SRC_DIR)/init_env_list.c \
		$(SRC_DIR)/parse_checks.c \
		$(SRC_DIR)/parse_string_utils.c \
		$(SRC_DIR)/parse_string.c \
		$(SRC_DIR)/free.c \
		$(SRC_DIR)/execution_with_pipe_3.c

OBJ_DIR = objects
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Output executable
NAME = minishell

# Default target
all: $(NAME)

# Name rule to create executable
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)

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