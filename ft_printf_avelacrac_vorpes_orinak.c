/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:44:58 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/02/07 17:25:00 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	cases(va_list lst, char c)
{
	if (c == 'c')
		return (ft_printchar(va_arg(lst, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(lst, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(lst, int)));
	else if (c == 'u')
		return (ft_printnbr(va_arg(lst, unsigned int)));
	else if (c == 'x')
		return (ft_print_x(va_arg(lst, unsigned int), 0));
	else if (c == 'X')
		return (ft_print_x(va_arg(lst, unsigned int), 1));
	else if (c == 'p')
		return (write(1, "0x", 2) + ft_print_x(va_arg(lst, unsigned long), 0));
	else if (c == '%')
		return (ft_printchar('%'));
	return (0);
}

int	lala(const char *a, va_list lst)
{
	int		len;
	char	*p;

	p = ft_strchr(a, '%');
	if (!p)
	{
		p = ft_strchr(a, '\0');
		return (write (1, a, p - a));
	}
	len = write(1, a, p - a);
	if (len < 0)
		return (-1);
	len += cases(lst, p[1]);
	if (*(p + 1))
		len += lala(p + 2, lst);
	return (len);
}

int	ft_printf(const char *a, ...)
{
	va_list	lst;
	int		len;

	va_start(lst, a);
	len = lala(a, lst);
	va_end(lst);
	return (len);
}
