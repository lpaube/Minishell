/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/30 19:51:26 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "minishell.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>

char	*get_line(char *line)
{
	char	*tmp;

	if (line)
		free(line);
	line = readline(SHELL_PROMPT);
	tmp = ft_strtrim(line, WHITESPACE);
	free(line);
	line = tmp;
	if (line && *line)
		add_history(line);
	return (line);
}

void	print_token_list(const t_list *lst)
{
	t_string	token;

	while (lst)
	{
		token = lst->content;
		printf("%s\n", ft_str_data(token));
		lst = lst->next;
	}
	printf("\n");
}

char	*op_name(t_operator op)
{
	if (op == PIPE)
		return ("PIPE");
	if (op == OUTPUT)
		return ("OUTPUT");
	if (op == APPEND)
		return ("APPEND");
	if (op == INPUT)
		return ("INPUT");
	if (op == READ)
		return ("READ");
	return ("NONE");
}

void	print_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("Arg %d: %s\n", i, args[i]);
		++i;
	}
}

void	print_nodes(const t_node *lst)
{
	while (lst)
	{
		printf("Cmd: %s - Operator: %s\n", lst->name, op_name(lst->op));
		print_args(lst->args);
		printf("\n");
		lst = lst->next;
	}
}

void	init_tokenizer(t_tokenizer *tok)
{
	tok->cursor = 0;
	tok->state = TEXT;
	tok->next_token = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_tokenizer	tok;
	t_list		*lst;
	t_node		*cmds;

	(void)argc;
	(void)argv;
	(void)env;
	tok.str = NULL;
	cmds = NULL;
	while (true)
	{
		init_tokenizer(&tok);
		tok.str = get_line(tok.str);
		if (!*tok.str)
			continue ;
		lst = tokenize(&tok);
		if (ft_strncmp("exit", tok.str, 5) == 0)
			break ;
		if (lst)
		{
			cmds = parse(lst);
			if (cmds)
				print_nodes(cmds);
		}
		ft_lstclear(&lst, ft_str_free);
		nodeclear(&cmds);
	}
	free(tok.str);
	ft_lstclear(&lst, ft_str_free);
	nodeclear(&cmds);
}
