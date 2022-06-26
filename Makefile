NAME_SERVER = server

NAME_CLIENT = client

CC	=	cc

CFLAGS = -Wall -Wextra -Werror

SRCS_SERVER = server.c

OBJS_SERVER = server.o

SRCS_CLINET = client.c

OBJS_CLINET = client.o

RM = rm -f

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(FT_PRINTF) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLINET) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLINET) $(FT_PRINTF) -o $(NAME_CLIENT)

$(FT_PRINTF):
	@make --no-print-directory -C $(FT_PRINTF_DIR)

clean:
	@make --no-print-directory clean -C $(FT_PRINTF_DIR)
	$(RM) *.o

fclean: clean
	@make --no-print-directory fclean -C $(FT_PRINTF_DIR)
	$(RM) $(NAME_SERVER)
	$(RM) $(NAME_CLIENT)

re:	fclean all

bonus:	all

.PHONY: all clean fclean re bonus .c.o
