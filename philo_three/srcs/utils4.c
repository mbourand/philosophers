/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 03:05:33 by user42            #+#    #+#             */
/*   Updated: 2020/11/09 01:31:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*ft_strcpy(char *dest, char *src)
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

char			*ft_itoa_buf(unsigned int nb, char *buf)
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

void		print_log(int t, int id, char *msg)
{
	static char buf[256];
	int i;

	ft_itoa_buf(t, buf);
	i = ft_numlen(t);
	buf[i++] = ' ';
	ft_itoa_buf(id, buf + i);
	i += ft_numlen(id);
	ft_strcpy(buf + i, msg);
	i += ft_strlen(msg);
	buf[i++] = '\n';
	write(1, buf, i);
	while (--i >= 0)
		buf[i] = 0;
}

int		is_fed(t_philo *philo)
{
	int ret;

	sem_wait(philo->meals.mutex);
	ret = philo->meals.val >= philo->env->stngs.max_eat;
	sem_post(philo->meals.mutex);
	return (ret);
}
