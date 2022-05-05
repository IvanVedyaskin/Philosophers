/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:20:06 by mmeredit          #+#    #+#             */
/*   Updated: 2022/05/01 16:20:16 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "unistd.h"
# include "sys/time.h"
# include "signal.h"
# include <semaphore.h>

# define PHILOS 201

typedef struct s_philo_person
{
	int				_id;
	int				_sleep;
	int				_die;
	int				n_eat;
	int				pid;
	int				m_die;
	sem_t			*fork;
	sem_t			*std_out;
	pthread_t		id;
	struct timeval	t_eat;
	struct timeval	m_time;
	long int		ms_eat;
}	t_philo;

typedef struct s_main_data
{
	int				n_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				n_eat;
	sem_t			*std_out;
	sem_t			*fork;
	struct timeval	m_time;
	t_philo			philo[PHILOS];
}	t_m_data;

int		print_status(t_philo *philo, int status);
int		time_count(struct timeval *tm1, struct timeval *tm2);
void	ft_usleep(long int ms, struct timeval *t_eat);
int		check_eat(t_philo *philo);
int		child(t_philo *philo);
int		all_destroy(t_m_data *m_data);

#endif
