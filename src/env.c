/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:28:13 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/03 09:38:25 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_getenv(char *name, char **envs)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	if (!name || ft_strequ(name, "$"))
		return (NULL);
	while (envs[i])
	{
		if (ft_env_exists(envs[i], name, len))
			return (&envs[i][len + 1]);
		i++;
	}
	return (NULL);
}

static int	ft_getenvi(char *name, char **envs)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	while (envs[i])
	{
		if (ft_env_exists(envs[i], name, len))
			return (i);
		i++;
	}
	return (-1);
}

static void	ft_new_env(char *name, char *value, char **envs)
{
	int		count;
	char	*new;
	char	*temp;

	count = ft_charelems(envs);
	if (count >= MAX_ENV_COUNT)
	{
		ft_dprintf(2, "No room!\n");
		return ;
	}
	temp = ft_strjoin(name, "=");
	new = ft_strjoin(temp, value);
	ft_strdel(&temp);
	envs[count] = ft_strdup(new);
	ft_strdel(&new);
	return ;
}

int			ft_unset_env(char *name, char **envs)
{
	int		i;

	i = ft_getenvi(name, envs);
	if (i == -1)
		return (0);
	ft_memset(envs[i], 0, ft_strlen(name));
	return (1);
}

void		ft_edit_env(char *name, char *value, char **envs)
{
	char	*old;
	char	*temp;
	int		i;

	i = ft_getenvi(name, envs);
	old = ft_getenv(name, envs);
	if (i == -1)
	{
		ft_unset_env(name, envs);
		ft_new_env(name, value, envs);
		return ;
	}
	temp = ft_strreplace(envs[i], old, value);
	free(envs[i]);
	envs[i] = temp;
}
