/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgrigor2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:21:22 by dgrigor2          #+#    #+#             */
/*   Updated: 2025/01/29 15:23:45 by dgrigor2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	unsigned char	*p;

	len = ft_strlen(s);
	p = (unsigned char *)s + len;
	while ((unsigned char *)s <= p)
	{
		if (*p == (unsigned char)c)
			return ((char *)p);
		p--;
	}
	return (0);
}
