/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtuomine <mtuomine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 07:57:54 by mtuomine          #+#    #+#             */
/*   Updated: 2020/01/03 12:22:43 by mtuomine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcome(void)
{
	ft_printf("==================================================\n");
	ft_printf("\nMTUOMINE'S SHELL                          		   \n");
	ft_printf("\n==================================================\n");
}

void	print_prompt(void)
{
	char	host[MAX_PATH + 1];
	char	cwd[MAX_PATH + 1];

	gethostname(host, MAX_PATH);
	getcwd(cwd, MAX_PATH);
	ft_printf(FT_GREEN);
	ft_printf("%s", getenv("LOGNAME"));
	ft_printf(FT_RESET);
	ft_printf("@");
	ft_printf(FT_BOLD_BLUE);
	ft_printf("%s: ", host);
	ft_printf(FT_RESET);
	ft_printf("%s> ", cwd);
}
