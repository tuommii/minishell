/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:31:56 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 16:01:53 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg_count(int argc)
{
	if (argc > 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (0);
	}
	return (1);
}

static int	cd_home(int argc, char cwd[], char **envs)
{
	char *home;

	if (argc != 1)
		return (0);
	home = ft_getenv("HOME", envs);
	if (!home)
		home = "/home";
	ft_edit_env("OLDPWD", cwd, envs);
	chdir(home);
	ft_edit_env("PWD", home, envs);
	return (1);
}

static int	cd_prev(char **args, char cwd[], char old[], char **envs)
{
	if (args[1][0] == '-' && (args[1][1] == '\0' || args[1][1] == ';'))
	{
		ft_edit_env("OLDPWD", cwd, envs);
		chdir(old);
		ft_edit_env("PWD", old, envs);
		return (1);
	}
	return (0);
}

static void	cd_do(char **args, char cwd[], char **envs)
{
	if (chdir(args[1]) == 0)
	{
		ft_edit_env("OLDPWD", cwd, envs);
		getcwd(cwd, MAX_PATH);
		ft_edit_env("PWD", cwd, envs);
	}
	else
	{
		if (!check_access(args[1]))
			ft_dprintf(2, "minishell: cd: %s: Not a directory!\n", args[1]);
	}
}

int			ft_shell_cd(char **args, char **envs)
{
	int		argc;
	char	cwd[MAX_PATH + 1];
	char	old[MAX_PATH + 1];

	argc = ft_charelems(args);
	if (!check_arg_count(argc))
		return (0);
	ft_strcpy(old, ft_getenv("OLDPWD", envs));
	getcwd(cwd, MAX_PATH);
	if (args[1] && ft_strequ(args[1], "--") && cd_home(1, cwd, envs))
		return (1);
	if (cd_home(argc, cwd, envs))
		return (1);
	if (cd_prev(args, cwd, old, envs))
		return (1);
	cd_do(args, cwd, envs);
	return (1);
}
