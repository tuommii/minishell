/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:17:20 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 17:32:50 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_print_envs(char **envs)
{
	int i;

	i = 0;
	while (envs[i])
	{
		ft_printf("%d: %s\n", i, envs[i]);
		i++;
	}
	return (1);
}

int		handle_set_envs(char **args, char **envs)
{
	int		argc;
	char	*new;

	argc = ft_charelems(args);
	if (argc == 1)
	{
		handle_print_envs(envs);
		return (1);
	}
	if (argc != 3)
	{
		ft_dprintf(2, "Wrong amount of arguments!\n");
		return (2);
	}
	new = ft_strreplace(args[2], "\"", "");
	ft_edit_env(args[1], new, envs);
	ft_strdel(&new);
	return (1);
}

int		handle_unset_env(char **args, char **envs)
{
	if (ft_charelems(args) != 2)
	{
		ft_dprintf(2, "Wrong amount of arguments!\n");
		return (2);
	}
	ft_unset_env(args[1], envs);
	return (1);
}

void	handle_exit(char **args, char **envs, char *input)
{
	ft_printf("Very cool shell! 42/42\n");
	ft_free_arr(args);
	ft_free_arr(envs);
	ft_strdel(&input);
	exit(0);
}
