# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Source files
SRC_PATH = ./sources
SRCS =	$(SRC_PATH)/ft_isalpha.c $(SRC_PATH)/ft_isdigit.c \
		$(SRC_PATH)/ft_isalnum.c $(SRC_PATH)/ft_isascii.c \
		$(SRC_PATH)/ft_isprint.c $(SRC_PATH)/ft_strlen.c \
		$(SRC_PATH)/ft_memset.c $(SRC_PATH)/ft_bzero.c \
		$(SRC_PATH)/ft_memcpy.c $(SRC_PATH)/ft_memmove.c \
		$(SRC_PATH)/ft_strlcpy.c $(SRC_PATH)/ft_strlcat.c \
		$(SRC_PATH)/ft_toupper.c $(SRC_PATH)/ft_tolower.c \
		$(SRC_PATH)/ft_strchr.c $(SRC_PATH)/ft_strrchr.c \
		$(SRC_PATH)/ft_strncmp.c $(SRC_PATH)/ft_memchr.c \
		$(SRC_PATH)/ft_memcmp.c $(SRC_PATH)/ft_strnstr.c \
		$(SRC_PATH)/ft_atoi.c $(SRC_PATH)/ft_calloc.c \
		$(SRC_PATH)/ft_strdup.c $(SRC_PATH)/ft_substr.c \
		$(SRC_PATH)/ft_strjoin.c $(SRC_PATH)/ft_strtrim.c \
		$(SRC_PATH)/ft_split.c $(SRC_PATH)/ft_itoa.c \
		$(SRC_PATH)/ft_strmapi.c $(SRC_PATH)/ft_striteri.c \
		$(SRC_PATH)/ft_putchar_fd.c $(SRC_PATH)/ft_putstr_fd.c \
		$(SRC_PATH)/ft_putendl_fd.c $(SRC_PATH)/ft_putnbr_fd.c \
		$(SRC_PATH)/ft_lstnew_bonus.c $(SRC_PATH)/ft_lstadd_front_bonus.c \
		$(SRC_PATH)/ft_lstsize_bonus.c $(SRC_PATH)/ft_lstlast_bonus.c \
		$(SRC_PATH)/ft_lstadd_back_bonus.c $(SRC_PATH)/ft_lstdelone_bonus.c \
		$(SRC_PATH)/ft_lstclear_bonus.c $(SRC_PATH)/ft_lstiter_bonus.c \
		$(SRC_PATH)/ft_lstmap_bonus.c $(SRC_PATH)/ft_strcmp.c \
		$(SRC_PATH)/ft_strstr.c $(SRC_PATH)/ft_strndup.c \

OBJ_DIR = objects
OBJS = $(SRCS:$(SRC_PATH)/%.c=$(OBJ_DIR)/%.o)

# Output library
NAME = libft.a

# Rule to create libft.a
$(NAME): $(OBJS)
	ar rcs $@ $^

# Default target
all: $(NAME)

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)

# Clean up object files and library
fclean: clean
	rm -f $(NAME)

# Recompile all files
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus
