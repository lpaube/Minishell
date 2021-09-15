/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/15 18:02:06 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	*print_error(const char *msg, const char *value)
{
	if (value)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putendl_fd(value, STDERR_FILENO);
	}
	else
		ft_putendl_fd(msg, STDERR_FILENO);
	return (NULL);
}

void	*unexpected_token(const char *token)
{
	t_string	msg;

	msg = ft_str_new(NULL);
	ft_str_append_cstr(msg, "error: syntax error near unexpected token \'");
	ft_str_append_cstr(msg, token);
	ft_str_add_back(msg, '\'');
	print_error(ft_str_data(msg), NULL);
	ft_str_free(msg);
	return (NULL);
}

static void	print_redir(void *redir)
{
	t_redir	*r;

	r = redir;
	printf("File: %s - type: %s\n", r->file, type_str(r->type));
}

void	print_cmds(const t_node *cmds)
{
	int	i;

	while (cmds)
	{
		printf("Cmd: %s\n", cmds->prg);
		i = 0;
		while (cmds->args[i])
		{
			printf("Arg%d: %s\n", i, cmds->args[i]);
			++i;
		}
		ft_lstiter(cmds->redirs, print_redir);
		cmds = cmds->next;
	}
}
