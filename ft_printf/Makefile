NAME	=	ft_printf.a
CC	=	gcc
FLAGS	=	-Wall -Wextra -Werror
SRC	=	ft_printf.c \
		src/ft_putchar.c \
		src/ft_putnbr.c \
		src/ft_putnbru.c \
		src/ft_puthex.c \
		src/ft_putmhex.c \
		src/ft_putptr.c \
		src/ft_putstr.c \
		src/ft_printchar.c
OBJ	=	$(SRC:.c=.o)
all:	$(NAME)
$(NAME):	$(OBJ)
	ar -rc $(NAME) $(OBJ)
%.o:	%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)
fclean:	clean
	rm -f $(NAME)
re:	fclean all
