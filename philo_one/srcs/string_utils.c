/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/30 18:15:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_atoui(const char *s)
{
	int res;
	int i;

	i = -1;
	res = 0;
	if (!s || !s[0])
		return (-1);
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		res = res * 10 + (s[i] - '0');
	}
	return (res);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	if (!dest || !src)
		return (dest);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

int		ft_numlen(unsigned int i)
{
	unsigned int	len;

	len = 1;
	while (i >= 10)
	{
		len++;
		i /= 10;
	}
	return (len);
}

char	*ft_itoa(unsigned int nb, char *buf)
{
	int		len;

	len = ft_numlen(nb);
	while (--len >= 0)
	{
		buf[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (buf);
}
