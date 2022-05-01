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
	if (!philo->max)
	{
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 0);
		pthread_mutex_unlock(philo->std_out);
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 0);
		pthread_mutex_unlock(philo->std_out);
	}
	else
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 0);
		pthread_mutex_unlock(philo->std_out);
		pthread_mutex_lock(philo->right);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 0);
		pthread_mutex_unlock(philo->std_out);
	}
}

static void	ph_process(void *ph)
{
	t_philo	*philo;

	philo = ph;
	usleep((philo->_id % 2) * 1000);
	gettimeofday(&philo->t_eat, NULL);
	while (1)
	{
		if (philo->n_eat == 0)
			return ;
		check_fork(philo);
		pthread_mutex_lock(philo->std_out);
		philo->n_eat--;
		print_status(philo, 1);
		pthread_mutex_unlock(philo->std_out);
		ft_usleep(philo->ms_eat, &philo->t_eat);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 2);
		pthread_mutex_unlock(philo->std_out);
		ft_usleep(philo->_sleep, NULL);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 3);
		usleep(pthread_mutex_unlock(philo->std_out) + 900);
	}
}

int	m_fork(pthread_mutex_t *fork, int n, t_philo *philo, pthread_mutex_t *out)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(&(fork[i]), NULL))
			return (0);
		philo[i].std_out = out;
		philo[i].right = &(fork[i]);
		i++;
	}
	i = 0;
	while (i < n - 1)
	{
		philo[i].max = 0;
		philo[i].left = philo[i + 1].right;
		i++;
	}
	philo[i].left = philo[0].right;
	philo[i].max = 1;
	return (1);
}

static void	ph_init(t_m_data *m_data)
{
	int	i;

	i = 0;
	while (i < m_data->n_philo)
	{
		m_data->philo[i].n_eat = m_data->n_eat;
		m_data->philo[i].m_time = m_data->m_time;
		m_data->philo[i]._id = i + 1;
		m_data->philo[i].ms_eat = m_data->t_to_eat;
		m_data->philo[i]._sleep = m_data->t_to_sleep;
		m_data->philo[i].t_eat = m_data->m_time;
		pthread_mutex_init(&m_data->philo[i].time, NULL);
		i++;
	}
}

int	ph_mutex_tread_all(t_m_data *m_data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&(m_data->std_out), NULL))
		return (0);
	if (!m_fork(m_data->fork, m_data->n_philo, m_data->philo, &m_data->std_out))
		return (0);
	gettimeofday(&(m_data->m_time), NULL);
	ph_init(m_data);
	while (i < m_data->n_philo)
	{
		if (pthread_create(&m_data->philo[i].id, NULL, (void *)&ph_process, \
				(void *)&m_data->philo[i]))
			return (0);
		if (pthread_detach(m_data->philo[i].id))
			return (0);
		i++;
	}
	return (1);
}
