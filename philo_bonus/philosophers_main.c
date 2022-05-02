/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeredit <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 16:20:24 by mmeredit          #+#    #+#             */
/*   Updated: 2022/05/01 16:20:26 by mmeredit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	print_error(int flag)
{
	if (flag == 1)
		printf ("The argument is greater than an integer!\n");
	else if (flag == 2)
		printf ("The argument cannot be a negative number!\n");
	else if (flag == 3)
		printf ("Invalid number of arguments!\n");
	else
		printf ("Enter at least one philosopher!\n");
	return (0);
}

static int	ft_atoi(char *str, int *ag_philo)
{
	int						i;
	int						negative;
	unsigned long long int	num;

	num = 0;
	negative = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > 2147483647)
			return (print_error(1));
		i++;
	}
	if (negative < 0)
		return (print_error(2));
	*ag_philo = (int) num;
	return (1);
}

static int	ft_init(int ag, char **av, t_m_data *m_data)
{
	if (ag >= 5 && ag <= 6)
	{
		if (!ft_atoi(av[1], &m_data->n_philo))
			return (0);
		if (!ft_atoi(av[2], &m_data->t_to_die))
			return (0);
		if (!ft_atoi(av[3], &m_data->t_to_eat))
			return (0);
		if (!ft_atoi(av[4], &m_data->t_to_sleep))
			return (0);
	}
	else
		return (print_error(3));
	m_data->n_eat = -1;
	if (ag == 6)
	{
		if (!ft_atoi(av[5], &m_data->n_eat))
			return (0);
	}
	if (m_data->n_philo == 0)
		return (print_error(4));
	return (1);
}

void	is_died(t_philo *philo)
{
	int				i;
	struct timeval	tmp;

	i = -1;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		sem_wait(philo->time);
		if (time_count(&tmp, &philo->t_eat) > philo->_die)
		{
			sem_post(philo->time);
			sem_wait(philo->std_out);
			if (check_eat(philo))
				sem_post(philo->std_out);
			else
				print_status(philo, 4);
			kill(philo->pid, SIGTERM);
		}
		sem_post(philo->time);
		usleep(1000);
	}
	return ;
}

int	all_semaphors(t_m_data *m_data)
{
	int		i;

	i = 0;
	m_data->fork = sem_open("eat semaphor", O_CREAT, S_IRWXU, m_data->n_philo);
	m_data->time = sem_open("time semaphor", O_CREAT, S_IRWXU, 1);
	m_data->std_out = sem_open("out semaphor", O_CREAT, S_IRWXU, 1);
	// if (*(m_data->eat) == -1 || *(m_data->time) == -1 || *(m_data->std_out) == -1)
	// 	return (0);
	gettimeofday(&m_data->m_time, NULL);
	while (i < m_data->n_philo)
	{
		m_data->philo[i].time = m_data->time;
		m_data->philo[i].fork = m_data->fork;
		m_data->philo[i].std_out = m_data->std_out;
		m_data->philo[i]._id = i + 1;
		m_data->philo[i].n_eat = m_data->n_eat;
		m_data->philo[i]._sleep = m_data->t_to_sleep;
		m_data->philo[i].m_time = m_data->m_time;
		m_data->philo[i].t_eat = m_data->m_time;
		m_data->philo[i]._die = m_data->t_to_die;
		m_data->philo[i].ms_eat = m_data->t_to_eat;
		i++;
	}
	return (1); 
}

int	func(t_philo *philo)
{
	int	i;

	i = 0;
	if (pthread_create(&philo->id, NULL, (void *)&is_died, (void *)philo))
		return (kill(philo->pid, SIGKILL));
	if (pthread_detach(philo->id))
		return (kill(philo->pid, SIGKILL));
	printf ("id = %d time = %ld\n", philo->_id, philo->m_time.tv_sec * 1000 + philo->m_time.tv_usec / 1000);
	ph_process(philo);
	while (1)
	{
		printf("lol\n");
	}
	return (1);
}

int	all_destroy(t_m_data *m_data)
{
	int		i;
	pid_t	_pid;

	i = 0;
	_pid = waitpid(-1, 0, 0);
	printf ("pid = %d\n", _pid);
	while (i < m_data->n_philo)
	{
		if (m_data->philo[i].pid != _pid)
			kill(m_data->philo[i].pid, SIGKILL);
		i++;
	}
	return (0);
}

int	main(int ag, char **av)
{
	t_m_data	m_data;
	int			i;
	struct timeval tmp;

	i = 0;
	if (!ft_init(ag, av, &m_data))
		return (write(2, "Error!\n", 7));
	if (!all_semaphors(&m_data))
		return (write(2, "Error!\n", 7));
	while (i < m_data.n_philo)
	{
		m_data.philo[i].pid = fork();
		if (m_data.philo[i].pid == 0)
		{
			if (!func(&m_data.philo[i]))
				return (write(2, "Error!\n", 7));
		}
		i++;
	}
	printf ("time = %ld\n", m_data.m_time.tv_sec * 1000 + m_data.m_time.tv_usec / 1000);
	all_destroy(&m_data);
	printf ("lol\n");
	sem_close (m_data.fork);
	sem_close (m_data.time);
	sem_close (m_data.std_out);
	sem_unlink("eat semaphor");
	sem_unlink("time semaphor");
	sem_unlink("out semaphor");

	// sem_close("/eat semaphor")
	// if (!ph_mutex_tread_all(&m_data))
	// 	return (write(1, "Error!\n", 7));
	// if (is_died(&m_data) == 5)
	// {
	// 	if (!all_destroy(&m_data))
	// 		return (write(1, "Error!\n", 7));
	// }
	return (0);
}
