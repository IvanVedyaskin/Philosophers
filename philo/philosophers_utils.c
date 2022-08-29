/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:20:47 by mmeredit          #+#    #+#             */
/*   Updated: 2022/05/01 16:20:49 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_status(t_philo *philo, int status)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	pthread_mutex_lock(&philo->time);
	if (status == 1)
	{
		philo->t_eat.tv_sec = timer.tv_sec;
		philo->t_eat.tv_usec = timer.tv_usec;
	}
	timer.tv_usec = time_count(&timer, &philo->m_time);
	pthread_mutex_unlock(&philo->time);
	if (!status)
		printf ("%d %d has taken a fork\n", timer.tv_usec, philo->_id);
	else if (status == 1)
		printf ("%d %d is eating\n", timer.tv_usec, philo->_id);
	else if (status == 2)
		printf ("%d %d is sleeping\n", timer.tv_usec, philo->_id);
	else if (status == 3)
		printf ("%d %d is thinking\n", timer.tv_usec, philo->_id);
	else if (status == 4)
		printf("%d %d is died\n", timer.tv_usec, philo->_id);
	else
		printf ("%d is all eat\n", timer.tv_usec);
	return (status);
}

void	ft_usleep(long int ms, struct timeval *t_eat)
{
	struct timeval	before;
	struct timeval	after;

	(void) t_eat;
	gettimeofday(&before, NULL);
	usleep((ms * 1000) - 5000);
	gettimeofday(&after, NULL);
	while (1)
	{
		if (time_count(&after, &before) >= ms)
			return ;
		usleep(500);
		gettimeofday(&after, NULL);
	}
}

int	time_count(struct timeval *tm1, struct timeval *tm2)
{
	struct timeval	res;

	res.tv_sec = tm1->tv_sec - tm2->tv_sec;
	res.tv_usec = tm1->tv_usec - tm2->tv_usec;
	while (res.tv_sec-- != 0)
		res.tv_usec += 1000000;
	return (res.tv_usec / 1000);
}

int	check_eat(t_m_data *m_data)
{
	int	i;

	i = 0;
	while (i < m_data->n_philo)
	{
		if (m_data->philo[i].n_eat != 0)
			return (0);
		i++;
	}
	return (1);
}

int	all_destroy(t_m_data *m_data)
{
	int	i;

	i = 0;
	while (i < m_data->n_philo)
	{
		if (pthread_mutex_destroy(&m_data->fork[i]))
			return (0);
		if (pthread_mutex_destroy(&m_data->philo[i].time))
			return (0);
		i++;
	}
	if (pthread_mutex_destroy(&m_data->std_out))
		return (0);
	return (1);
}
