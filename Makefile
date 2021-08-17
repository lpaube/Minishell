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

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -rf

$(OBJ)/%.o:	$(SRC)/%.c
			$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME):	$(OBJ) $(OBJS)
			$(CC) $(OBJS) -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norme:
			norminette $(SRCS) $(HEADERS)

.PHONY:		all clean fclean re norme