/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laube <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 14:46:24 by laube             #+#    #+#             */
/*   Updated: 2021/09/02 19:04:13 by laube            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "phrase.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include "my_env.h"
#include "tokenizer.h"

void	execution_control(t_phrase *phrase);
int		main_control(t_phrase *phrase);
char	**dup_env_table(char **table, t_phrase *phrase, int new_var);
char	*ft_append_str(char **str, char c);
char	*get_bin_path(char **envp, char *cmd);
void	pipe_read(t_phrase *phrase);
void	pipe_write(t_phrase *phrase);
int		ft_binary(t_phrase *phrase);
void	ft_echo(t_phrase *phrase);
void	ft_cd(t_phrase *phrase);
void	ft_pwd(t_phrase *phrase);
void	ft_export(t_phrase *phrase);
void	ft_unset(t_phrase *phrase);
void	ft_env(t_phrase *phrase);
void	ft_exit(t_phrase *phrase);
void	operation_control(t_phrase *phrase);
