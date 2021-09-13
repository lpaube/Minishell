/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <louis-philippe.aube@hotmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/13 17:01:57 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "phrase.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"

void	execution_control(t_phrase *phrase);
int		main_control(t_phrase *phrase);
char	**dup_env_table(char **table, t_phrase *phrase, int new_var);
char	*get_bin_path(char **envp, char *cmd);
void	pipe_read(void);
void	pipe_write(void);
int		ft_binary(t_phrase *phrase);
void	ft_echo(t_phrase *phrase);
void	ft_cd(t_phrase *phrase);
void	ft_pwd(t_phrase *phrase);
void	ft_export(t_phrase *phrase);
void	ft_unset(t_phrase *phrase);
void	ft_env(t_phrase *phrase);
void	ft_exit(t_phrase *phrase);
void	operation_control(void);
void	clean_fd(void);
void	get_dest(void);
void	clean_fd(void);
