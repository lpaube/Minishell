/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleblanc <mleblanc@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 00:11:05 by laube             #+#    #+#             */
/*   Updated: 2021/09/15 18:03:09 by mleblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

#define CWD_BUFFER_SIZE (4096)

void	ft_cd(t_node *node)
{
	char	*cwd;
	char	*pwd;

	if (ft_strarr_size(node->args) > 2)
		ft_putendl_fd("cd: too many arguments", STDERR_FILENO);
	else if (ft_strarr_size(node->args) == 1)
		chdir(ft_getenv("HOME"));
	else if (chdir(node->args[1]) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(node->args[1], STDERR_FILENO);
	}
	cwd = getcwd(NULL, 0);
	pwd = ft_strjoin("PWD=", cwd);
	ft_export(pwd);
	free(cwd);
}

void	ft_pwd(t_node *node)
{
	char	cwd[CWD_BUFFER_SIZE];

	(void)node;
	if (getcwd(cwd, CWD_BUFFER_SIZE) != NULL)
		printf("%s\n", cwd);
	else
		print_error("pwd: could not get current directory.");
}

bool	is_valid_var_name(const char *name)
{
	char		*ptr;
	t_string	var;
	bool		ret;

	ptr = ft_strchr(name, '=');
	if (!ptr)
	{
		print_error("export: not valid in this context: ", name);
		return (false);
	}
	var = ft_str_new(NULL);
	while (name != ptr)
		ft_str_add_back(var, *name++);
	ptr = ft_str_data(var);
	ret = true;
	while (*ptr)
	{
		if (!(ft_isalnum(*ptr) || *ptr == '_'))
		{
			ret = false;
			print_error("export: not valid in this context: ", ft_str_data(var));
			break ;
		}
		++ptr;
	}
	ft_str_free(var);
	return (ret);
}

int	ft_export(char *env_var)
{
	char	*var_name;
	char	*equal_char;
	int		i;

	if (!env_var)
		return (ft_env());
	if (!is_valid_var_name(env_var))
		return (0);
	var_name = ft_strdup(env_var);
	i = -1;
	while (g_minishell.env[++i])
	{
		if (ft_strnstr(g_minishell.env[i], var_name, ft_strlen(var_name)))
		{
			free(g_minishell.env[i]);
			g_minishell.env[i] = env_var;
			free(var_name);
			return (0);
		}
	}
	g_minishell.env = dup_env_table(g_minishell.env, env_var, 1);
	free(var_name);
	return (0);
}

void	ft_unset(t_node *phrase)
{
	int	i;
	int	j;

	i = 0;
	while (phrase->args[++i])
	{
		phrase->args[i] = ft_strjoin(phrase->args[i], "=");
		j = -1;
		while (g_minishell.env[++j])
		{
			if (ft_strnstr(g_minishell.env[j], phrase->args[i],
					ft_strlen(phrase->args[i])))
			{
				free(g_minishell.env[j]);
				while (g_minishell.env[j + 1])
				{
					g_minishell.env[j] = g_minishell.env[j + 1];
					j++;
				}
				g_minishell.env[j] = NULL;
				free(g_minishell.env[j + 1]);
				break ;
			}
		}
	}
}

int	ft_env(void)
{
	int	i;

	i = 0;
	while (g_minishell.env[i])
	{
		printf("%s\n", g_minishell.env[i]);
		i++;
	}
	return (0);
}
