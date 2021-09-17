/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 01:43:42 by mleblanc          #+#    #+#             */
/*   Updated: 2021/09/17 17:47:19 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	print_error(const char *prg, const char *v1, const char *v2)
{
	if (prg)
	{
		ft_putstr_fd(prg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (v1)
	{
		ft_putstr_fd(v1, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(v2, STDERR_FILENO);
}

void	unexpected_token(const char *token)
{
	t_string	msg;

	msg = ft_str_new_copy("error: syntax error near unexpected token \'");
	ft_str_append_cstr(msg, token);
	ft_str_add_back(msg, '\'');
	print_error(NULL, NULL, ft_str_data(msg));
	ft_str_free(msg);
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
		printf("Cmd: %s\n", cmds->cmd);
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
