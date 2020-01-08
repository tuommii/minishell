/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:04:26 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 11:57:52 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_internal_cmd(char **args, char **envs, char *input)
{
	int code;

	code = 1;
	if (!args)
		return (0);
	if (ft_strequ(args[0], "exit"))
		handle_exit(args, envs, input);
	else if (ft_strequ(args[0], "cd"))
		code = ft_shell_cd(args, envs);
	else if (ft_strequ(args[0], "echo"))
		code = ft_shell_echo(args, envs, input);
	else if (ft_strequ(args[0], "env"))
		code = handle_print_envs(envs);
	else if (ft_strequ(args[0], "setenv"))
		code = handle_set_envs(args, envs);
	else if (ft_strequ(args[0], "unsetenv"))
		code = handle_unset_env(args, envs);
	else
		return (0);
	return (code);
}

static int	which_command(char **args, char **envs, char *input)
{
	if (check_internal_cmd(args, envs, input))
		return (0);
	ft_path_exec(args, envs);
	return (0);
}

static void	shell_loop(char **envs)
{
	char	**args;
	char	*input;
	char	*edited;
	int		code;

	welcome();
	while (1)
	{
		print_prompt();
		signal(SIGINT, handle_sigint);
		if ((code = get_next_line(1, &input)) == 0)
			return ;
		if (!input || !input[0])
			continue ;
		edited = ft_strreplace(input, "\t", " ");
		ft_strdel(&input);
		if (!(args = parse_input(edited, envs)))
		{
			ft_strdel(&edited);
			continue;
		}
		which_command(args, envs, edited);
		ft_strdel(&edited);
		ft_free_arr(args);
	}
}

char		**ft_copy_envs(char **envs)
{
	int		i;
	int		count;
	char	**tab;

	i = 0;
	tab = NULL;
	count = ft_charelems(envs);
	if (!(tab = (char **)malloc(sizeof(char *) * (count + MAX_ENV_COUNT) + 1)))
		return (NULL);
	while (envs[i])
	{
		tab[i] = NULL;
		tab[i] = ft_strdup(envs[i]);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int			main(int argc, char **argv, char **environ)
{
	char	**envs;

	envs = NULL;
	if (!(envs = ft_copy_envs(environ)) || !argc || !argv)
		return (0);
	shell_loop(envs);
	ft_free_arr(envs);
	ft_printf("\n");
	exit(0);
}
