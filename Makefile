NAME		=	minishell

SRC			=	src
INC			=	include
OBJ			=	obj
LIB			=	lib
CC			=	clang
CFLAGS		=	-Wall -Wextra -Werror -Wpedantic -Wconversion
RM			=	rm -rf

FTDIR		=	libft
LIBFT		=	ft
MAKELIBFT	=	$(MAKE) -C $(FTDIR)

HFILES		=	tokenizer.h parse.h node.h exec.h minishell.h builtin.h
BUILTIN_C	=	cd.c echo.c env.c exit.c export.c pwd.c unset.c
PARSING_C	=	interpolation.c interpolation2.c parse.c syntax.c token.c\
				tokenizer.c tokenizer_utils.c
EXEC_C		=	cmd.c exec.c pipe.c redir.c heredoc.c pipe_utils.c
CFILES		=	main.c node.c eprint.c environment.c signal_handlers.c

BUILTIN_DIR	=	$(SRC)/builtins
PARSING_DIR	=	$(SRC)/parsing
EXEC_DIR	=	$(SRC)/exec

BUILTIN_SRC	=	$(addprefix $(BUILTIN_DIR)/, $(BUILTIN_C))
PARSING_SRC	=	$(addprefix $(PARSING_DIR)/, $(PARSING_C))
EXEC_SRC	=	$(addprefix $(EXEC_DIR)/, $(EXEC_C))

OFILES		=	$(CFILES:.c=.o) $(BUILTIN_C:.c=.o) $(PARSING_C:.c=.o) $(EXEC_C:.c=.o)

HEADERS		=	$(addprefix $(INC)/, $(HFILES))
OBJS		=	$(addprefix $(OBJ)/, $(OFILES))
SRCS		=	$(addprefix $(SRC)/, $(CFILES)) $(BUILTIN_SRC) $(PARSING_SRC) $(EXEC_SRC)

VPATH		=	$(SRC) $(BUILTIN_DIR) $(PARSING_DIR) $(EXEC_DIR)

$(OBJ)/%.o:	%.c
			$(CC) $(CFLAGS) -I. -I$(INC) -c $< -o $@

all:		CFLAGS += -O2 -DNDEBUG
all:		$(NAME)

$(NAME):	$(OBJ) $(OBJS)
			@$(MAKELIBFT)
			$(CC) $(OBJS) -L$(FTDIR) -l$(LIBFT) -L$(LIB) -lreadline -lcurses -o $(NAME)

$(OBJ):
			@mkdir -p $(OBJ)

debug:		CFLAGS += -g
debug:		$(NAME)

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

.PHONY:		all clean fclean re norme debug
