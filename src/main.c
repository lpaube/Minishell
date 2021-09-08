/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/08 17:35:33 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"
#include "tokenizer.h"
#include "parser.h"
#include "print.h"
#include "signal_handler.h"
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

t_minishell	g_minishell;

void	minishell_init(void)
{
	g_minishell.env = NULL;
	g_minishell.code = 0;
	g_minishell.fd = malloc(2 * sizeof(int));
	if (pipe(g_minishell.fd) != 0)
		print_error("Pipe failed in minishell_init");
	g_minishell.saved_stdin = dup(0);
	g_minishell.saved_stdout = dup(1);
}

char	*get_line(char *line)
{
	char	*tmp;

	line = readline("minishell: ");
	if (!line)
		exit(0);
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (*line)
		add_history(line);
	return (line);
}

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
}

void	free_lists(t_list **lst1, t_phrase **lst2)
{
	ft_lstclear(lst1, ft_str_free);
	nodeclear(lst2);
}

int	main(int argc, char **argv, char **env)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_phrase	*cmds;

	(void)argc;
	(void)argv;
	signal(SIGINT, newline);
	signal(SIGQUIT, nothing);
	minishell_init();
	g_minishell.env = ft_dup_strarr(env);
	tok.str = NULL;
	cmds = NULL;
	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!*tok.str)
			continue ;
		lst = tokenize(&tok);
		if (lst)
		{
			cmds = parse(lst);
			if (argv[1] && ft_strncmp(argv[1], "-d", 3) == 0)	// Launch with "-d" for debug mode
				print_nodes(cmds);
			main_control(cmds);
		}
		free_lists(&lst, &cmds);
		free(tok.str);
	}
}
