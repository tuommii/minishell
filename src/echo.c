/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:08:41 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 11:48:03 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_splitstr(char *split)
{
	split[0] = 24;
	split[1] = '$';
	split[2] = '\0';
}

static void	print_arr(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
	{
		ft_printf("%s", arr[i]);
	}
	ft_printf("\n");
	ft_free_arr(arr);
}

static int	handle_quoted(char *input, char **envs)
{
	char	*new;
	int		i;
	char	**arr;
	char	split[3];

	if (!ft_strchr(input, '"'))
		return (0);
	i = 5;
	create_splitstr(split);
	while (ft_isspace(input[i]))
		i++;
	new = ft_strreplace(input + i, "\"", "");
	if (!new || !new[0])
	{
		ft_strdel(&new);
		ft_printf("\n");
		return (1);
	}
	arr = split_dollars(new, envs, split, 24);
	ft_strdel(&new);
	print_arr(arr);
	return (1);
}

int			ft_shell_echo(char **args, char **env, char *input)
{
	int i;

	i = 1;
	if (!args[1])
	{
		ft_printf("\n");
		return (1);
	}
	if (handle_quoted(input, env))
		return (1);
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	ft_printf("\n");
	return (1);
}
