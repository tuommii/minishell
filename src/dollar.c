/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 20:19:30 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 11:48:31 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset(int *i, int *j, int *start, int *env_len)
{
	*i = -1;
	*j = 0;
	*start = 0;
	*env_len = 0;
}

char		*get_dollar_name(const char *str)
{
	int		start;
	int		env_len;
	int		i;
	int		j;
	char	*new;

	reset(&i, &j, &start, &env_len);
	if (!str || (str[0] && str[0] == '$' && str[1] && str[1] == '\0'))
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			start = i;
			j = i;
			env_len = 1;
			while (str[++j] && (ft_isalnum(str[j]) || str[j] == '_'))
				env_len++;
		}
	}
	if (env_len <= 1 || !(new = ft_strsub(str, start, env_len)))
		return (NULL);
	return (new);
}

static char	**expand_dollar(char **args, char **envs)
{
	int		i;
	char	*env_name;
	char	*value;
	char	*new;

	i = -1;
	if (!args)
		return (args);
	while (args[++i])
	{
		env_name = get_dollar_name(args[i]);
		if (!env_name)
			continue ;
		value = ft_getenv(env_name + 1, envs);
		if (!value)
		{
			free(env_name);
			continue ;
		}
		new = ft_strreplace(args[i], env_name, value);
		free(args[i]);
		free(env_name);
		args[i] = new;
	}
	return (args);
}

char		**split_dollars(char *str, char **envs, char *rep_with, char split)
{
	char **arr;
	char *new;

	new = ft_strreplace(str, "$", rep_with);
	arr = ft_strsplit(new, split);
	ft_strdel(&new);
	expand_dollar(arr, envs);
	return (arr);
}
