# The name of your final executable
NAME = so_long

# Compiler and flags
CC = gcc
# -g flag adds debugging symbols
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

# --- Project Source Files ---
# List all of your project's .c files here
SRCS =  so_long.c \
        map_parser.c \
        map_parser2.c \
        rendering.c \
        cleanup.c

# --- Library Paths ---
# Adjust these paths if your folders are named differently
LIBFT_DIR = ./libft
GNL_DIR = ./get_next_line
PRINTF_DIR = ./ft_printf
MLX_DIR = ./minilibx-linux

# Add the GNL source files directly, as it does not have its own Makefile
SRCS += $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

# --- Library Archives (.a files) ---
LIBFT = $(LIBFT_DIR)/libft.a
# MODIFICATION 1: Use the correct filename
PRINTF = $(PRINTF_DIR)/ft_printf.a

# Automatically create object file names from source file names
OBJS = $(SRCS:.c=.o)

# --- Flags for Headers and Libraries ---
# -I tells the compiler where to find header files (.h)
CPPFLAGS = -I. \
           -I$(MLX_DIR) \
           -I$(LIBFT_DIR) \
           -I$(GNL_DIR) \
           -I$(PRINTF_DIR)

# -L tells the linker where to find library files (.a)
# -l tells the linker which library to link
LDFLAGS = -L$(MLX_DIR) -lmlx \
          -L$(LIBFT_DIR) -lft \
          $(PRINTF) \
          -lXext -lX11 -lm -lbsd

# --- Rules ---

# Default rule
all: $(NAME)

# Rule to create the final executable
# This depends on the object files and the compiled libraries
$(NAME): $(OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

# Rules to build the libraries. 'make' will run 'make' inside these folders.
$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

# Rule to compile a .c file into a .o file
# It depends on so_long.h to recompile if the header changes
%.o: %.c so_long.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Rule to remove object files
clean:
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean
	$(RM) $(OBJS)

# Rule to remove object files and the final executable
fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	$(RM) $(NAME)

# Rule to force re-compilation
re: fclean all

# Mark rules that are not files as .PHONY
.PHONY: all clean fclean re
