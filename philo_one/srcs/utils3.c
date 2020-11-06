/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/06 01:22:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	print_log(int t, int id, char *msg)
{
	static char	buf[256];
	int			i;

	ft_itoa(t, buf);
	i = ft_numlen(t);
	buf[i++] = ' ';
	ft_itoa(id, buf + i);
	i += ft_numlen(id);
	ft_strcpy(buf + i, msg);
	i += ft_strlen(msg);
	buf[i++] = '\n';
	write(1, buf, i);
	while (--i >= 0)
		buf[i] = 0;
}
