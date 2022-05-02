/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:20:31 by mmeredit          #+#    #+#             */
/*   Updated: 2022/05/01 16:20:40 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_fork(t_philo *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->std_out);
	print_status(philo, 0);
	sem_post(philo->std_out);
	sem_wait(philo->fork);
	sem_wait(philo->std_out);
	print_status(philo, 0);
	sem_post(philo->std_out);
}

void	ph_process(t_philo *philo)
{
	struct timeval tmp;

	// usleep((philo->_id % 2) * 1000);
	// gettimeofday(&tmp, NULL);
	// printf ("id2 = %d time2 = %ld\n", philo->_id, (tmp.tv_sec - philo->m_time.tv_sec) / 1000 + \
	// 	(tmp.tv_usec - philo->m_time.tv_usec) * 1000);
	while (1)
	{
		if (philo->n_eat == 0)
			return ;
		check_fork(philo);
		sem_wait(philo->std_out);
		philo->n_eat--;
		print_status(philo, 1);
		sem_post(philo->std_out);
		ft_usleep(philo->ms_eat, &philo->t_eat);
		sem_post(philo->fork);
		sem_post(philo->fork);
		sem_wait(philo->std_out);
		print_status(philo, 2);
		sem_post(philo->std_out);
		ft_usleep(philo->_sleep, NULL);
		sem_wait(philo->std_out);
		print_status(philo, 3);
		usleep(sem_post(philo->std_out) + 900);
	}
}

// int	m_fork(pthread_mutex_t *fork, int n, t_philo *philo, pthread_mutex_t *out)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (pthread_mutex_init(&(fork[i]), NULL))
// 			return (0);
// 		philo[i].std_out = out;
// 		philo[i].right = &(fork[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		philo[i].max = 0;
// 		philo[i].left = philo[i + 1].right;
// 		i++;
// 	}
// 	philo[i].left = philo[0].right;
// 	philo[i].max = 1;
// 	return (1);
// }

// static void	ph_init(t_m_data *m_data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < m_data->n_philo)
// 	{
// 		m_data->philo[i].n_eat = m_data->n_eat;
// 		m_data->philo[i].m_time = m_data->m_time;
// 		m_data->philo[i]._id = i + 1;
// 		m_data->philo[i].ms_eat = m_data->t_to_eat;
// 		m_data->philo[i]._sleep = m_data->t_to_sleep;
// 		m_data->philo[i].t_eat = m_data->m_time;
// 		pthread_mutex_init(&m_data->philo[i].time, NULL);
// 		i++;
// 	}
// }

// int	ph_mutex_tread_all(t_m_data *m_data)
// {
// 	int	i;

// 	i = 0;
// 	if (pthread_mutex_init(&(m_data->std_out), NULL))
// 		return (0);
// 	if (!m_fork(m_data->fork, m_data->n_philo, m_data->philo, &m_data->std_out))
// 		return (0);
// 	gettimeofday(&(m_data->m_time), NULL);
// 	ph_init(m_data);
// 	while (i < m_data->n_philo)
// 	{
// 		if (pthread_create(&m_data->philo[i].id, NULL, (void *)&ph_process, \
// 				(void *)&m_data->philo[i]))
// 			return (0);
// 		if (pthread_detach(m_data->philo[i].id))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }
