NAME		=	minishell

SRC			=	src
INC			=	include
OBJ			=	obj
LIB			=	lib

HFILES		=	tokenizer.h parse.h node.h execution.h minishell.h builtin.h\
				eprint.h environment.h
HEADERS		=	$(addprefix $(INC)/, $(HFILES))

BUILTIN_DIR	=	$(SRC)/builtins
BUILTIN_C	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
BUILTIN_SRC	=	$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_C))

PARSING_DIR	=	$(SRC)/parsing
PARSING_C	=	interpolation.c interpolation2.c parse.c syntax.c token.c\
				tokenizer.c tokenizer_utils.c
PARSING_SRC	=	$(addprefix $(PARSING_DIR)/, $(PARSING_C))

CFILES		=	main.c node.c eprint.c environment.c exec_control.c\
				signal_handler.c exec_cmd.c
#				 exec_control.c 

OFILES		=	$(CFILES:.c=.o) $(BUILTIN_C:.c=.o) $(PARSING_C:.c=.o)
OBJS		=	$(addprefix $(OBJ)/, $(OFILES))
SRCS		=	$(addprefix $(SRC)/, $(CFILES)) $(BUILTIN_SRC) $(PARSING_SRC)

FTDIR		=	libft
LIBFT		=	ft
MAKELIBFT	=	$(MAKE) -C $(FTDIR)

CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -g
RM			=	rm -rf

VPATH		= $(SRC) $(BUILTIN_DIR) $(PARSING_DIR)

$(OBJ)/%.o:	%.c
			$(CC) $(CFLAGS) -I$(INC) -I$(FTDIR) -c $< -o $@

$(NAME):	$(OBJ) $(OBJS)
			@$(MAKELIBFT)
			$(CC) $(OBJS) -L$(FTDIR) -l$(LIBFT) -L$(LIB) -lreadline -lcurses -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

all:		$(NAME)

linux:		$(OBJ) $(OBJS)
			@$(MAKELIBFT)
			$(CC) $(OBJS) -L$(FTDIR) -l$(LIBFT) -lreadline -o $(NAME)

clean:
			@$(MAKELIBFT) clean
			@$(RM) $(OBJS)

fclean:		clean
			@$(MAKELIBFT) fclean
			@$(RM) $(NAME)

re:			fclean all

norme:
			@$(MAKELIBFT) norme
			@norminette $(SRCS) $(HEADERS)

.PHONY:		all clean fclean re norme linux
