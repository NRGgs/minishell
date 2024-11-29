# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

LIBFT_PATH	= ../libft
LIBFT		= $(LIBFT_PATH)/libft.a

SRC_PATH = ./sources
SRCS =	$(SRC_PATH)/ft_printf.c $(SRC_PATH)/flags.c $(SRC_PATH)/flag_utils.c \
		$(SRC_PATH)/print_char.c $(SRC_PATH)/print_decimal.c \
		$(SRC_PATH)/print_string.c $(SRC_PATH)/print_unsigned.c \
		$(SRC_PATH)/print_hex.c $(SRC_PATH)/print_pointer.c \
		$(SRC_PATH)/print_utils.c $(SRC_PATH)/print_decimal_station.c \
		$(SRC_PATH)/print_unsigned_station.c $(SRC_PATH)/print_hex_station.c

OBJ_DIR = objects
OBJS = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

# Output library (libftprintf.a)
NAME = libftprintf.a

# Default target
all: $(NAME)

bonus: $(LIBFT)
	ar rcs $(NAME) $^

# Rule to create libftprintf.a
$(NAME): $(LIBFT) $(OBJS)
	ar rcs $@ $^

# Rule to create libft.a
$(LIBFT):
	@make -C $(LIBFT_PATH)
	@cp $(LIBFT) .
	@mv libft.a $(NAME)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

# Clean up object files and library
fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)

# Recompile all files
re: clean all

# Phony targets
.PHONY: all clean fclean re
