/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/12/10 14:31:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int		ft_atoui(const char *s)
{
	long long	res;
	int			i;

	i = -1;
	res = 0;
	if (!s || !s[0])
		return (-1);
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9' || res > INT_MAX)
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
	buf[len] = 0;
	while (--len >= 0)
	{
		buf[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (buf);
}

char	*ft_strjoin(char *s1, char *s2, char *buf)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	while (s1[++i])
		buf[i] = s1[i];
	while (s2[++j])
		buf[i + j] = s2[j];
	buf[i + j] = 0;
	return (buf);
}
