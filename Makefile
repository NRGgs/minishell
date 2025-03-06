# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LFLAGS = -lreadline
# -fsanitize=address

# Libraries
LIBFT_PATH	= ./includes/libft
LIBFT		= $(LIBFT_PATH)/libft.a

# Source files and object files
SRC_DIR = sources
EXP_DIR = expand
TKN_DIR = tokenize
PARSE_DIR = parse
EXE_DIR = execute
BLT_DIR = execute/builtins
MEM_DIR = memory
SRCS =	$(SRC_DIR)/minishell.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/$(EXP_DIR)/backslashes.c \
		$(SRC_DIR)/$(EXP_DIR)/prepare.c \
		$(SRC_DIR)/$(EXP_DIR)/quotes.c \
		$(SRC_DIR)/$(EXP_DIR)/variables.c \
		$(SRC_DIR)/$(EXE_DIR)/find_path.c \
		$(SRC_DIR)/$(EXE_DIR)/redirect.c \
		$(SRC_DIR)/$(EXE_DIR)/find_path_2.c \
		$(SRC_DIR)/$(EXE_DIR)/init_env_list.c \
		$(SRC_DIR)/$(EXE_DIR)/build_execve_args.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_1.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_2.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_3.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_4.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_without_pipe.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_without_pipe_2.c \
		$(SRC_DIR)/$(EXE_DIR)/execution.c \
		$(SRC_DIR)/$(BLT_DIR)/builtins.c \
		$(SRC_DIR)/$(BLT_DIR)/cd.c \
		$(SRC_DIR)/$(BLT_DIR)/echo.c \
		$(SRC_DIR)/$(BLT_DIR)/env.c \
		$(SRC_DIR)/$(BLT_DIR)/exit.c \
		$(SRC_DIR)/$(BLT_DIR)/export.c \
		$(SRC_DIR)/$(BLT_DIR)/export_2.c \
		$(SRC_DIR)/$(BLT_DIR)/export_3.c \
		$(SRC_DIR)/$(BLT_DIR)/pwd.c \
		$(SRC_DIR)/$(BLT_DIR)/unset.c \
		$(SRC_DIR)/$(MEM_DIR)/free.c \
		$(SRC_DIR)/$(MEM_DIR)/commands.c \
		$(SRC_DIR)/$(MEM_DIR)/tokens.c \
		$(SRC_DIR)/$(PARSE_DIR)/parse_utils.c \
		$(SRC_DIR)/$(PARSE_DIR)/assign.c \
		$(SRC_DIR)/$(PARSE_DIR)/get_commands.c \
		$(SRC_DIR)/$(PARSE_DIR)/heredoc.c \
		$(SRC_DIR)/$(PARSE_DIR)/parse.c \
		$(SRC_DIR)/$(TKN_DIR)/tokenize.c \
		$(SRC_DIR)/$(TKN_DIR)/utils.c \
		$(SRC_DIR)/$(TKN_DIR)/word_length.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_5.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_with_pipe_6.c \
		$(SRC_DIR)/$(EXE_DIR)/execution_without_pipe_3.c

OBJ_DIR = objects
# OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Output executable
NAME = minishell

# Default target
all: $(NAME)

# Name rule to create executable
$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LFLAGS)
	@echo "Executable $(NAME) created"

# Rule to create libft.a
$(LIBFT):
	@make -C $(LIBFT_PATH)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(EXP_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(TKN_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(PARSE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(EXE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(BLT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(MEM_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	@echo "Compiled $<"

# Clean up object files
clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

# Clean up object files, libraries, and executable(s)
fclean: clean
	@echo "Cleaning executable..."
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

# Recompile all files
re: fclean all

# Phony targets
.PHONY: all clean fclean re
