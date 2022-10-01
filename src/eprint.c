#include "minishell.h"
#include <unistd.h>
#include <stdio.h>

void	pset_err(const char *prg, const char *v1, const char *v2, int err)
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
	g_mini.code = (uint32_t)err;
}

void	unexpected_token(const char *token)
{
	t_string	msg;

	msg = ft_str_new_copy("syntax error near unexpected token \'");
	ft_str_append_cstr(msg, token);
	ft_str_add_back(msg, '\'');
	pset_err(SHELL_NAME, NULL, ft_str_data(msg), SYNTAX_ERR);
	ft_str_free(msg);
}
