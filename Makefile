NAME		=	minishell

SRC			=	src
INC			=	include
OBJ			=	obj

HFILES		=	utils.h
HEADERS		=	$(addprefix $(INC)/, $(HFILES))

CFILES		=	main.c
OFILES		=	$(CFILES:.c=.o)
OBJS		=	$(addprefix $(OBJ)/, $(OFILES))
SRCS		=	$(addprefix $(SRC)/, $(CFILES))

FTDIR		=	libft
LIBFT		=	ft
MAKELIBFT	=	$(MAKE) -C $(FTDIR)

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			$(CC) $(CFLAGS) -I$(INC) -I$(FTDIR) -c $< -o $@

$(NAME):	$(OBJ) $(OBJS)
			@$(MAKELIBFT)
			$(CC) $(OBJS) -L$(FTDIR) -l$(LIBFT) -lreadline -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			@$(MAKELIBFT) clean
			@$(RM) $(OBJS)

fclean:		clean
			@$(MAKELIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all

norme:
			$(MAKELIBFT) norme
			norminette $(SRCS) $(HEADERS)

.PHONY:		all clean fclean re norme
