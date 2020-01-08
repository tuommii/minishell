/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 11:32:38 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 16:06:16 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_path_exec(char **args, char **envs)
{
	char	**paths;
	char	*cmd;
	int		i;

	if ((args[0][0] == '.' || args[0][0] == '/') \
	&& ft_execute(args[0], args, envs))
		return (1);
	i = 0;
	paths = ft_strsplit(ft_getenv("PATH", envs), ':');
	while (paths != NULL && paths[i])
	{
		cmd = ft_pathjoin(paths[i], args[0]);
		if (ft_execute(cmd, args, envs))
		{
			ft_strdel(&cmd);
			ft_free_arr(paths);
			return (1);
		}
		ft_strdel(&cmd);
		i++;
	}
	ft_dprintf(2, "minishell: command %s not found\n", args[0]);
	if (paths != NULL)
		ft_free_arr(paths);
	return (0);
}

int			check_access(char *path)
{
	struct stat sb;

	if (!(access(path, X_OK) == 0) && lstat(path, &sb) == 0)
	{
		ft_dprintf(2, "minishell: permission denied: %s\n", path);
		return (1);
	}
	return (0);
}

int			ft_execute(char *path, char **args, char **envs)
{
	struct stat	sb;
	pid_t		pid;

	if (!args[0])
		return (0);
	if (lstat(path, &sb) == 0)
	{
		if (check_access(path))
			return (-1);
		if ((sb.st_mode & S_IFREG) && (S_IXUSR & sb.st_mode))
		{
			pid = fork();
			signal(SIGINT, handle_sigint_proc);
			if (pid == 0)
				execve(path, args, envs);
			else if (pid < 0)
			{
				ft_dprintf(2, "Fork failed!\n");
				return (-1);
			}
			wait(&pid);
			return (1);
		}
	}
	return (0);
}
