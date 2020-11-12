/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:17 by user42            #+#    #+#             */
/*   Updated: 2020/11/07 15:07:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

char	*ft_itoa(unsigned int nb)
{
	char	*res;
	int		len;

	len = ft_numlen(nb);
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[len] = 0;
	while (--len >= 0)
	{
		res[len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		s1len;
	int		s2len;
	int		i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(res = malloc(sizeof(char) * (s1len + s2len + 1))))
		return (NULL);
	i = -1;
	while (++i < s1len)
		res[i] = s1[i];
	i--;
	while (++i < s1len + s2len)
		res[i] = s2[i - s1len];
	res[s1len + s2len] = 0;
	return (res);
}
