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

#include "philosophers_bonus.h"

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
	usleep((philo->_id % 2) * 1000);
	while (1)
	{
		if (philo->n_eat == 0)
			break ;
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
		sem_post(philo->std_out);
		usleep(900);
	}
	while (1)
		usleep(200);
}

static void	is_died(t_philo *philo)
{
	int				i;
	struct timeval	tmp;

	i = -1;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		if (time_count(&tmp, &philo->t_eat) > philo->_die)
		{
			sem_wait(philo->std_out);
			if (check_eat(philo))
				sem_post(philo->std_out);
			else
				print_status(philo, 4);
			exit(EXIT_SUCCESS);
		}
		usleep(2000);
	}
	return ;
}

int	child(t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_create(&philo->id, NULL, (void *)&is_died, (void *)philo))
		exit(EXIT_FAILURE);
	if (pthread_detach(philo->id))
		exit(EXIT_FAILURE);
	ph_process(philo);
	return (1);
}

int	all_destroy(t_m_data *m_data)
{
	int		i;
	pid_t	_pid;

	i = 0;
	_pid = waitpid(-1, 0, 0);
	i = 0;
	while (i < m_data->n_philo)
	{
		if (m_data->philo[i].pid != _pid)
			kill(m_data->philo[i].pid, SIGKILL);
		i++;
	}
	sem_close (m_data->fork);
	sem_close (m_data->std_out);
	sem_unlink("eat semaphor");
	sem_unlink("out semaphor");
	return (0);
}
