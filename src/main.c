/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/22 03:43:57 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

t_minishell	g_mini;

static void	minishell_init(char **env)
{
	g_mini.env = ft_strarr_dup(env);
	g_mini.code = 0;
	g_mini.stdin_fd = dup(STDIN_FILENO);
	g_mini.stdout_fd = dup(STDOUT_FILENO);
	signal(SIGINT, newline);
	signal(SIGQUIT, SIG_IGN);
}

static char	*get_line(char *line)
{
	char	*tmp;

	line = readline(SHELL_NAME"% ");
	if (!line)
	{
		g_mini.code = 0;
		return (NULL);
	}
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (*line)
		add_history(line);
	return (line);
}

static void	free_memory(t_list **tokens, t_node **cmds, char *line)
{
	ft_lstclear(tokens, ft_str_free);
	nodeclear(cmds);
	free(line);
}

static void	minishell_loop(void)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_node		*cmds;

	tok.str = NULL;
	cmds = NULL;
	lst = NULL;
	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!tok.str)
			return (free_memory(&lst, &cmds, tok.str));
		if (!*tok.str)
		{
			free(tok.str);
			continue ;
		}
		lst = tokenize(&tok);
		cmds = parse(lst);
		if (process_cmd(cmds))
			return (free_memory(&lst, &cmds, tok.str));
		free_memory(&lst, &cmds, tok.str);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	minishell_init(env);
	minishell_loop();
	close(g_mini.stdin_fd);
	close(g_mini.stdout_fd);
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (g_mini.code);
}
