/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:28:30 by user42            #+#    #+#             */
/*   Updated: 2020/11/07 15:10:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

struct s_philo;

typedef struct	s_mutexint
{
	sem_t	*mutex;
	int		val;
}				t_mutexint;

typedef struct	s_settings
{
	int		philo_nb;
	int		die_time;
	int		sleep_time;
	int		eat_time;
	int		max_eat;
}				t_settings;

typedef struct	s_env
{
	t_settings		stngs;
	sem_t			*log_mutex;
	struct s_philo	*philos;
	sem_t			*forks;
	sem_t			*picking;
	int				start_time;
	t_mutexint		finish;
	t_mutexint		terminated;
}				t_env;

typedef struct	s_philo
{
	t_env		*env;
	pthread_t	thread;
	int			id;
	t_mutexint	last_eat;
	t_mutexint	meals;
	int			l_fork;
	int			r_fork;
	char		*meals_name;
	char		*lsteat_name;
}				t_philo;

void			*process_philosopher(void *philo);
void			phil_wait(long micro);
void			phil_eat(t_philo *philo);
void			phil_sleep(t_philo *philo);
void			phil_think(t_philo *philo);
void			phil_die(t_philo *philo);
void			phil_fork(t_philo *philo);
int				starved(t_philo *philo);
void			log_philo(t_philo *philo, char *msg);
int				ft_atoui(const char *s);
size_t			ft_strlen(char *s);
void			ft_putnbr(int i);
void			ft_putchar(char c);
int				get_time(void);
void			wait_philosophers(t_env *env);
int				is_finished(t_env *env);
int				can_eat(t_philo *philo);
void			free_env(t_env *env);
void			log_philo_force(t_philo *philo, char *msg);
void			wait_fork(t_philo *philo, int index);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_itoa(unsigned int nb);
int				ft_numlen(unsigned int i);
void			print_log(int t, int id, char *msg);
char			*ft_itoa_buf(unsigned int nb, char *buf);

#endif
