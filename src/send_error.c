/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 12:56:25 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/07/04 12:56:26 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	send_error(char **envp)
{
	if (!*envp)
		ft_putstr_fd("environment not loaded\n", 2);
	else if (errno)
	{
		perror(get_shell(envp));
	}
	else
	{
		ft_putstr_fd(get_shell(envp), 2);
		ft_putstr_fd(": an unexpected error occured\n", 2);
	}
}
