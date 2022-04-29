//
// Created by Ivan on 29.04.2022.
//

#include "philosophers.h"

int	print_status(t_philo *philo, int status)
{
	struct timeval	timer;

//	if (status == 1)
//		gettimeofday(&philo->t_eat, NULL);
	gettimeofday(&timer, NULL);
	timer.tv_usec = (timer.tv_sec - philo->m_time.tv_sec) * 1000 + (timer.tv_usec - philo->m_time.tv_usec) / 1000;
//	while (timer.tv_sec-- != 0)
//		timer.tv_usec += 1000000;
//	timer.tv_usec = timer.tv_usec / 1000;
	if (!status)
		printf ("%ld %d has taken a fork\n", timer.tv_usec, philo->_id);
	else if (status == 1)
		printf ("%ld %d is eating\n", timer.tv_usec, philo->_id);
	else if (status == 2)
		printf ("%ld %d is sleeping\n", timer.tv_usec, philo->_id);
	else if (status == 3)
		printf ("%ld %d is thinking\n", timer.tv_usec, philo->_id);
	else if (status == 4)
		printf ("%ld %d is died\n", timer.tv_usec, philo->_id);
	else
		printf ("%ld %d is all eat\n", timer.tv_usec, philo->_id);
	return (status);
}

void	ft_usleep(long int ms, struct timeval *t_eat)
{
	struct timeval	before;
	struct timeval	after;

	gettimeofday(&before, NULL);
	if (t_eat != NULL)
	{
		t_eat->tv_usec = before.tv_usec;
		t_eat->tv_sec = before.tv_sec;
	}
	usleep((ms * 1000) - 5000);
	gettimeofday(&after, NULL);
	while (1)
	{
//		printf ("time == %ld \n", (after.tv_sec * 1000 + after.tv_usec / 1000) - (before.tv_usec / 1000 + before.tv_sec * 1000));
		if ((after.tv_sec * 1000 + after.tv_usec / 1000) - (before.tv_usec / 1000 + before.tv_sec * 1000) >= ms)
			return ;
		usleep(700);
		gettimeofday(&after, NULL);
	}
}

void	check_fork(t_philo *philo)
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

void	ph_process(void *ph)
{
	t_philo *philo;

	philo = ph;
	gettimeofday(&philo->t_eat, NULL);
	if (philo->_id % 2)
		usleep(1000);
	while (1)
	{
		if (philo->n_eat == 0)
			return ;
		check_fork(philo);
		pthread_mutex_lock(philo->std_out);
		print_status(philo, 1);
		philo->n_eat--;
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
		pthread_mutex_unlock(philo->std_out);
	}
}


int m_forks_and_out(pthread_mutex_t *fork, int n_ph, t_philo *philo, pthread_mutex_t s_out)
{
	int i;

	i = 0;
	while (i < n_ph)
	{
		if (pthread_mutex_init(&(fork[i]), NULL))
			return (0);
		philo[i].std_out = &s_out;
		philo[i].right = &(fork[i]);
		i++;
	}
	i = 0;
	while (i < n_ph - 1)
	{
		philo[i].max = 0;
		philo[i].left = philo[i + 1].right;
		i++;
	}
	philo[i].left = philo[0].right;
	philo[i].max = 1;
	return (1);
}

int	ph_mutex_tread_all(t_m_data *m_data)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&(m_data->std_out), NULL))
		return (0);
	if (!m_forks_and_out(m_data->fork, m_data->n_philo, m_data->philo, &m_data->std_out))
		return (0);
	gettimeofday(&(m_data->m_time), NULL);
	while (i < m_data->n_philo)
	{
		m_data->philo[i].n_eat = m_data->n_eat;
		m_data->philo[i].m_time = m_data->m_time;
		m_data->philo[i]._id = i;
		m_data->philo[i].ms_eat = m_data->t_to_eat;
		m_data->philo[i]._sleep = m_data->t_to_sleep;
		if (pthread_create(&m_data->philo[i].id, NULL, (void *)&ph_process, (void *)&m_data->philo[i]))
			return (0);
		if (pthread_detach(m_data->philo[i].id))
			return (0);
		i++;
	}
	return (1);
}