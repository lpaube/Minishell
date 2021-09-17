/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/16 20:11:04 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

t_minishell	g_mini;

void	minishell_init(void)
{
	g_mini.env = NULL;
	g_mini.code = 0;
	g_mini.fd = malloc(2 * sizeof(int));
	g_mini.saved_stdin = dup(0);
	g_mini.saved_stdout = dup(1);
	g_mini.allow_signal = 1;
}

char	*get_line(char *line)
{
	char	*tmp;

	line = readline("minishell: ");
	if (!line)
	{
		g_mini.code = 0;
		exit(0);
	}
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (*line)
		add_history(line);
	return (line);
}

void	free_memory(t_list **lst1, t_node **lst2, char *str)
{
	ft_lstclear(lst1, ft_str_free);
	nodeclear(lst2);
	free(str);
}

void	minishell_loop(void)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_node	*cmds;

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
			if (main_control(cmds))
			{
				free_memory(&lst, &cmds, tok.str);
				break ;
			}
		}
		free_memory(&lst, &cmds, tok.str);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	signal(SIGINT, newline);
	signal(SIGQUIT, nothing);
	minishell_init();
	g_mini.env = ft_dup_strarr(env);
	minishell_loop();
	close(g_mini.saved_stdin);
	close(g_mini.saved_stdout);
	free(g_mini.fd);
	//scanf("c");
}
