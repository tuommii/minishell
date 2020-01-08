/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 07:07:19 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/06 15:49:34 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# ifdef linux
#  include <wait.h>
# endif
# ifdef unix
#  include <sys/wait.h>
# endif

# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"

# define MAX_PATH 4096
# define MAX_ENV_COUNT 1024

char	**parse_input(char *str, char **envs);
int		ft_execute(char *path, char **args, char **envs);

void	handle_sigint(int sig);
void	handle_sigint_proc(int sig);

char	*ft_getenv(char *name, char **envs);
int		ft_env_exists(char *name, char *given, int len_given);
int		ft_charelems(char **tab);
char	**ft_copy_envs(char **envs);
void	ft_edit_env(char *name, char *value, char **envs);
int		ft_unset_env(char *name, char **envs);
int		ft_path_exec(char **args, char **envs);
int		check_access(char *path);

int		ft_shell_echo(char **args, char **env, char *input);
int		ft_shell_cd(char **args, char **envs);

void	ft_free_arr(char **arr);

void	welcome(void);
void	print_prompt(void);

int		handle_set_envs(char **args, char **envs);
int		handle_unset_env(char **args, char **envs);
int		handle_print_envs(char **envs);
void	handle_exit(char **args, char **envs, char *input);

char	**expand_tilde(char **args, char **envs);
char	*get_dollar_name(const char *str);
char	**split_dollars(char *str, char **envs, char *rep_with, char split);

#endif
