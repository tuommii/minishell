/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 19:49:39 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/04 16:37:34 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tilde_to_home(char **args, int index, char *home, char *temp)
{
	if (ft_strequ(args[index], "~"))
	{
		free(args[index]);
		args[index] = ft_strdup(home);
	}
	else if (args[index][0] == '~')
	{
		temp = ft_strjoin(home, &args[index][1]);
		free(args[index]);
		args[index] = ft_strdup(temp);
		free(temp);
	}
}

char		**expand_tilde(char **args, char **envs)
{
	int		i;
	char	*temp;
	char	*home;

	home = NULL;
	temp = NULL;
	if (!(home = ft_getenv("HOME", envs)))
		ft_edit_env("HOME", "/home", envs);
	i = 0;
	if (!args)
		return (args);
	while (args[i])
	{
		tilde_to_home(args, i, home, temp);
		i++;
	}
	return (args);
}

static int	is_valid_input(char *str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isspace(str[i]))
			return (1);
	}
	return (0);
}

char		**parse_input(char *str, char **envs)
{
	char **arr;

	arr = NULL;
	if (!is_valid_input(str))
		return (NULL);
	arr = split_dollars(str, envs, " $", ' ');
	arr = expand_tilde(arr, envs);
	return (arr);
}
