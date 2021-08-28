/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:03:37 by mleblanc          #+#    #+#             */
/*   Updated: 2021/08/27 20:37:38 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "parser.h"
#include "minishell.h"
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
	t_string		token;
	const t_list	*ptr;

	if (lst)
	{
		ptr = lst;
		while (ptr)
		{
			token = ptr->content;
			printf("%s\n", ft_str_data(token));
			ptr = ptr->next;
		}
	}
	printf("\n");
}

void	print_ast(const t_tree *ast)
{
	t_construct	*construct;
	size_t		i;

	construct = ast->content;
	printf("Name: %s\n", construct->name);
	i = 0;
	while (construct->args[i])
	{
		printf("Arg %zu: %s\n", i + 1, construct->args[i]);
		++i;
	}
	printf("\n");
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
	t_tree		*ast;

	(void)argc;
	(void)argv;
	(void)env;
	tok.str = NULL;
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
			print_token_list(lst);
			ast = parse(lst);
			if (ast)
			{
				print_ast(ast);
				print_ast(ast->right);
			}
		}
		ft_lstclear(&lst, ft_str_free);
		ft_treeclear(&ast, free_construct);
	}
	free(tok.str);
	ft_lstclear(&lst, ft_str_free);
}
