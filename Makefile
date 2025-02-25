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
PREP_DIR = prepare_arg
TKN_DIR = tokenize
PARSE_DIR = parse
EXE_DIR = execution
BLT_DIR = execution/builtins
MEM_DIR = memory
SRCS =	$(SRC_DIR)/minishell.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/find_path.c \
		$(SRC_DIR)/redirect.c \
		$(SRC_DIR)/find_path_2.c \
		$(SRC_DIR)/init_env_list.c \
		$(SRC_DIR)/build_execve_args.c \
		$(SRC_DIR)/$(PREP_DIR)/backslashes.c \
		$(SRC_DIR)/$(PREP_DIR)/prepare.c \
		$(SRC_DIR)/$(PREP_DIR)/quotes.c \
		$(SRC_DIR)/$(PREP_DIR)/variables.c \
		$(SRC_DIR)/$(TKN_DIR)/tokenize.c \
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
		$(SRC_DIR)/$(BLT_DIR)/pwd.c \
		$(SRC_DIR)/$(BLT_DIR)/unset.c \
		$(SRC_DIR)/$(MEM_DIR)/free.c \
		$(SRC_DIR)/$(MEM_DIR)/custom_variables.c \
		$(SRC_DIR)/$(MEM_DIR)/commands.c \
		$(SRC_DIR)/$(MEM_DIR)/tokens.c \
		$(SRC_DIR)/$(PARSE_DIR)/necessary.c

OBJ_DIR = objects
# OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

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

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(PREP_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(TKN_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(PARSE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(EXE_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(BLT_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/$(MEM_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

$(OBJ_DIR)/%.o: nrgtokenizing/%.c
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